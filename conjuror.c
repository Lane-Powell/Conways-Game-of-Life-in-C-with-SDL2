/* SDL functions for Cells project */
/* Function names should use double__underscore spacing convention */
/* to disambiguate from other functions in the project */

#include <stdio.h>
#include "conjuror.h"

#define FAILED 0
#define SUCCESS 1

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;

int init__SDL(void) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError() );
		return FAILED;
	}
	return SUCCESS;
}

int init__Window(void) {
	Window = SDL_CreateWindow("Conway Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if (Window == NULL) {
		printf("Window initialization failed. SDL Error: %s\n", SDL_GetError() );
		return FAILED;
	}
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == NULL) {
        printf("Renderer initialization failed. SDL Error: %s\n", SDL_GetError() );
        return FAILED;
    }
	return SUCCESS;
}

// Currently unused except for debugging
// Do not call before kill__SDL unless a new Window/Renderer is created afterwards
void kill__Window(void) {
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
}

void kill__SDL(void) {
    SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void draw__binary__grid (int** grid, SDL_Rect cell, int rows, int columns, int cell_size) {
	// Loop through each cell:
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cell.x = j*cell_size;
			cell.y = i*cell_size;
			cell.w = cell_size;
			cell.h = cell_size;
			// Logic to decide individual cell color:
			if (grid[i][j] == 0) {
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			} else if (grid[i][j] == 1) {
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
			}
			// Draw cell:
			SDL_RenderFillRect(Renderer, &cell);
		}
	}
}