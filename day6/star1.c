#include <stdio.h>
#include <stdlib.h>

// Example has 4, input has 1000
#define NUM_MATH_PROBLEMS 1000
// 4 nums per math problem, 3 in the example
#define MATH_PROBLEMS_DEPTH 4

unsigned long* readLine() {
    unsigned long* line = calloc(NUM_MATH_PROBLEMS, sizeof(unsigned long));
    for (int i = 0; i < NUM_MATH_PROBLEMS; i++) {
        scanf("%lu", line+i);
    }
    getchar();
    return line;
}

int main() {
    unsigned long* lines[MATH_PROBLEMS_DEPTH] = {0};
    for (int i = 0; i < MATH_PROBLEMS_DEPTH; i++) {
        lines[i] = readLine();
    }
    char c;
    unsigned long sum = 0;
    for (int i = 0; i < NUM_MATH_PROBLEMS; i++) {
        scanf(" %c", &c);
        if (c == '*') {
            unsigned long total = 1;
            for (int j = 0; j < MATH_PROBLEMS_DEPTH; j++) {
                total *= lines[j][i];
            }
            sum += total;
        } else {
            unsigned long total = 0;
            for (int j = 0; j < MATH_PROBLEMS_DEPTH; j++) {
                total += lines[j][i];
            }
            sum += total;
        }
    }
    printf("Math homework sum: %lu\n", sum);
}