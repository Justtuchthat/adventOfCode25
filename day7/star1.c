#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 256

char* readLine() {
    char buffer[MAX_LINE_SIZE];
    char* result = fgets(buffer, MAX_LINE_SIZE, stdin);
    if (result == NULL) return NULL;
    int size = strlen(buffer);
    char* line = calloc(size, sizeof(char));
    memcpy(line, buffer, size*sizeof(char));
    if (line[size-1] == '\n') line[size-1] = '\0';
    return line;
}

char** readInput() {
    char* buffer[MAX_LINE_SIZE] = {0};
    char* line = readLine();
    int i;
    for (i = 0; i < MAX_LINE_SIZE; i++) {
        if (line == NULL) break;
        buffer[i] = line;
        line = readLine();
    }
    char** lines = calloc(i+1, sizeof(char*));
    memcpy(lines, buffer, i*sizeof(char*));
    return lines;
}

void processFirstLine(char** lines) {
    for (int i = 0; lines[0][i] != '\0'; i++) {
        if (lines[0][i] == 'S') {
            lines[1][i] = '|';
            break;
        }
    }
}

void printLines(char** lines) {
    for (int i = 0; lines[i] != NULL; i++) {
        printf("%s\n", lines[i]);
    }
}

void processLine(char** lines, int i) {
    for (int j = 0; lines[i][j] != '\0'; j++) {
        if (lines[i][j] == '^' & lines[i-1][j] == '|') {
            lines[i][j-1] = '|';
            lines[i][j+1] = '|';
            lines[i+1][j-1] = '|';
            lines[i+1][j+1] = '|';
        }
        if (lines[i][j] == '.' & lines[i-1][j] == '|') {
            lines[i][j] = '|';
            lines[i+1][j] = '|';
        }
    }
}

int countSplits(char** lines) {
    int splits = 0;
    for (int line = 2; lines[line] != NULL; line += 2) {
        for (int i = 0; lines[line][i] != '\0'; i++) {
            if (lines[line][i] == '^' & lines[line-1][i] == '|') splits++;
        }
    }
    return splits;
}

void freeLines(char** lines) {
    for (int i = 0; lines[i] != NULL; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main() {
    char** lines = readInput();
    processFirstLine(lines);
    for (int i = 2; lines[i] != NULL; i+= 2) {
        processLine(lines, i);
    }
    printf("Total splits: %d\n", countSplits(lines));
    freeLines(lines);
}