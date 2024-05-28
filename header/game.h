#define FOOD_POINTS 5
#define ROWS 23
#define COLS 22
#define BONUS_MOVES 300
#define REVERSED_TIME 15000
#define FREEZE_GHOST_TIME 10000
#define INVISIBLE_TIME 10000
#define POWER_UP_TIME 10000
#define DOUBLE_SCORE_TIME 10000
#define SPEED_UP_TIME 15000

#ifndef GAME_H
#define GAME_H

#include "object.h"
#include "map.h"
#include "linkedlist.h"
#include "global.h"
#include "timer_and_interrupt.h"

#ifndef POINT_H
#define POINT_H
typedef struct {
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

extern int scatter_mode;
extern int chase_mode;
extern int frighten_mode;
extern int is_all_out_of_house;
extern int total_food;
extern int total_points;
extern int total_special_foods_eaten;
extern int total_ghosts_eaten;
extern int is_all_out_of_house;
extern int total_food;
extern int threshold;
extern int level;
extern int map[ROWS][COLS];	
extern int ghost_speed;
extern int reversed_time;
extern int freeze_ghosts_time;
extern int invisible_time;
extern int power_up_time;
extern int double_score_time;
extern int speed_up_time;
extern Node *head;
extern int game_time;
extern int size;

void draw_map();
void draw_map_preview();
void game(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky);
int is_caught(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky);
int is_eaten(Pacman pacman, Ghost *ghost);
void enable_frighten_mode(Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void disable_frighten_mode(Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void handle_special_food(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);

#endif 

void get_map();
void level_preview();
void display_instruction(int page);
void display_home_screen();
void game_init();
void display_ending_screen();
void display_ending_result(int col, int row);
void display_statistic(int value, int time);
void display_statistic_overall();
void display_rating(int value);