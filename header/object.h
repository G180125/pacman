#ifndef OBJECT_H
#define OBJECT_H

#include "ultility.h"
#include "gameimg.h"
#include "framebf.h"
#include "uart0.h"
#include "game.h"
#include "map.h"

#ifndef POINT_H
#define POINT_H
typedef struct
{
    int row;
    int col;
} Point;
#endif // POINT_H

#ifndef PIXEL_POINT_H
#define PIXEL_POINT_H
typedef struct
{
    int x;
    int y;
} Pixel_Position;
#endif

#ifndef SIZE_H
#define SIZE_H
typedef struct
{
    int width;
    int height;
} Size;
#endif

#ifndef SPECIAL_FOODS_H
#define SPECIAL_FOODS_H
typedef struct
{
    int active;
    int freeze_ghosts;
    int reversed;
    int double_score;
    int invisible;
    int speed_up;
    int power_up;
} Special_Foods;
#endif

#ifndef PACMAN_H
#define PACMAN_H
typedef struct
{
    Point point;
    Pixel_Position pixel_position;
    Special_Foods special_foods;
    Size size;
    int current_frame;
    int current_move;
} Pacman;
#endif

#ifndef GHOST_H
#define GHOST_H
typedef struct
{
    Point point;
    Pixel_Position pixel_position;
    Size size;
    Point scatter_position;
    Point target_position;
    int is_move;
    int previous_move;
    int current_frame;
    int status;
} Ghost;
#endif

extern Pacman pacman;
extern Ghost pinky;
extern Ghost blinky;
extern Ghost clyde;
extern Ghost inky;

void move_priority(Ghost *ghost, PriorityQueue (*arr)[]);
void process_next_move(Ghost *ghost, PriorityQueue dis[]);
void draw_pacman(Pacman *pacman);
void draw_pinky(Ghost *pinky);
void draw_blinky(Ghost *blinky);
void draw_clyde(Ghost *clyde);
void draw_inky(Ghost *inky);
void draw_eaten_ghost(Ghost *ghost);
void ghost_turn_around(Ghost *ghost);
void move_ghost(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void move_ghost_execute(Pacman *pacman, Ghost *ghost);
void move_ghost(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void move_ghost_scatter(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void move_ghost_chase(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void move_ghost_frighten(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
int random_move(Ghost *ghost, int direction);
void move_pacman(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky, char c);
void draw_food_after_ghosts_move(Ghost *ghost);

#endif

