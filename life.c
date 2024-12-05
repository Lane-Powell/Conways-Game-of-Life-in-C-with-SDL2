// SDL2 implementation of Conway's Game of Life

// Conway's Game of Life is a cellular automaton that is played on a 2D square grid.
// Each square (or "cell") on the grid can be either alive 1 or dead 0.
// They evolve according to the following rules:

//     Any live cell with fewer than two live neighbours dies (referred to as underpopulation).
//     Any live cell with more than three live neighbours dies (referred to as overpopulation).
//     Any live cell with two or three live neighbours lives, unchanged, to the next generation.
//     Any dead cell with exactly three live neighbours comes to life.

#include <stdio.h>
#include <stdlib.h>
#include "conjuror.h"
#include "conway.h"

#define HALT 0
#define CONTINUE 1

#define BUFFER 8

#define DELAY 1000	// milliseconds between each step of simulation

int main_loop(int** Grid, int max_generations);

int main(int argc, char* args[]) {
	if ( !init__SDL() ) {
		return 1;
	}

	int max_generations;
	printf("Conway's Game of Life\n");
	printf("Enter max generations for simulation: ");
	scanf("%d", &max_generations);

    int** Grid = create_alternating_grid(GRID_ROWS, GRID_COLUMNS, BUFFER);
    if (Grid == NULL) {
        fprintf(stderr, "Grid creation failed\n");
        return 1;
    }

	printf("Running simulation in 3 seconds...\n");
	SDL_Delay(3000);

	if ( !init__Window() ) {
		return 1;
	}

	while ( main_loop(Grid, max_generations) ) {
		SDL_Delay(DELAY);
	}
    
    // Clean up when done:
    free_grid(Grid, GRID_ROWS);
    kill__SDL();

    return 0;
}


int main_loop(int** Grid, int max_generations) {
	static int generation = 0;

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			return HALT;
		}
	}
	
	SDL_Rect cell; // Represents generic cell in Grid for drawing purposes
	// Clear window to white and reset at beginning of each loop:
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderClear(Renderer);

	if (generation == 0) {
		// Draw initial state:
		draw__binary__grid(Grid, cell, GRID_ROWS, GRID_COLUMNS, CELL_SIZE);
		SDL_RenderPresent(Renderer);
	} else {
		// Update state according to Conway logic:
		conways_game_of_life(Grid, GRID_ROWS, GRID_COLUMNS);
		// Draw Grid:
		draw__binary__grid(Grid, cell, GRID_ROWS, GRID_COLUMNS, CELL_SIZE);
		// Update window:
		SDL_RenderPresent(Renderer);

	}

	generation++;
	if (generation >= max_generations) {
		return HALT;
	}
	return CONTINUE;
}