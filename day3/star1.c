#include <stdio.h>
#include <stdlib.h>

int getDigit() {
    return getchar() - '0';
}

int readBank() {
    int first = getDigit(), last = getDigit();
    int next = getDigit();
    while (next >= 0 & next < 10) {
        if (10*last+next > 10*first + last) {
            first = last;
            last = next;
        } else if (10*first+next > 10*first + last) {
            last = next;
        }
        next = getDigit();
    }
    int jolts = 10*first+last;
    if (next == '\n'-'0') return jolts;
    return jolts+100;
}

int main() {
    int joltage = readBank();
    int newJolts = 0;
    while (newJolts < 100) {
        joltage += newJolts;
        newJolts = readBank();
    }
    joltage += newJolts;
    joltage -= 100;
    printf("Total banks summed joltage: %d\n", joltage);
}