//------------------------------main.h---------------------
#include "uart0.h"
#include "framebf.h"
#include "gameimg.h"
#include "ultility.h"
#include "queue.h"
#include "image.h"

#define BUFFER_SIZE 256
#define ROWS 23
#define COLS 22
#define MAX_SIZE 500

char buffer[BUFFER_SIZE];
int buffer_index = 0;

typedef struct
{
    int x;
    int y;
} Pixel_Position;

typedef struct
{
    int width;
    int height;
} Size;

typedef struct
{
    Point point;
    Pixel_Position pixel_position;
    Size size;
    int current_frame;
    int current_move;
    unsigned long *frames[7];
} Pacman;

typedef struct
{
    Point point;
    Pixel_Position pixel_position;
    Size size;
    Point scatter_position;
    Point target_position;
    int is_move;
    int previous_move;
    unsigned long *image[1];
} Ghost;

const int SCREEN_WIDTH = 524;
const int SCREEN_HEIGHT = 524;
const int OFFSET = 20;

int y_index = 0;
int x_index = 0;

typedef struct
{
    int total_food;
    int ghost_ability_to_move;
    int score;
    int game_status;
} Game;

// GAME INFO
int scatter_mode = 1;
int chase_mode = 0;
int total_food = 220;
int is_all_out_of_house = 0;
int end_game = 0;

