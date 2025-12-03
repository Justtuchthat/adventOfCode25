#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isDoubledNumber(char* buff) {
    int len = strlen(buff);
    if (len % 2 == 1) return 0;
    int mid = len/2;
    for (int i = 0; i < mid; i++) {
        if (buff[i] != buff[i+mid]) return 0;
    }
    return 1;
}

unsigned long readNextIDRange() {
    unsigned long summedIDs = 0;
    unsigned long start, end;
    scanf("%ld-%ld", &start, &end);
    for (unsigned long i = start; i <= end; i++) {
        char buff[20] = {0};
        sprintf(buff, "%ld", i);
        if (isDoubledNumber(buff)) summedIDs += i;
    }
    return summedIDs;
}

int main() {
    unsigned long sum = readNextIDRange();
    while (getchar() != EOF) {
        sum += readNextIDRange();
    }
    printf("Sum of all invalid IDs: %ld\n", sum);
}