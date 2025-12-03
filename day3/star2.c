#include <stdio.h>
#include <stdlib.h>

// Banksize = 100 for real input, 15 for test input
#define BANKSIZE 100
#define BATTERYSIZE 12

int getDigit() {
    return getchar() - '0';
}

unsigned long makeNum(int* num) {
    long res = num[0];
    for (int i = 1; i < BATTERYSIZE; i++) {
        res *= 10;
        res += num[i];
    }
    return res;
}

void readBank(int* bank) {
    for (int i = 0; i < BANKSIZE; i++) {
        bank[i] = getDigit();
    }
}

int rightBigger(int* left, int* right) {
    for (int i = 0; i < BATTERYSIZE; i++) {
        if (right[i] > left[i]) return 1;
        if (right[i] < left[i]) return 0;
    }
    return 0;
}

void copy(int* toCopy, int* copyInto) {
    for (int i = 0; i < BATTERYSIZE; i++) {
        copyInto[i] = toCopy[i];
    }
}

int* removeElem(int* new, int* num, int idx, int newdigit) {
    int newidx = 0;
    for (int i = 0; i < BATTERYSIZE; i++) {
        if (i == idx) continue;
        new[newidx] = num[i];
        newidx++;
    }
    new[BATTERYSIZE-1] = newdigit;
}

unsigned long processBank(int* bank) {
    int num[BATTERYSIZE] = {0};
    copy(bank, num);
    for (int nextIdx = BATTERYSIZE; nextIdx < BANKSIZE; nextIdx++) {
        int nextDigit = bank[nextIdx];
        int biggest[BATTERYSIZE] = {0};
        copy(num, biggest);
        for (int i = 0; i < BATTERYSIZE; i++) {
            int new[BATTERYSIZE] = {0};
            removeElem(new, num, i, nextDigit);
            if (rightBigger(biggest, new)) {
                copy(new, biggest);
            }
        }
        copy(biggest, num);
    }
    return makeNum(num);
}

int main() {
    int bank[BANKSIZE] = {0};
    readBank(bank);
    unsigned long joltSum = processBank(bank);
    while (getchar() != EOF) {
        readBank(bank);
        joltSum += processBank(bank);
    }
    printf("Total jolts with bigger batteries: %lu\n", joltSum);
}