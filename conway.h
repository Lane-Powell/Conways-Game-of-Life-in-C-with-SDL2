int** create_alternating_grid(int rows, int columns, int buffer);
void free_grid(int** grid,  int rows);
void conways_game_of_life(int** grid, int rows, int columns);

// For debugging:
void print_grid(int** grid, int rows, int columns);