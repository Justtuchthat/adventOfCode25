#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 256
#define SPLITTER -1
#define START -2
#define LINE_END -3

long long* readLine() {
    char buffer[MAX_LINE_SIZE];
    char* result = fgets(buffer, MAX_LINE_SIZE, stdin);
    if (result == NULL) return NULL;
    int size = strlen(buffer);
    long long* line = calloc(size+1, sizeof(long long));
    for (int i = 0; i < size+1; i++) {
        if (buffer[i] == '.') line[i] = 0;
        if (buffer[i] == '^') line[i] = SPLITTER;
        if (buffer[i] == 'S') line[i] = START;
        if (buffer[i] == '\n') line[i] = LINE_END;
        if (buffer[i] == '\0') line[i] = LINE_END;
    }
    return line;
}

long long** readInput() {
    long long* buffer[MAX_LINE_SIZE] = {0};
    long long* line = readLine();
    int i;
    for (i = 0; i < MAX_LINE_SIZE; i++) {
        if (line == NULL) break;
        buffer[i] = line;
        line = readLine();
    }
    long long** lines = calloc(i+1, sizeof(long long*));
    memcpy(lines, buffer, i*sizeof(long long*));
    lines[i] = NULL;
    return lines;
}

void processFirstLine(long long** lines) {
    for (int i = 0; lines[0][i] != -3; i++) {
        if (lines[0][i] == START) {
            lines[1][i] = 1;
            break;
        }
    }
}

void printLines(long long** lines) {
    for (int line = 0; lines[line] != NULL; line++) {
        if (lines[line][0]) {
            printf("%02lld", lines[line][0]);
        } else {
            printf("  ");
        }
        for (int i = 1; lines[line][i] != LINE_END; i++) {
            if (lines[line][i]) {
                printf(" %02lld", lines[line][i]);
            } else {
                printf("   ");
            }
        }
        putchar('\n');
    }
}

void processLine(long long** lines, int i) {
    for (int j = 0; lines[i][j] != LINE_END; j++) {
        if (lines[i][j] != SPLITTER && lines[i-1][j] > 0) {
            lines[i][j] += lines[i-1][j];
        }
        if (lines[i][j] == SPLITTER && lines[i-1][j] > 0) {
            lines[i][j-1] += lines[i-1][j];
            lines[i][j+1] += lines[i-1][j];
        }
    }
    for (int j = 0; lines[i][j] != LINE_END; j++) {
        if (lines[i][j] > 0) lines[i+1][j] = lines[i][j];
    }
}

long long countTimelines(long long** lines) {
    int lastLine = 0;
    for (;lines[lastLine+1] != NULL; lastLine++);
    long long totalTimelines = 0;
    for (int i = 0; lines[lastLine][i] != LINE_END; i++) {
        totalTimelines += lines[lastLine][i];
    }
    return totalTimelines;
}

void freeLines(long long** lines) {
    for (int i = 0; lines[i] != NULL; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main() {
    long long** lines = readInput();
    processFirstLine(lines);
    for (int i = 2; lines[i] != NULL; i+= 2) {
        processLine(lines, i);
    }
    printLines(lines);
    printf("Total timelines: %lld\n", countTimelines(lines));
    freeLines(lines);
}