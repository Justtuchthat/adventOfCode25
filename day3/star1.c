#include <stdio.h>
#include <stdlib.h>

int getDigit() {
    return getchar() - '0';
}

int readBank() {
    int first = getDigit(), last = getDigit(); // Get first possible battery reading
    int next = getDigit(); // Get next digit that could be added
    while (next >= 0 & next < 10) { // Continue while reading digits (stop at endline and EOF)
        if (10*last+next > 10*first + last) { // If pushing out the first digit replacing empty space with new digit is larger, keep the new numbers
            first = last;
            last = next;
        } else if (10*first+next > 10*first + last) { // If pushing out the last digit, replacing empty space with new digit is larger, keep the new numbers
            last = next;
        }
        next = getDigit();
    }
    int jolts = 10*first+last; // Calculate battery reading
    if (next == '\n'-'0') return jolts; // If last read character was endline return normally
    return jolts+100; // If last read character was not endline, it was EOF, add 100 to battery level to signify EOF
}

int main() {
    int joltage = readBank();
    int newJolts = 0;
    while (newJolts < 100) { // If newJolts is larger than 100 EOF was reahced and stop looping
        joltage += newJolts;
        newJolts = readBank();
    }
    joltage += newJolts; // Add jolts form last battery bank
    joltage -= 100; // Remove 100 that was added to signify EOF
    printf("Total banks summed joltage: %d\n", joltage);
}