int map[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1},
    {5, 5, 5, 5, 1, 2, 1, 2, 2, 6, 2, 6, 2, 2, 1, 2, 1, 5, 5, 5, 5},
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {5, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 5},
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {5, 5, 5, 5, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 5, 5, 5, 5},
    {5, 5, 5, 5, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 5, 5, 5, 5},
    {1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 6, 2, 6, 2, 2, 2, 2, 1, 2, 2, 2, 1},
    {1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 1, 1},
    {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void handle_delete();
void handle_enter();
void execute_command(char *command);
void move_image(char c, int flag);
void draw_map();
void draw_pacman(Pacman *pacman);
void move_pacman(Pacman *pacman, char c);
void draw_food_after_ghosts_move(Ghost *ghost);
void game(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky);
int is_caught(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky);
void move_ghost_execute(Ghost *ghost);
void move_ghost(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);

void main()
{
    // set up serial console
    uart_init();
    // say hello
    uart_puts("\n\nHello World!\n");
    // Initialize frame buffer
    framebf_init();
    // Draw something on the screen
    // drawStringARGB32(50, 50, "Nguyen Vi Phi Long - s3904632", 0x0000BB00);
    // drawStringARGB32(100, 100, "Nguyen Minh Hung - s3924473", 0x00AA0000);
    // drawStringARGB32(150, 150, "Le Tran Minh Trung - s3927071", 0x000000CC);
    // drawStringARGB32(200, 200, "Huynh Tan Phat - s3926661", 0x00FFFF00);

    uart_puts("\nGroup7> ");

    Pacman pacman = {
        {1, 1},
        {36, 35},
        {20, 20},
        0,
        -1,
        {pacman_frame_0,
         pacman_frame_1,
         pacman_frame_2,
         pacman_frame_3,
         pacman_frame_4,
         pacman_frame_5,
         pacman_frame_6}};

    Ghost pinky = {
        {10, 9},
        {237, 252},
        {22, 20},
        {-4, 2},
        {0, 0},
        0,
        -1,
        {pinky_frame}};

    Ghost blinky = {
        {10, 11},
        {287, 252},
        {22, 20},
        {-4, 20},
        {0, 0},
        0,
        -1,
        {blinky_frame}};

    Ghost clyde = {
        {11, 9},
        {237, 275},
        {22, 20},
        {23, 0},
        {0, 0},
        0,
        -1,
        {clyde_frame}};

    Ghost inky = {
        {11, 11},
        {287, 275},
        {22, 20},
        {23, 22},
        {0, 0},
        0,
        -1,
        {inky_frame}};

        game(pacman, pinky, blinky, clyde, inky);

    // while (1)
    // {
    //     // drawImageARGB32(0, 0, x_index, y_index, image);
    //     // int flag = 1;

    //     // while(flag == 1){
    //     //     char c1 = getUart();
    //     //     move_image(c1, flag);
    //     // }

    // }
}

void handle_delete()
{
    // Move buffer index back
    buffer_index--;

    // Erase last character from console
    uart_puts("\b \b");

    // Shift characters after deleted character one position to the left
    for (int i = buffer_index; i < BUFFER_SIZE - 1; i++)
    {
        buffer[i] = buffer[i + 1];
    }

    // Null terminate the last character in the buffer
    buffer[BUFFER_SIZE - 1] = '\0';
}

void move_image(char c, int flag)
{
    if (c == 's')
    {
        if (y_index + SCREEN_HEIGHT + OFFSET <= IMAGE_HEIGHT)
        {
            y_index += OFFSET;
            clearScreen();
            drawImageARGB32(0, 0, x_index, y_index, image);
        }
    }
    else if (c == 'w')
    {
        if (y_index >= OFFSET)
        {
            y_index -= OFFSET;
            clearScreen();
            drawImageARGB32(0, 0, x_index, y_index, image);
        }
    }
    else if (c == 'd')
    {
        if (x_index + SCREEN_WIDTH + OFFSET <= IMAGE_WIDTH)
        {
            x_index += OFFSET;
            clearScreen();
            drawImageARGB32(0, 0, x_index, y_index, image);
        }
    }
    else if (c == 'a')
    {
        if (x_index >= OFFSET)
        {
            x_index -= OFFSET;
            clearScreen();
            drawImageARGB32(0, 0, x_index, y_index, image);
        }
    }
    else
    {
        flag = 1;
    }
}

void move_pacman(Pacman *pacman, char c)
{
    int pacman_old_x_position = pacman->pixel_position.x;
    int pacman_old_y_position = pacman->pixel_position.y;
    if (c == 's')
    {
        // if the pacman is in the last row
        // it cannot go down any more
        if (pacman->point.row == 22)
        {
            return;
        }

        // if the under position is a wall
        // pacman cannot move down
        if (map[pacman->point.row + 1][pacman->point.col] == 1)
        {
            return;
        }

        // clearing the pacman's old position in the map
        map[pacman->point.row][pacman->point.col] = 0;

        // move to the new position
        // increasing the row
        pacman->point.row++;
        pacman->pixel_position.y += 24;
        pacman->current_move = 2;
    }
    else if (c == 'w')
    {
        // if the pacman is in the first row
        // it cannot go down any more
        if (pacman->point.row <= 1)
        {
            return;
        }

        // if the above position is a wall
        // pacman cannot move down
        if (map[pacman->point.row - 1][pacman->point.col] == 1)
        {
            return;
        }

        // clearing the pacman's old position in the map
        map[pacman->point.row][pacman->point.col] = 0;

        // move to the new position
        // decreasing the row
        pacman->point.row--;
        pacman->pixel_position.y -= 24;
        pacman->current_move = 0;
    }
    else if (c == 'd')
    {
        // if the pacman is in the last collumn
        // it cannot go right any more
        if (pacman->point.col == 21)
        {
            return;
        }

        // if the right position is a wall
        // pacman cannot move right
        if (map[pacman->point.row][pacman->point.col + 1] == 1)
        {
            return;
        }

        // clearing the pacman's old position in the map
        map[pacman->point.row][pacman->point.col] = 0;

        // move to the new position
        // increasing the collumn
        pacman->point.col++;
        pacman->pixel_position.x += 25;
        pacman->current_move = 3;
    }
    else if (c == 'a')
    {
        // if the pacman is in the first collumn
        // it cannot go left any more
        if (pacman->point.col == 0)
        {
            return;
        }

        // if the left position is a wall
        // pacman cannot move left
        if (map[pacman->point.row][pacman->point.col - 1] == 1)
        {
            return;
        }

        // clearing the pacman's old position in the map
        map[pacman->point.row][pacman->point.col] = 0;

        // move to the new position
        // decreasing the collumn
        pacman->point.col--;
        pacman->pixel_position.x -= 25;
        pacman->current_move = 1;
    }

    // if the new position has a food
    if (map[pacman->point.row][pacman->point.col] == 2)
    {
        // decrease the total food
        total_food -= 1;
    }

    // mark the new position of pacman on the map
    map[pacman->point.row][pacman->point.col] = 4;

    // clearing the old pacman in the screen
    clearObject(pacman_old_x_position, pacman_old_y_position, pacman->size.width, pacman->size.height);
}

void draw_food_after_ghosts_move(Ghost *ghost)
{
    // clearing the old ghosts in the screen
    // draw back the foods
    clearObject(ghost->pixel_position.x, ghost->pixel_position.y, ghost->size.width, ghost->size.height);
    if (map[ghost->point.row][ghost->point.col] == 2 || map[ghost->point.row][ghost->point.col] == 6)
    {
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 24, 10 + ghost->point.row * 24 + 23, 0xFF000000, 1);
        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 6;
        int food_end_x = (2 * ghost->pixel_position.x + 25) / 2 + 2;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 3;
        int food_end_y = (2 * ghost->pixel_position.y + 24) / 2 + 3;
        drawRectARGB32(food_start_x, food_start_y, food_end_x, food_end_y, 0xFFFFAA88, 1);
    }
    else
    {
        drawRectARGB32(9 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 25, 10 + ghost->point.row * 24 + 23, 0xFF000000, 1);
    }
}

