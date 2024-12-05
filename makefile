# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# SDL2 flags and libraries
SDL_FLAGS = -lSDL2main -lSDL2
SDL_INCLUDE = -IC:/usr/include/SDL2
SDL_LIB = -LC:/usr/include/SDL2

# Source files
SRCS = life.c conjuror.c conway.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = test

# Default target
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(SDL_FLAGS) $(SDL_LIB)

# Compiling life.c
life.o: life.c conjuror.h conway.h
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c $<

# Compiling conjuror.c
conjuror.o: conjuror.c conjuror.h
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c $<

# Compiling conway.c
conway.o: conway.c conway.h
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c $<

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean