#include <stdio.h>
#include <string.h>

int isTupledNumber(char* buff, int len, int tuple) {
    if (len % tuple) return 0; // If number string length not a multiple of the tuple being checked it cannot be the tuple
    int stride = len/tuple; // Calculate length of substring in tuple
    for (int i = 0; i < stride; i++) { // Loop over each char in substring
        for (int s = 1; s < tuple; s++) { // Check if substrings all equal
            if (buff[i+(s-1)*stride] != buff[i+s*stride]) return 0; //  Character missmatch means it is not tupled
        }
    }
    return 1; // All substrings match
}

unsigned long readNextIDRange() {
    unsigned long summedIDs = 0; // Keep track of sum of invalid IDs
    unsigned long start, end;
    scanf("%ld-%ld", &start, &end); // Read next ID range
    for (unsigned long i = start; i <= end; i++) { // Loop over range
        char buff[20] = {0}; // Buffer to print next number to check to
        sprintf(buff, "%ld", i); // Print number to buffer
        int len = strlen(buff); // Get number string length
        for (int t = 2; t <= len; t++) { // Check all possible tuples
            if (isTupledNumber(buff, len, t)) { // If number is tupled
                printf("Invalid ID in range %ld-%ld: %ld.\n", start, end, i);
                summedIDs += i; // Add number to range
                break; // Break out of all tuple check for loop, continue to next ID to check
            }
        }
    }
    return summedIDs;
}

int main() {
    unsigned long sum = readNextIDRange();
    while (getchar() != EOF) { // Keep going until EOF is reached
        sum += readNextIDRange();
    }
    printf("Sum of all invalid IDs: %ld\n", sum);
}