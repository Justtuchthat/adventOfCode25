#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isDoubledNumber(char* buff) {
    int len = strlen(buff);
    if (len % 2 == 1) return 0; // If number string length is odd it cannot be doubled
    int mid = len/2; // Calculate midpoint of number string
    for (int i = 0; i < mid; i++) { // Loop until midpoint
        if (buff[i] != buff[i+mid]) return 0; // If 2 characters missmatch the number is not doubled
    }
    return 1; // Number string is even length and all characters match eachother so is doubled
}

unsigned long readNextIDRange() {
    unsigned long summedIDs = 0; // Keep track of sum of invalid IDs
    unsigned long start, end;
    scanf("%ld-%ld", &start, &end); // Read ID range
    for (unsigned long i = start; i <= end; i++) { // Loop over ID range
        char buff[20] = {0}; // Make string buffer for number string
        sprintf(buff, "%ld", i); // Print number to buffer to get number string
        if (isDoubledNumber(buff)) summedIDs += i; // If number is doubled add it to invalid ID sum
    }
    return summedIDs;
}

int main() {
    unsigned long sum = readNextIDRange();
    while (getchar() != EOF) { // Loop over all ID ranges until EOF is reached
        sum += readNextIDRange();
    }
    printf("Sum of all invalid IDs: %ld\n", sum);
}