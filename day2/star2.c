#include <stdio.h>
#include <string.h>

int isTupledNumber(char* buff, int len, int tuple) {
    if (len % tuple) return 0;
    int stride = len/tuple;
    for (int i = 0; i < stride; i++) {
        for (int s = 1; s < tuple; s++) {
            if (buff[i+(s-1)*stride] != buff[i+s*stride]) return 0;
        }
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
        int len = strlen(buff);
        for (int t = 2; t <= len; t++) {
            if (isTupledNumber(buff, len, t)) {
                printf("Invalid ID in range %ld-%ld: %ld.\n", start, end, i);
                summedIDs += i;
                break;
            }
        }
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