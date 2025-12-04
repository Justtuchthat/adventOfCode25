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
            grid[y][x] = (getchar() == '@'); // Set grid position to 1 if paper roll is present
        }
        getchar(); // Remove newline character from stdin
    }
    return grid;
}

void printGrid(int** grid, int gridSize) {
    for (int y = 0; y < gridSize; y++) {
        printf("%d", grid[y][0]); // Print first character of current row
        for (int x = 1; x < gridSize; x++) {
            printf(" %d", grid[y][x]); // Print aditional characters of row
        }
        putchar('\n'); // Add newline to finish row
    }
}

int get(int** grid, int x, int y) {
    // get Is a function that returns 0 when trying to access out of bounds
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
            if (grid[y][x] == 0) continue; // If there is no paper roll it is not accessible
            int neighbors = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i == j & j == 0) continue; // Center of looking is the roll itself, you are not your own neighbor
                    neighbors += get(grid, x+i, y+j); // Add all rolls to the neighbors count
                }
            }
            if (neighbors < 4) total++; // If less than 4 neighboring rolls increase total count
        }
    }
    return total;
}

int main() {
    int** grid = readGrid();
    int amount = countAllNeighbors(grid);
    freeMatrix(grid, GRID_SIZE); // Always clean up after yourself
    printf("Total accessible rols of paper: %d\n", amount);
}