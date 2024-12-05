#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 540
#define SCREEN_WIDTH 960
#define CELL_SIZE 10
#define GRID_ROWS (SCREEN_HEIGHT / CELL_SIZE)
#define GRID_COLUMNS (SCREEN_WIDTH / CELL_SIZE)

extern SDL_Renderer *Renderer;

int init__SDL(void);
int init__Window(void);
void kill__Window(void);
void kill__SDL(void);
void draw__binary__grid (int** grid, SDL_Rect cell, int rows, int columns, int cell_size);