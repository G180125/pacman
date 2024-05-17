#define ROWS 23
#define COLS 22

#ifndef MAP_H
#define MAP_H

#include "gameimg.h"
#include "framebf.h"

#ifndef POINT_H
#define POINT_H
typedef struct {
    int row;
    int col;
} Point;
#endif // POINT_H

typedef struct {
    int is_done;
    int goal;
    char description[100];
} Mission;

typedef struct {
    Mission mission1;
    Mission mission2;
    Mission mission3;
    int scatter_duration;
    int chase_duration;
    int highest_score;
    int map[ROWS][COLS];
    Point gate;
} Map_data;

extern Map_data map_data[];

#endif
