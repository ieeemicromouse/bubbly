#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "maze.h"
#include "hardware.h"

void init_maze(struct cell maze[WIDTH][HEIGHT]) {
    int8_t i;
    int8_t j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            maze[i][j].x = i;
            maze[i][j].y = j;
            maze[i][j].north = NULL;
            maze[i][j].south = NULL;
            maze[i][j].east = NULL;
            maze[i][j].west = NULL;
        }
    }
}

void connect_maze(struct cell maze[WIDTH][HEIGHT]) {
    int8_t i;
    int8_t j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            if (j != HEIGHT-1)
                maze[i][j].north = &(maze[i][j+1]);
            if (j != 0)
                maze[i][j].south = &(maze[i][j-1]);
            if (i != WIDTH-1)
                maze[i][j].east = &(maze[i+1][j]);
            if (i != 0)
                maze[i][j].west = &(maze[i-1][j]);
        }
    }
}

int main(int argc, char* argv[]) {
    struct cell maze[WIDTH][HEIGHT];
    initialize_hardware(argc, argv);
    init_maze(maze);
    connect_maze(maze);

    while (!has_wall(FRONT)) {
        move_forward(1);
    }
    int8_t i;
    for (i = 0; i < 2; i++) {
        turn_right();
        move_forward(2);
    }
    while (has_wall(FRONT)) {
        turn_left();
    }

    finalize_hardware();
    return 0;
}
