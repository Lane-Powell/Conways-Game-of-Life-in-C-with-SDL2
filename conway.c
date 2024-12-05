/* Functions related to Conway's Game of Life and grids */

#include <stdlib.h>
#include <stdio.h>
#include "conway.h"

// n rows, m columns. Interior of alternating zeros and ones with surrounding 'buffer' of zeroes
int** create_alternating_grid(int rows, int columns, int buffer) {
    // Allocate memory for the 2D array
    int** grid = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*)malloc(columns * sizeof(int));
    }

    // Fill with alternating 1s and 0s
    for (int i = buffer; i < rows - buffer; i++) {
        for (int j = buffer; j < columns - buffer; j++) {
            grid[i][j] = ((i + j + 1) % 2) ? 1 : 0;
        }
    }

    // Set the buffer rows and columns to 0
    for (int i = 0; i < buffer; i++) {
        for (int j = 0; j < columns; j++) {
            grid[i][j] = 0;
            grid[rows - 1 - i][j] = 0;
        }
    }
    for (int i = buffer; i < rows - buffer; i++) {
        for (int j = 0; j < buffer; j++) {
            grid[i][j] = 0;
            grid[i][columns - 1 - j] = 0;
        }
    }

    return grid;
}

// Included for debugging:
void print_grid(int** grid, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void free_grid(int** grid, int rows) {
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}


static int count_live_neighbors(int** grid, int rows, int columns, int row, int col) {
    // Helper function to count live neighbors of cell located at grid[row][col]
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int new_row = row + i;
            int new_col = col + j; // Getting index to check
            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < columns) { // Check if in bounds
                count += grid[new_row][new_col];
            }
        }
    }
    return count;
}

void conways_game_of_life(int** grid, int rows, int columns) {
    // Create a temporary grid to store the next generation
     int** temp_grid = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        temp_grid[i] = (int*)malloc(columns * sizeof(int));
    }

    // Apply Game of Life rules
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int live_neighbors = count_live_neighbors(grid, rows, columns, i, j);
            if (grid[i][j] == 1) { // Cell is alive
                if (live_neighbors < 2 || live_neighbors > 3) {
                    temp_grid[i][j] = 0;  // Cell dies
                } else {
                    temp_grid[i][j] = 1;  // Cell survives
                }
            } else {
                if (live_neighbors == 3) { // Cell is dead
                    temp_grid[i][j] = 1;  // Cell is born
                } else {
                    temp_grid[i][j] = 0;  // Cell stays dead
                }
            }
        }
    }

    // Copy the next generation back to the original grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            grid[i][j] = temp_grid[i][j];
        }
    }

    // Free the temporary grid
    for (int i = 0; i < rows; i++) {
        free(temp_grid[i]);
    }
    free(temp_grid);
}