#include <stdio.h>
#include <stdlib.h>

// Banksize = 100 for real input, 15 for test input
#define BANKSIZE 100
#define BATTERYSIZE 12

int getDigit() {
    return getchar() - '0'; // Returns the number that represents the read digit
}

unsigned long makeNum(int* num) {
    long res = num[0];
    for (int i = 1; i < BATTERYSIZE; i++) {
        res *= 10; // Multiply number by 10, then add new digit to calculate number represented by array
        res += num[i];
    }
    return res;
}

void readBank(int* bank) {
    for (int i = 0; i < BANKSIZE; i++) {
        bank[i] = getDigit(); // Read BANKSIZE amount of digits to read a bank fully
    }
}

int rightBigger(int* left, int* right) {
    for (int i = 0; i < BATTERYSIZE; i++) {
        if (right[i] > left[i]) return 1; // If right battery is bigger, return true
        if (right[i] < left[i]) return 0; // If right battery is smaller, return false
    }
    return 0; // Left and right battery are equal, thus right is not bigger
}

void copy(int* toCopy, int* copyInto) {
    for (int i = 0; i < BATTERYSIZE; i++) {
        copyInto[i] = toCopy[i]; // Copies battery from toCopy to copyInto
    }
}

int* removeElem(int* new, int* num, int idx, int newdigit) {
    int newidx = 0;
    for (int i = 0; i < BATTERYSIZE; i++) {
        if (i == idx) continue; // If removing idx is reached, skip it
        new[newidx] = num[i];
        newidx++; // Increase pasting index only when not removing idx is copied
    }
    new[BATTERYSIZE-1] = newdigit; // Insert new digit in last place
}

unsigned long processBank(int* bank) {
    int num[BATTERYSIZE] = {0};
    copy(bank, num); // Copy the first 12 digits of bank to battery
    for (int nextIdx = BATTERYSIZE; nextIdx < BANKSIZE; nextIdx++) { // Loop over all other digits
        int nextDigit = bank[nextIdx];
        int biggest[BATTERYSIZE] = {0}; // Using extra battery to not change num in the middle of calculations
        copy(num, biggest); // Create copy of battery for storing largest possible battery with new digit
        for (int i = 0; i < BATTERYSIZE; i++) { // Loop over all digits in battery to see if removing any of them creates a bigger battery
            int new[BATTERYSIZE] = {0};
            removeElem(new, num, i, nextDigit); // Remove ith digit from current battery and add newest digit in the end
            if (rightBigger(biggest, new)) { // If it is bigger than current num, store result in biggest
                copy(new, biggest);
            }
        }
        copy(biggest, num); // Copy biggest back into num
    }
    return makeNum(num);
}

int main() {
    int bank[BANKSIZE] = {0};
    readBank(bank);
    unsigned long joltSum = processBank(bank);
    while (getchar() != EOF) { // Continue until EOF is reached
        readBank(bank);
        joltSum += processBank(bank);
    }
    printf("Total jolts with bigger batteries: %lu\n", joltSum);
}