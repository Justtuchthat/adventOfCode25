#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// actual input it is 140, test it is 10
#define GRID_SIZE 140

void freeMatrix(int** grid, int size) {
    for (int y = 0; y < size; free(grid[y++])) {}
    free(grid);
}

int** readGrid() {
    int** grid = calloc(GRID_SIZE, sizeof(int*));
    for (int y = 0; y < GRID_SIZE; y++) {
        grid[y] = calloc(GRID_SIZE, sizeof(int));
        for (int x = 0; x < GRID_SIZE; x++) {
            grid[y][x] = (getchar() == '@');
        }
        getchar();
    }
    return grid;
}

void printGrid(int** grid, int gridSize) {
    for (int y = 0; y < gridSize; y++) {
        printf("%d", grid[y][0]);
        for (int x = 1; x < gridSize; x++) {
            printf(" %d", grid[y][x]);
        }
        putchar('\n');
    }
}

int get(int** grid, int x, int y) {
    if (x < 0) return 0;
    if (y < 0) return 0;
    if (x >= GRID_SIZE) return 0;
    if (y >= GRID_SIZE) return 0;
    return grid[y][x];
}

int countAllNeighbors(int** grid) {
    int total = 0;
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (grid[y][x] == 0) continue;
            int neighbors = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i == j & j == 0) continue;
                    if (get(grid, x+i, y+j)) neighbors++;
                }
            }
            if (neighbors < 4) {
                total++;
                grid[y][x] = 2;
            }
        }
    }
    return total;
}

void removePaperRolls(int** grid) {
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            grid[y][x] %= 2;
        }
    }
}

int main() {
    int** grid = readGrid();
    int amount = countAllNeighbors(grid);
    int next = amount;
    while (next) {
        removePaperRolls(grid);
        next = countAllNeighbors(grid);
        amount += next;
    }
    
    freeMatrix(grid, GRID_SIZE);
    printf("Total accessible rols of paper: %d\n", amount);
}