void draw_map()
{
    // loop through the 2D map
    for (int i = 0; i < 23; ++i)
    {
        for (int j = 0; j < 22; ++j)
        {
            // calculate x1, y1, x2, y2 of every box in the map
            // each box has a width of 25 and height of 24
            int start_x = 10 + (25 * j);
            int end_x = start_x + 25;
            int start_y = 10 + (24 * i);
            int end_y = start_y + 24;

            if (map[i][j] == 1)
            { // if this is a wall
                // draw a bule rectangal
                drawRectARGB32(start_x, start_y, end_x, end_y, 0x000000CC, 2);
            }
            else if (map[i][j] == 2 || map [i][j] == 6)
            { // if this is a road
                // draw a black rectangle
                //drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                // draw the food
                // the food is place in the middle of the reactangle
                // the food has a width of 8 and a height of 6
                int food_start_x = (start_x + end_x) / 2 - 4;
                int food_end_x = (start_x + end_x) / 2 + 4;
                int food_start_y = (start_y + end_y) / 2 - 3;
                int food_end_y = (start_y + end_y) / 2 + 3;
                drawRectARGB32(food_start_x, food_start_y, food_end_x, food_end_y, 0xFFFFAA88, 1);
            }
            else
            { // outside maze zone
                // drawing a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);
            }
        }
    }
}

void draw_pacman(Pacman *pacman)
{
    // Define the duration (in milliseconds) between each frame update
    const unsigned int frame_duration_ms = 2000;

    // Update the frame
    if (pacman->current_frame < 6)
    {
        pacman->current_frame++;
    }
    else
    { // reset the frame
        pacman->current_frame = 0;
    }

    set_wait_timer(1, frame_duration_ms);

    // Animate the pacman
    // Delete the old frame
    // Draw the current frame
    clearObject(pacman->pixel_position.x, pacman->pixel_position.y, pacman->size.width, pacman->size.height);
    drawObjectARGB32(pacman->pixel_position.x, pacman->pixel_position.y, pacman->size.width, pacman->size.height, pacman->frames[pacman->current_frame]);

    set_wait_timer(0, frame_duration_ms);
}

void draw_ghost(Ghost *ghost)
{
    // drawCircleARGB32(ghost_1_x_position + (GHOST_WIDTH / 2), ghost_1_y_position + (GHOST_HEIGHT /2), ghost_radar_radius);
    drawObjectARGB32(ghost->pixel_position.x, ghost->pixel_position.y, ghost->size.width, ghost->size.height, ghost->image[0]);
}

void game(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky)
{
    // draw the map
    draw_map();
    int cnt = 0;

    while (1)
    {
        set_wait_timer(1, 10);
        // animate the pacman
        draw_pacman(&pacman);

        // break the loop if the game is end.
        if (end_game == 1)
        {
            wait_msec(1000);
            break;
        }

        if (pinky.is_move)
        {
            wait_msec(100000);
            move_ghost(&pacman, &pinky, &blinky, &clyde, &inky);
        }
        draw_ghost(&pinky);
        draw_ghost(&blinky);
        draw_ghost(&clyde);
        draw_ghost(&inky);

        if (is_caught(pacman, pinky, blinky, clyde, inky))
        {
            uart_puts("\nGame Over");
            end_game = 1;
        }

        // if there is an input key
        if (uart_isReadByteReady() == 0)
        {
            // get the input and execute
            char c = uart_getc();
            move_pacman(&pacman, c);
            pinky.is_move = 1;
        }

        // if all the foods are eaten, dislay winning message and end the game.
        if (total_food == 0)
        {
            uart_puts("\nWINNER! WINNER! CHICKEN! DINNER!");
            end_game = 1;
        }

        // Stop counting time and polling to switch state if all the ghost leaves the house
        if (is_all_out_of_house)
        {
            set_wait_timer(0, 10);
            cnt++;
            // After 7s, change to chase mode
            if (cnt % 70 == 0 && scatter_mode)
            {
                scatter_mode = 0;
                chase_mode = 1;
                cnt = 0;
            }
            else if (cnt % 200 == 0 && chase_mode)
            { // After 20s, back to scatter mode
                scatter_mode = 1;
                chase_mode = 0;
                cnt = 0;
            }
        }
        else
        { // The player not start the game or all the ghosts not leave the house yet
            set_wait_timer(0, 10);
        }
    }
}

