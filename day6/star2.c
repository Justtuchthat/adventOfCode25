#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ul unsigned long

// Example has 4, input has 1000
#define NUM_MATH_PROBLEMS 1000
// 4 nums per math problem, 3 in the example
#define MATH_PROBLEMS_DEPTH 4

char* readLine() {
    char buffer[NUM_MATH_PROBLEMS*(MATH_PROBLEMS_DEPTH+1)+2];
    fgets(buffer, NUM_MATH_PROBLEMS*(MATH_PROBLEMS_DEPTH+1)+2, stdin);
    int size = strlen(buffer);
    char* line = calloc(size, sizeof(char));
    memcpy(line, buffer, size);
    if (line[size-1] == '\n') line[size-1] = '\0';
    return line;
}

size_t readNum(char** lines, int i) {
    char num[MATH_PROBLEMS_DEPTH+1] = {0};
    for (int j = 0; j < MATH_PROBLEMS_DEPTH; j++) {
        num[j] = lines[j][i];
    }
    size_t ret = 0;
    if (sscanf(num, "%zu", &ret) == 0) return 0;
    return ret;
}

size_t readProblem(char** lines, int* i) {
    size_t num = readNum(lines, *i);
    size_t total = 0;
    if (lines[MATH_PROBLEMS_DEPTH][*i] == '*') {
        total = 1;
        while (num) {
            total *= num;
            (*i)++;
            num = readNum(lines, *i);
        }
    } else {
        while (num) {
            total += num;
            (*i)++;
            num = readNum(lines, *i);
        }
    }
    return total;
}

int main() {
    char** lines = calloc(MATH_PROBLEMS_DEPTH+1, sizeof(char*));
    for (int i = 0; i <= MATH_PROBLEMS_DEPTH; i++) {
        lines[i] = readLine();
    }
    size_t total = 0;
    for (int i = 0; i < strlen(lines[0]); i++) {
        total += readProblem(lines, &i);
    }
    printf("Total of problems: %zu\n", total);
    for (int i = 0; i <= MATH_PROBLEMS_DEPTH; i++) {
        free(lines[i]);
    }
    free(lines);
}