int is_caught(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky)
{
    return (pacman.point.row == pinky.point.row && pacman.point.col == pinky.point.col) ||
           (pacman.point.row == blinky.point.row && pacman.point.col == blinky.point.col) ||
           (pacman.point.row == clyde.point.row && pacman.point.col == clyde.point.col) ||
           (pacman.point.row == inky.point.row && pacman.point.col == inky.point.col);
}

void move_ghost(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    if (scatter_mode)
    {
        if (!is_all_out_of_house)
        {
            move_ghost_execute(pinky);
            if (distance_square(blinky->point.row, blinky->point.col, pinky->point.row, pinky->point.col) > 30)
            {
                blinky->is_move = 1;
            }
            if (distance_square(blinky->point.row, blinky->point.col, clyde->point.row, clyde->point.col) > 30 && !clyde->is_move)
            {
                clyde->is_move = 1;
                clyde->scatter_position.row = blinky->scatter_position.row;
                clyde->scatter_position.col = blinky->scatter_position.col;
            }
            if (distance_square(clyde->point.row, clyde->point.col, inky->point.row, inky->point.col) > 10 && !inky->is_move)
            {
                inky->is_move = 1;
                inky->scatter_position.row = blinky->scatter_position.row;
                inky->scatter_position.col = blinky->scatter_position.col;
            }
            if (blinky->is_move)
            {
                move_ghost_execute(blinky);
            }
            if (clyde->is_move)
            {
                move_ghost_execute(clyde);
                if (distance_square(clyde->point.row, clyde->point.col, blinky->scatter_position.row, blinky->scatter_position.col) < 200)
                {
                    clyde->scatter_position.row = 24;
                    clyde->scatter_position.col = 0;
                }
            }
            if (inky->is_move)
            {
                move_ghost_execute(inky);
                if (distance_square(inky->point.row, inky->point.col, blinky->scatter_position.row, blinky->scatter_position.col) < 200)
                {
                    inky->scatter_position.row = 23;
                    inky->scatter_position.col = 22;
                    is_all_out_of_house = 1;
                }
            }
        }
        else
        {
            move_ghost_execute(pinky);
            move_ghost_execute(blinky);
            move_ghost_execute(clyde);
            move_ghost_execute(inky);
        }
    }
    else
    {
        // Pinky -> 4 tiles a head pacman
        switch (pacman->current_move)
        {
        case 0:
            pinky->target_position.row = pacman->point.row - 4;
            pinky->target_position.col = pacman->point.col - 4;
            break;

        case 1:
            pinky->target_position.row = pacman->point.row;
            pinky->target_position.col = pacman->point.col - 4;
            break;

        case 2:
            pinky->target_position.row = pacman->point.row + 4;
            pinky->target_position.col = pacman->point.col;
            break;

        default:
            pinky->target_position.row = pacman->point.row;
            pinky->target_position.col = pacman->point.col + 4;
            break;
        }
        move_ghost_execute(pinky);

        // Blinky -> Follow pacman
        blinky->target_position.row = pacman->point.row;
        blinky->target_position.col = pacman->point.col;
        move_ghost_execute(blinky);

        // Clyde -> outside 8 tiles around pacman -> chase like blinky; otherwise, scatter
        int distance_to_pacman = distance_square(clyde->point.row, clyde->point.col, pacman->point.row, pacman->point.col);
        if (distance_to_pacman > 64)
        {
            clyde->target_position.row = pacman->point.row;
            clyde->target_position.col = pacman->point.col;
        }
        else
        {
            clyde->target_position.row = clyde->scatter_position.row;
            clyde->target_position.col = clyde->scatter_position.col;
        }
        move_ghost_execute(clyde);

        // Inky
        Point intermidiate;
        switch (pacman->current_move)
        {
        case 0:
            intermidiate.row = pacman->point.row - 2;
            intermidiate.col = pacman->point.col - 2;
            break;

        case 1:
            intermidiate.row = pacman->point.row;
            intermidiate.col = pacman->point.col - 2;
            break;

        case 2:
            intermidiate.row = pacman->point.row + 2;
            intermidiate.col = pacman->point.col;
            break;

        default:
            intermidiate.row = pacman->point.row;
            intermidiate.col = pacman->point.col + 2;
            break;
        }
        inky->target_position.row = 2 * intermidiate.row - blinky->point.row;
        inky->target_position.col = 2 * intermidiate.col - blinky->point.col;
        move_ghost_execute(inky);
    }
}

void move_priority(Ghost *ghost, PriorityQueue (*arr)[])
{
    int up_dis, left_dis, down_dis, right_dis;
    if (scatter_mode)
    {
        up_dis = distance_square(ghost->point.row - 1, ghost->point.col, ghost->scatter_position.row, ghost->scatter_position.col);
        left_dis = distance_square(ghost->point.row, ghost->point.col - 1, ghost->scatter_position.row, ghost->scatter_position.col);
        down_dis = distance_square(ghost->point.row + 1, ghost->point.col, ghost->scatter_position.row, ghost->scatter_position.col);
        right_dis = distance_square(ghost->point.row, ghost->point.col + 1, ghost->scatter_position.row, ghost->scatter_position.col);
    }
    else
    {
        up_dis = distance_square(ghost->point.row - 1, ghost->point.col, ghost->target_position.row, ghost->target_position.col);
        left_dis = distance_square(ghost->point.row, ghost->point.col - 1, ghost->target_position.row, ghost->target_position.col);
        down_dis = distance_square(ghost->point.row + 1, ghost->point.col, ghost->target_position.row, ghost->target_position.col);
        right_dis = distance_square(ghost->point.row, ghost->point.col + 1, ghost->target_position.row, ghost->target_position.col);
    }

    // Initialize the first element of the struct array
    (*arr)[0].distance = up_dis;
    (*arr)[0].direction = 0;

    // Initialize the first element of the struct array
    (*arr)[1].distance = left_dis;
    (*arr)[1].direction = 1;

    // Initialize the first element of the struct array
    (*arr)[2].distance = down_dis;
    (*arr)[2].direction = 2;

    // Initialize the first element of the struct array
    (*arr)[3].distance = right_dis;
    (*arr)[3].direction = 3;

    bubbleSort(*arr, 4);
}

void process_next_move(Ghost *ghost, PriorityQueue dis[])
{
    for (int i = 3; i >= 0; i--)
    {
        if (dis[i].direction == 0)
        {
            if (ghost->previous_move != 2 && ghost->point.row > 1 && map[ghost->point.row - 1][ghost->point.col] != 1 &&
                map[ghost->point.row][ghost->point.col] != 6)
            {
                // move to the new position
                // increasing the row
                ghost->point.row -= 1;
                ghost->pixel_position.y -= 24;

                // update the previous
                ghost->previous_move = 0;
                return;
            }
        }

        if (dis[i].direction == 1)
        {
            if (ghost->previous_move != 3 && ghost->point.col > 0 && map[ghost->point.row][ghost->point.col - 1] != 1)
            {
                // move to the new position
                // decreasing the collumn
                ghost->point.col -= 1;
                ghost->pixel_position.x -= 25;

                // update the previous
                ghost->previous_move = 1;
                return;
            }
        }

        if (dis[i].direction == 2)
        {
            if (ghost->previous_move != 0 && ghost->point.row < 23 && map[ghost->point.row + 1][ghost->point.col] != 1)
            {
                // move to the new position
                // increasing the row
                ghost->point.row += 1;
                ghost->pixel_position.y += 24;

                // update the previous
                ghost->previous_move = 2;
                return;
            }
        }
        if (dis[i].direction == 3)

        {
            if (ghost->previous_move != 1 && ghost->point.col < 22 && map[ghost->point.row][ghost->point.col + 1] != 1)
            {
                // move to the new position
                // increasing the collumn
                ghost->point.col += 1;
                ghost->pixel_position.x += 25;

                // update the previous
                ghost->previous_move = 3;
                return;
            }
        }
    }
}

void move_ghost_execute(Ghost *ghost)
{
    // clearing the old ghost in the screen
    // draw back the food if there is one
    draw_food_after_ghosts_move(ghost);

    PriorityQueue descending_dis[4];

    // Find and sort the distance from surrounding tiles to the target (by distance and priority of directions)
    move_priority(ghost, &descending_dis);

    process_next_move(ghost, descending_dis);
}
