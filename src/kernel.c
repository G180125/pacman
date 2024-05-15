//------------------------------main.h---------------------
#include "uart0.h"
#include "framebf.h"
#include "gameimg.h"
#include "ultility.h"
#include "queue.h"
#include "image.h"

#define ROWS 23
#define COLS 22
#define FOOD_POINTS 5
#define MAX_SIZE 500
#define preText "Group7> "
char *buffer = "";    // buffer string for input
int buffer_index = 0; // index for buffer string
int case_one = 0;     // flag for case 1 (image viewer)
int restart_flag = 0; // restart flag for game
int threshold = 0;    // goal to win the game
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
    int active;
    int freeze_ghosts;
    int reversed;
    int double_score;
    int invisible;
    int shield;
    int power_up;
} Special_Foods;

typedef struct
{
    Point point;
    Pixel_Position pixel_position;
    Special_Foods special_foods;
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
    int status;
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
Pacman pacman = {
    {1, 1},
    {36, 35},
    {0, 0, 0, 0, 0, 0, 0},
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
    0,
    0,
    {pinky_frame}};

Ghost blinky = {
    {10, 11},
    {287, 252},
    {22, 20},
    {-4, 20},
    {0, 0},
    0,
    0,
    0,
    {blinky_frame}};

Ghost clyde = {
    {11, 9},
    {237, 275},
    {22, 20},
    {23, 0},
    {0, 0},
    0,
    0,
    0,
    {clyde_frame}};

Ghost inky = {
    {11, 11},
    {287, 275},
    {22, 20},
    {23, 22},
    {0, 0},
    0,
    0,
    0,
    {inky_frame}};
// GAME INFO
int scatter_mode = 1;
int chase_mode = 0;
int frighten_mode = 0;
int total_food = 0;
int total_points = 0;
int total_special_foods_eaten = 0;
int total_ghosts_eaten = 0;
int is_all_out_of_house = 0;
int end_game = 0;
Point gate = {9, 10};

int original_map[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 4, 9, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 12, 1},
    {1, 2, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1},
    {-1, -1, -1, -1, 1, 2, 1, 7, 2, 3, 2, 3, 2, 2, 1, 2, 1, -1, -1, -1, -1},
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 0, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {5, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 5},
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 0, 0, 0, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {-1, -1, -1, -1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, -1, -1, -1, -1},
    {1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 12, 2, 2, 1, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 1, 2, 2, 12, 1},
    {1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 1, 1},
    {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int map[ROWS][COLS];

//-1: Outside the maze
// 0: Empty road
// 1: Wall
// 2: Normal Food
// 3: Special Tiles
// 4: Pacman
// 5: Teleport Gate
// 6: Freeze Ghosts Food (Freeze the ghosts for 15 seconds)
// 7: Reverse Food (Make the pacman moved in the opposite direction than the user input for 15 seconds)
// 8: Double-Score Food (All the foods eaten will score double for 30 seconds)
// 9: Invisible Food (The ghost can not target the pacman for 15 seconds) //ghost stage 1 only
// 10: Shield Food (The ghost can not get close to the pacman for 30 seconds)
// 11: Random Effect Food (Trigger a random effect of the above food)

void move_image(char c, int flag);
void draw_map();
void draw_pacman(Pacman *pacman);
void move_pacman(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky, char c);
void draw_food_after_ghosts_move(Ghost *ghost);
void game(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky);
int is_caught(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky);
int is_eaten(Pacman pacman, Ghost *ghost);
void draw_ghost(Ghost *ghost);
void move_ghost_execute(Pacman *pacman, Ghost *ghost);
void move_ghost(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void move_ghost_scatter(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void move_ghost_chase(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void move_ghost_frighten(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
int random_move(Ghost *ghost, int direction);
void ghost_turn_around(Ghost *ghost);
void enable_frighten_mode(Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void intro();
void clear();
void process(char *input);
void handle_special_food(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky);
void display_ending_screen();
void display_ending_result(int col, int row);
void display_statistic(int statistic, int time);
void main()
{
    // set up serial console
    uart_init();
    // say hello
    uart_puts("\n\nWELCOME TO GROUP 7 BARE OS, CHECK THE MONITOR FOR INSTRUCTION\n");
    // Initialize frame buffer
    framebf_init();
    intro();

    uart_puts("\n" preText);

    while (1)
    {
        // read each char
        char c = uart_getc();
        if (c == 8) // if character is backspace
        {

            if (buffer_index > 0)
            {
                deleteChar();

                *(buffer + buffer_index) = '\0'; // endline
                buffer_index--;
            }
        }
        else if (c == 10) // if character is endline
        {
            ///////////////
            *(buffer + buffer_index) = '\0'; // endline
            process(buffer);                 // Input processing
            ///////////////////////////
            uart_puts("\n" preText);
            for (int i = 0; i < buffer_index; i++) // Clear the the buffer
            {
                buffer[i] = ' ';
            }
            buffer_index = 0;
        }

        else
        {
            uart_sendc(c); // send back to terminal
            *(buffer + buffer_index) = c;
            buffer_index++;
        }
    }
}

void displayNumber(int x, int y, int offset, char *input, unsigned int attr)
{
    // uart_puts("Input in display number: ");
    int offset_temp = offset;
    int count = 1;
    for (int i = string_length(input) - 1; i >= 0; i--)
    {
        drawCharARGB32(x + offset_temp * count, y, input[i], attr);
        count++;
    }
}

void intro()
{
    clearScreen();

    // Draw something on the screen
    drawStringARGB32(0, 50, "Nguyen Vi Phi Long - s3904632", 0x0000BB00);
    drawStringARGB32(0, 100, "Nguyen Minh Hung - s3924473", 0x00AA0000);
    drawStringARGB32(300, 50, "Le Tran Minh Trung - s3927071", 0x000000CC);
    drawStringARGB32(300, 100, "Huynh Tan Phat - s3926661", 0x00FFFF00);
    drawStringARGB32(150, 300, "Press 1 for Image Viewing", 0x00FFFFFF);
    drawStringARGB32(150, 400, "Press 2 for Video Watching", 0xF2a08B);
    drawStringARGB32(150, 500, "Press 3 for Gaming", 0x00FFFF00);
}

void process(char *input)
{
    if (stringcompare(buffer, "exit") == 0)
    {
        intro();
        restart_flag = 0;
    }
    //////////////////////////////////////////////////////////////////
    else if (stringcompare(buffer, "1") == 0)
    {
        uart_puts("\n");

        clearScreen();
        case_one = 1;
        buffer_index = 0;
        buffer = " "; // reset buffer
        uart_puts("Image Viewer activated, type Exit anytime to exit out of this feature");

        while (case_one == 1)
        {
            uart_puts("\n" preText);
            drawImageARGB32(0, 0, x_index, y_index, image);
            int flag = 1;

            while (flag == 1)
            {
                char c1 = getUart();
                if (c1 == 10)
                {
                    *(buffer + buffer_index) = '\0';        // endline
                    if (stringcompare(buffer, "exit") == 0) // clean up here
                    {

                        clearScreen();
                        case_one = 0;
                        flag = 0;

                        uart_puts("\nThank you for viewing our image\n");
                        intro();

                        break;
                    }
                    else
                    {
                        uart_puts("\nError: Unidentified command");
                    }
                }
                else
                {
                    move_image(c1, flag);
                    if (c1 != 'w' && c1 != 'a' && c1 != 's' && c1 != 'd')
                    {
                        uart_sendc(c1); // send back to terminal
                        *(buffer + buffer_index) = c1;
                        buffer_index++;
                    }
                }
            }
        }
    }

    ///////////////////////////////////////////////////////////////
    else if (stringcompare(buffer, "3") == 0 || restart_flag == 1)
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int k = 0; k < COLS; k++)
            {
                map[i][k] = original_map[i][k];
            }
        }
        //////////////////////////////////////
        clearScreen();

        uart_puts("\nGame activated\n");

        scatter_mode = 1;
        chase_mode = 0;
        frighten_mode = 0;
        total_food = 0;
        total_points = 0;
        total_ghosts_eaten = 0;
        total_special_foods_eaten = 0;
        is_all_out_of_house = 0;
        end_game = 0;

        game(pacman, pinky, blinky, clyde, inky);
        restart_flag = 1;
        uart_puts("\n Type exit to exit out of the game, any button to replay the game");
    }

    else if (stringcompare(buffer, "clear") == 0)
    {
        clear();
    }
    else
    {
        uart_puts("\nError: Unidentified command");
    }
}

void clear()
{
    uart_puts("\e[1;1H\e[2J"); // clear
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

void move_pacman(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky, char c)
{

    int pacman_old_x_position = pacman->pixel_position.x;
    int pacman_old_y_position = pacman->pixel_position.y;

    // Check if Pacman is reversed
    if (pacman->special_foods.reversed)
    {
        // Reverse the direction based on user input index
        if (c == 's')
        {
            c = 'w'; // Reverse 's' to 'w'
        }
        else if (c == 'w')
        {
            c = 's'; // Reverse 'w' to 's'
        }
        else if (c == 'a')
        {
            c = 'd'; // Reverse 'a' to 'd'
        }
        else if (c == 'd')
        {
            c = 'a'; // Reverse 'd' to 'a'
        }
    }

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
        // uart_puts("Points remaining: ");
        // uart_dec(total_food);
        // uart_puts("\n");
        char *str_total_points = "";
        displayNumber(850, 600, 10, str_total_points, 0x000000);
        // decrease the total food
        total_food -= 1;
        if (pacman->special_foods.active && pacman->special_foods.double_score)
        {
            total_points += FOOD_POINTS * 2;
        }
        else
        {
            total_points += FOOD_POINTS;
        }

        copyString(str_total_points, numDisplay(total_points));

        displayNumber(850, 600, 10, str_total_points, 0xFFFFFF);
    }
    // if the pacman has eaten a freeze ghosts food
    else if (map[pacman->point.row][pacman->point.col] == 6)
    {
        pacman->special_foods.active++;
        pacman->special_foods.freeze_ghosts = 1;
        total_special_foods_eaten++;
    }
    // if the pacman has eaten a reversed food
    else if (map[pacman->point.row][pacman->point.col] == 7)
    {
        pacman->special_foods.active++;
        pacman->special_foods.reversed = 1;
        total_special_foods_eaten++;
    }
    // if the pacman has eaten a invisible food
    else if (map[pacman->point.row][pacman->point.col] == 9)
    {
        pacman->special_foods.active++;
        pacman->special_foods.invisible = 1;
        total_special_foods_eaten++;
    }
    // if the pacman has eaten a power_up food
    else if (map[pacman->point.row][pacman->point.col] == 12)
    {
        pacman->special_foods.active++;
        pacman->special_foods.power_up = 1;
        total_special_foods_eaten++;
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
    if (map[ghost->point.row][ghost->point.col] == 2 || map[ghost->point.row][ghost->point.col] == 3)
    {
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 24, 10 + ghost->point.row * 24 + 23, 0xFF000000, 1);
        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 6;
        int food_end_x = (2 * ghost->pixel_position.x + 25) / 2 + 2;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 3;
        int food_end_y = (2 * ghost->pixel_position.y + 24) / 2 + 3;
        drawRectARGB32(food_start_x, food_start_y, food_end_x, food_end_y, 0xFFFFAA88, 1);
    }
    else if (map[ghost->point.row][ghost->point.col] == 6)
    { // freeze ghost
        // draw a black rectangle
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 23, 10 + ghost->point.row * 24 + 22, 0xFF000000, 1);
        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 8;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 8;
        drawObjectARGB32(food_start_x, food_start_y, 16, 16, freeze_ghosts_food);
    }
    else if (map[ghost->point.row][ghost->point.col] == 7)
    { // reversed food
        // draw a black rectangle
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 23, 10 + ghost->point.row * 24 + 22, 0xFF000000, 1);

        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 8;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 8;
        drawObjectARGB32(food_start_x, food_start_y, 16, 16, reverse_food);
    }
    else if (map[ghost->point.row][ghost->point.col] == 8)
    { // double score
        // draw a black rectangle
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 23, 10 + ghost->point.row * 24 + 22, 0xFF000000, 1);

        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 8;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 8;
        drawObjectARGB32(food_start_x, food_start_y, 16, 16, double_score_food);
    }
    else if (map[ghost->point.row][ghost->point.col] == 9)
    { // invisible food
        // draw a black rectangle
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 23, 10 + ghost->point.row * 24 + 22, 0xFF000000, 1);

        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 8;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 8;
        drawObjectARGB32(food_start_x, food_start_y, 16, 16, invisible_food);
    }
    else if (map[ghost->point.row][ghost->point.col] == 10)
    { // shield food
        // draw a black rectangle
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 23, 10 + ghost->point.row * 24 + 22, 0xFF000000, 1);

        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 8;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 8;
        drawObjectARGB32(food_start_x, food_start_y, 16, 16, shield_food);
    }
    else if (map[ghost->point.row][ghost->point.col] == 11)
    { // random effect food
        // draw a black rectangle
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 23, 10 + ghost->point.row * 24 + 22, 0xFF000000, 1);

        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 8;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 8;
        drawObjectARGB32(food_start_x, food_start_y, 16, 16, random_effect_food);
    }
    else if (map[ghost->point.row][ghost->point.col] == 12)
    { // power food
        // draw a black rectangle
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 23, 10 + ghost->point.row * 24 + 22, 0xFF000000, 1);

        int food_start_x = (2 * ghost->pixel_position.x + 25) / 2 - 8;
        int food_start_y = (2 * ghost->pixel_position.y + 24) / 2 - 8;
        drawObjectARGB32(food_start_x, food_start_y, 16, 16, power_food);
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
            else if (map[i][j] == 2 || map[i][j] == 3)
            { // if this is a road
                // draw a black rectangle
                // drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                // draw the food
                // the food is place in the middle of the reactangle
                // the food has a width of 8 and a height of 6
                int food_start_x = (start_x + end_x) / 2 - 4;
                int food_end_x = (start_x + end_x) / 2 + 4;
                int food_start_y = (start_y + end_y) / 2 - 3;
                int food_end_y = (start_y + end_y) / 2 + 3;
                drawRectARGB32(food_start_x, food_start_y, food_end_x, food_end_y, 0xFFFFAA88, 1);
                total_food++;
            }
            else if (map[i][j] == 5)
            { // teleport gate
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, teleport_gate);
            }
            else if (map[i][j] == 6)
            { // freeze ghost
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, freeze_ghosts_food);
            }
            else if (map[i][j] == 7)
            { // reversed food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, reverse_food);
            }
            else if (map[i][j] == 8)
            { // double score
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, double_score_food);
            }
            else if (map[i][j] == 9)
            { // invisible food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, invisible_food);
            }
            else if (map[i][j] == 10)
            { // shield food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, shield_food);
            }
            else if (map[i][j] == 11)
            { // random effect food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, random_effect_food);
            }
            else if (map[i][j] == 12)
            { // random effect food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, power_food);
            }
            else
            { // outside maze zone
                // drawing a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);
            }
        }
    }
    threshold = total_food;
}

void draw_pacman(Pacman *pacman)
{
    // Define the duration (in milliseconds) between each frame update
    // const unsigned int frame_duration_ms = 10;
    clearObject(pacman->pixel_position.x, pacman->pixel_position.y, pacman->size.width, pacman->size.height);
    // set_wait_timer(1, frame_duration_ms);

    // Update the frame
    if (pacman->current_frame < 6)
    {
        pacman->current_frame++;
    }
    else
    { // reset the frame
        pacman->current_frame = 0;
    }

    // Animate the pacman
    // Delete the old frame
    // Draw the current frame
    clearObject(pacman->pixel_position.x, pacman->pixel_position.y, pacman->size.width, pacman->size.height);
    drawObjectARGB32(pacman->pixel_position.x, pacman->pixel_position.y, pacman->size.width, pacman->size.height, pacman->frames[pacman->current_frame]);

    // set_wait_timer(0, frame_duration_ms);
}

void draw_ghost(Ghost *ghost)
{
    if (ghost->status != 0)
    {
        if (ghost->status == 1)
        {
            drawObjectARGB32(ghost->pixel_position.x, ghost->pixel_position.y, ghost->size.width, ghost->size.height, frightened_ghost_frame);
        }
        else
        {
            drawObjectARGB32(ghost->pixel_position.x, ghost->pixel_position.y, ghost->size.width, ghost->size.height, eaten_ghost_frame);
        }
    }
    else
    {
        // drawCircleARGB32(ghost_1_x_position + (GHOST_WIDTH / 2), ghost_1_y_position + (GHOST_HEIGHT /2), ghost_radar_radius);
        drawObjectARGB32(ghost->pixel_position.x, ghost->pixel_position.y, ghost->size.width, ghost->size.height, ghost->image[0]);
    }
}

void game(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky)
{
    // clearScreen();
    // draw the map
    draw_map();
    draw_ghost(&pinky);
    draw_ghost(&blinky);
    draw_ghost(&clyde);
    draw_ghost(&inky);
    int cnt = 0;
    // uart_sendc(total_food); total_food is correct
    char *str_total_points = "";
    char *str_threshold = "";
    copyString(str_total_points, numDisplay(total_points));
    // copyString(str_threshold, numDisplay(threshold));
    // uart_puts(str_total_points);
    drawStringARGB32(750, 600, "Scoreboard: ", 0xFFFFFF);
    displayNumber(850, 600, 10, str_total_points, 0xFFFFFF);
    // uart_puts("Total Food with str_total_food: ");
    // uart_puts(str_total_food);
    // drawCharARGB32(900, 600, '/', 0xFFFFFF);
    // displayNumber(910, 600, 10, str_threshold, 0xFFFFFF);
    // uart_puts("\nThreshold: ");
    //  uart_puts(numDisplay(threshold));

    while (1)
    {
        set_wait_timer(1, 20);
        // break the loop if the game is end.
        if (end_game)
        {
            display_ending_screen();
            break;
        }

        if (is_caught(pacman, pinky, blinky, clyde, inky))
        {
            uart_puts("\nGame Over\n");
            end_game = 1;
            continue;
        }

        is_eaten(pacman, &pinky);
        is_eaten(pacman, &blinky);
        is_eaten(pacman, &clyde);
        is_eaten(pacman, &inky);

        handle_special_food(&pacman, &pinky, &blinky, &clyde, &inky);

        // animate the pacman
        draw_pacman(&pacman);

        // if there is an input key
        if (uart_isReadByteReady() == 0)
        {
            // get the input and execute
            char c = uart_getc();
            move_pacman(&pacman, &pinky, &blinky, &clyde, &inky, c);
            if (pinky.is_move == 0)
            {
                pinky.is_move = 1;
            }
        }

        if (pinky.is_move && cnt % 15 == 0)
        {
            // uart_dec(cnt);
            // uart_puts("\n");
            // set_wait_timer(1, 10);
            move_ghost(&pacman, &pinky, &blinky, &clyde, &inky);
            draw_ghost(&pinky);
            draw_ghost(&blinky);
            draw_ghost(&clyde);
            draw_ghost(&inky);
            // set_wait_timer(0, 10);
        }

        // if all the foods are eaten, dislay winning message and end the game.
        if (total_food == 0)
        {
            uart_puts("\nWINNER! WINNER! CHICKEN! DINNER!");
            end_game = 2;
        }

        // Stop counting time and polling to switch state if all the ghost leaves the house
        if (is_all_out_of_house)
        {
            if (pacman.special_foods.power_up && !frighten_mode)
            {
                enable_frighten_mode(&pinky, &blinky, &clyde, &inky);
            }
            if (pacman.special_foods.invisible)
            {
                scatter_mode = 1;
                chase_mode = 0;
            }
            else
            {
                // After 20s, change to chase mode
                if (((cnt - 1000) % 1500 == 0 && scatter_mode == 1) || cnt == 1000)
                {
                    uart_puts("chase\n");
                    scatter_mode = 0;
                    chase_mode = 1;
                }
                else if (cnt % 1500 == 0 && chase_mode == 1)
                { // After 10s, back to scatter mode
                    uart_puts("scatter\n");
                    scatter_mode = 1;
                    chase_mode = 0;
                }
            }
        }
        set_wait_timer(0, 20);
        if (pinky.is_move)
        {
            cnt++;
        }
    }
}

int is_caught(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky)
{
    return ((pacman.point.row == pinky.point.row && pacman.point.col == pinky.point.col && pinky.status == 0) ||
            (pacman.point.row == blinky.point.row && pacman.point.col == blinky.point.col && blinky.status == 0) ||
            (pacman.point.row == clyde.point.row && pacman.point.col == clyde.point.col && clyde.status == 0) ||
            (pacman.point.row == inky.point.row && pacman.point.col == inky.point.col && inky.status == 0));
}

int is_eaten(Pacman pacman, Ghost *ghost)
{
    if (ghost->status == 1)
    {
        if (pacman.point.row == ghost->point.row && pacman.point.col == ghost->point.col)
        {
            ghost->status = 2;
            total_ghosts_eaten++;

            // Increase score
            char *str_total_points = "";
            displayNumber(850, 600, 10, str_total_points, 0x000000);
            // decrease the total food
            total_points += FOOD_POINTS * 4;

            copyString(str_total_points, numDisplay(total_points));

            displayNumber(850, 600, 10, str_total_points, 0xFFFFFF);

            return 1;
        }
    }
    return 0;
}

void move_ghost(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    // set_wait_timer(1, 200000);

    if (scatter_mode)
    {
        move_ghost_scatter(pacman, pinky, blinky, clyde, inky);
    }
    else if (chase_mode)
    {
        move_ghost_chase(pacman, pinky, blinky, clyde, inky);
    }
    else
    {
        move_ghost_frighten(pacman, pinky, blinky, clyde, inky);
    }

    // set_wait_timer(1, 200000);
}

void move_ghost_scatter(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    if (!is_all_out_of_house)
    {
        move_ghost_execute(pacman, pinky);
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
            move_ghost_execute(pacman, blinky);
        }
        if (clyde->is_move)
        {
            move_ghost_execute(pacman, clyde);
            if (distance_square(clyde->point.row, clyde->point.col, blinky->scatter_position.row, blinky->scatter_position.col) < 200)
            {
                clyde->scatter_position.row = 24;
                clyde->scatter_position.col = 0;
            }
        }
        if (inky->is_move)
        {
            move_ghost_execute(pacman, inky);
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
        move_ghost_execute(pacman, pinky);
        move_ghost_execute(pacman, blinky);
        move_ghost_execute(pacman, clyde);
        move_ghost_execute(pacman, inky);
    }
}

void move_ghost_chase(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
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
    move_ghost_execute(pacman, pinky);

    // Blinky -> Follow pacman
    blinky->target_position.row = pacman->point.row;
    blinky->target_position.col = pacman->point.col;
    move_ghost_execute(pacman, blinky);

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
    move_ghost_execute(pacman, clyde);

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
    move_ghost_execute(pacman, inky);
}

void move_ghost_frighten(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    move_ghost_execute(pacman, pinky);
    move_ghost_execute(pacman, blinky);
    move_ghost_execute(pacman, clyde);
    move_ghost_execute(pacman, inky);
}

void enable_frighten_mode(Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    frighten_mode = 1;
    scatter_mode = 0;
    chase_mode = 0;
    pinky->status = 1;
    blinky->status = 1;
    clyde->status = 1;
    inky->status = 1;
    pinky->previous_move = (pinky->previous_move - 2) < 0 ? pinky->previous_move + 2 : pinky->previous_move - 2;
    blinky->previous_move = (blinky->previous_move - 2) < 0 ? blinky->previous_move + 2 : blinky->previous_move - 2;
    clyde->previous_move = (clyde->previous_move - 2) < 0 ? clyde->previous_move + 2 : clyde->previous_move - 2;
    inky->previous_move = (inky->previous_move - 2) < 0 ? inky->previous_move + 2 : inky->previous_move - 2;
}

void disable_frighten_mode(Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    frighten_mode = 0;
    scatter_mode = 1;
    chase_mode = 0;
    if (pinky->status == 1)
    {
        pinky->status = 0;
    }
    if (blinky->status == 1)
    {
        blinky->status = 0;
    }
    if (clyde->status == 1)
    {
        clyde->status = 0;
    }
    if (inky->status == 1)
    {
        inky->status = 0;
    }
}

void ghost_turn_around(Ghost *ghost)
{
    ghost->previous_move = (ghost->previous_move - 2) < 0 ? ghost->previous_move + 2 : ghost->previous_move - 2;
}

// void back_to_house

void move_priority(Ghost *ghost, PriorityQueue (*arr)[])
{
    int up_dis, left_dis, down_dis, right_dis;
    if (scatter_mode && ghost->status == 0)
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
                map[ghost->point.row][ghost->point.col] != 3)
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
            if (ghost->previous_move != 3 && ghost->point.col > 0 && map[ghost->point.row][ghost->point.col - 1] != 1 &&
                map[ghost->point.row][ghost->point.col - 1] != 5)
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
            if (ghost->previous_move != 0 && ghost->point.row < 23 && map[ghost->point.row + 1][ghost->point.col] != 1 &&
                (ghost->point.row + 1 != gate.row || ghost->point.col != gate.col || ghost->status != 1))
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
            if (ghost->previous_move != 1 && ghost->point.col < 22 && map[ghost->point.row][ghost->point.col + 1] != 1 &&
                map[ghost->point.row][ghost->point.col + 1] != 5)
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
    ghost_turn_around(ghost);
}

int random_move(Ghost *ghost, int direction)
{
    if (direction == 0)
    {
        if (ghost->previous_move != 2 && ghost->point.row > 1 && map[ghost->point.row - 1][ghost->point.col] != 1 &&
            map[ghost->point.row][ghost->point.col] != 3)
        {
            // move to the new position
            // increasing the row
            ghost->point.row -= 1;
            ghost->pixel_position.y -= 24;

            // update the previous
            ghost->previous_move = 0;
            return 1;
        }
    }

    if (direction == 1)
    {
        if (ghost->previous_move != 3 && ghost->point.col > 0 && map[ghost->point.row][ghost->point.col - 1] != 1)
        {
            // move to the new position
            // decreasing the collumn
            ghost->point.col -= 1;
            ghost->pixel_position.x -= 25;

            // update the previous
            ghost->previous_move = 1;
            return 1;
        }
    }

    if (direction == 2)
    {
        if (ghost->previous_move != 0 && ghost->point.row < 23 && map[ghost->point.row + 1][ghost->point.col] != 1 &&
            (ghost->point.row + 1 != gate.row || ghost->point.col != gate.col))
        {
            // move to the new position
            // increasing the row
            ghost->point.row += 1;
            ghost->pixel_position.y += 24;

            // update the previous
            ghost->previous_move = 2;
            return 1;
        }
    }
    if (direction == 3)
    {
        if (ghost->previous_move != 1 && ghost->point.col < 22 && map[ghost->point.row][ghost->point.col + 1] != 1)
        {
            // move to the new position
            // increasing the collumn
            ghost->point.col += 1;
            ghost->pixel_position.x += 25;

            // update the previous
            ghost->previous_move = 3;
            return 1;
        }
    }

    return 0;
}

void move_ghost_execute(Pacman *pacman, Ghost *ghost)
{
    // clearing the old ghost in the screen
    // draw back the food if there is one
    draw_food_after_ghosts_move(ghost);

    if (frighten_mode && ghost->status == 1)
    {
        int move_cnt = 0;
        while (1)
        {
            move_cnt++;
            int random_direction = random_small_number() % 4;
            if (random_move(ghost, random_direction))
            {
                return;
            }
            if (move_cnt > 20)
            {
                ghost_turn_around(ghost);
                move_cnt = 0;
            }
        }
    }
    else
    {
        if (ghost->status > 1)
        {
            if (ghost->status == 2)
            {
                // uart_puts("To gate\n");
                ghost->target_position.row = gate.row;
                ghost->target_position.col = gate.col;
                ghost->status = 3;
            }
            else if (ghost->point.row == gate.row && ghost->point.col == gate.col)
            {
                // uart_puts("To house\n");
                ghost->target_position.row = gate.row + 2;
                ghost->target_position.col = gate.col;
                ghost->status = 4;
            }
            else if (ghost->point.row == gate.row + 2 && ghost->point.col != gate.col && ghost->status == 4)
            {
                // uart_puts("Alive\n");
                ghost->target_position.row = pacman->point.row;
                ghost->target_position.col = pacman->point.col;
                // ghost->target_position.row = gate.row;
                // ghost->target_position.col = gate.col;
                ghost->status = 0;
            }
        }
        PriorityQueue descending_dis[4];

        // Find and sort the distance from surrounding tiles to the target (by distance and priority of directions)
        move_priority(ghost, &descending_dis);

        process_next_move(ghost, descending_dis);
    }
}

void handle_special_food(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    static int reversed_time = 15;
    static int freeze_ghosts_time = 15;
    static int invisible_time = 15;
    static int power_up_time = 10;

    int x_offset = 0;

    if (!pacman->special_foods.active)
    {
        for (int i = 0; i < 5; i++)
        {
            clearObject(10 + x_offset * 40, 572, 32, 32);
        }
    }

    if (pacman->special_foods.freeze_ghosts)
    {
        if (x_offset < pacman->special_foods.active)
        {
            // set_wait_timer(1, 10);
            drawObjectARGB32(10 + x_offset * 40, 572, 32, 32, freeze_ghosts_food_icon);
            // set_wait_timer(0, 10);
            x_offset++;
        }

        if (pinky->is_move)
        {
            pinky->is_move = 0;
        }

        clock(&freeze_ghosts_time);
        if (!freeze_ghosts_time)
        {
            freeze_ghosts_time = 15; // Reset time for next time pacman eat that item
            clearObject(10 + x_offset * 40, 572, 32, 32);
            pacman->special_foods.active--;
            pacman->special_foods.freeze_ghosts = 0;

            if (!pinky->is_move)
            {
                pinky->is_move = 1;
            }
        }
    }

    if (pacman->special_foods.reversed)
    {
        if (x_offset < pacman->special_foods.active)
        {
            // set_wait_timer(1, 10);
            drawObjectARGB32(10 + x_offset * 40, 572, 32, 32, reversed_food_icon);
            // set_wait_timer(0, 10);
            x_offset++;
        }

        clock(&reversed_time);
        if (!reversed_time)
        {
            reversed_time = 15; // Reset time for next time pacman eat that item
            clearObject(10 + x_offset * 40, 572, 32, 32);
            pacman->special_foods.active--;
            pacman->special_foods.reversed = 0;
        }
    }

    if (pacman->special_foods.invisible)
    {
        if (x_offset < pacman->special_foods.active)
        {
            // set_wait_timer(1, 10);
            drawObjectARGB32(10 + x_offset * 40, 572, 32, 32, invisible_food_icon);
            // set_wait_timer(0, 10);
            x_offset++;
        }

        clock(&invisible_time);
        if (!invisible_time)
        {
            // invisible_time = 15; // Reset time for next time pacman eat that item
            clearObject(10 + x_offset * 40, 572, 32, 32);
            pacman->special_foods.active--;
            pacman->special_foods.invisible = 0;
        }
    }

    if (pacman->special_foods.power_up)
    {
        if (x_offset < pacman->special_foods.active)
        {
            // set_wait_timer(1, 10);
            drawObjectARGB32(10 + x_offset * 40, 572, 32, 32, power_food_icon);
            // set_wait_timer(0, 10);
            x_offset++;
        }

        clock(&power_up_time);
        if (!power_up_time)
        {
            disable_frighten_mode(pinky, blinky, clyde, inky);
            power_up_time = 10; // Reset time for next time pacman eat that item
            clearObject(10 + x_offset * 40, 572, 32, 32);
            pacman->special_foods.active--;
            pacman->special_foods.power_up = 0;
        }
    }
}

void display_ending_screen()
{
    int cnt = 0;
    int result_col = 9;
    int result_row = 13;
    int statistic = 0;
    int time = 0;
    int stage = 0;
    int wait = 0;
    display_ending_result(result_col, result_row);
    while (1)
    {
        set_wait_timer(1, 5);
        if (cnt == 600)
        {
            clearScreen();
            display_ending_result(result_col, result_row);
            stage++;
        }
        if (stage == 1 && cnt % 10 == 0 && result_row > 2)
        {
            result_row -= 1;
            display_ending_result(result_col, result_row);
            if (result_row == 2)
            {
                stage++;
            }
        }
        if (stage == 2 && cnt % 5 == 0 && time <= threshold - total_food && statistic == 0)
        {
            display_statistic(statistic, time);
            time++;
            if (time > threshold - total_food)
            {
                time = 0;
                statistic++;
                wait = 200;
            }
        }
        if (wait == 0 && cnt % 5 == 0 && time <= total_special_foods_eaten && statistic == 1)
        {
            display_statistic(statistic, time);
            time++;
            if (time > total_special_foods_eaten)
            {
                time = 0;
                statistic++;
                wait = 200;
            }
        }
        if (wait == 0 && cnt % 5 == 0 && time <= total_ghosts_eaten && statistic == 2)
        {
            display_statistic(statistic, time);
            time++;
            if (time > total_ghosts_eaten)
            {
                time = 0;
                statistic++;
                wait = 200;
                stage++;
            }
        }
        if (wait == 0 && stage == 3 && time <= total_points) 
        {
            display_statistic(statistic, time);
            time++;
            if (time > total_points) {
                stage++;
                time = 0;
                wait = 200;
            }
        }
        if (wait == 0 && stage == 4 && cnt % 200 == 0) {
            display_rating(time);
            time++;
            if (time > 5) {
                break;
            }
        }
        if (wait != 0)
        {
            wait--;
        }
        cnt++;
        set_wait_timer(0, 5);
    }
}

void display_ending_result(int col, int row)
{
    if (row != 13)
    {
        drawRectARGB32(10 + col * 25, 10 + (row + 1) * 24, 10 + col * 25 + 24, 10 + (row + 1) * 24 + 23, 0x00000000, 1);
        drawRectARGB32(10 + (col + 1) * 25, 10 + (row + 1) * 24, 10 + (col + 1) * 25 + 24, 10 + (row + 1) * 24 + 23, 0x00000000, 1);
        drawRectARGB32(10 + (col + 2) * 25, 10 + (row + 1) * 24, 10 + (col + 2) * 25 + 24, 10 + (row + 1) * 24 + 23, 0x00000000, 1);
    }

    if (end_game == 1)
    {
        drawRectARGB32(10 + col * 25, 10 + row * 24, 10 + col * 25 + 24, 10 + row * 24 + 23, 0x00000000, 1);
        drawRectARGB32(10 + (col + 1) * 25, 10 + row * 24, 10 + (col + 1) * 25 + 24, 10 + row * 24 + 23, 0x00000000, 1);
        drawRectARGB32(10 + (col + 2) * 25, 10 + row * 24, 10 + (col + 2) * 25 + 24, 10 + row * 24 + 23, 0x00000000, 1);
        drawStringARGB32(238, 330 / 13.0f * row, "Game Over", 0x00FF00000);
    }
    else
    {
        drawRectARGB32(10 + col * 25, 10 + row * 24, 10 + col * 25 + 24, 10 + row * 24 + 23, 0x00000000, 1);
        drawRectARGB32(10 + (col + 1) * 25, 10 + row * 24, 10 + (col + 1) * 25 + 24, 10 + row * 24 + 23, 0x00000000, 1);
        drawRectARGB32(10 + (col + 2) * 25, 10 + row * 24, 10 + (col + 2) * 25 + 24, 10 + row * 24 + 23, 0x00000000, 1);
        drawStringARGB32(240, 330 / 13.0f * row, "You Won", 0x00FF00);
    }
}

void display_statistic(int value, int time)
{
    switch (value)
    {
    case 0: // Total foods
        if (time == 0)
        {
            drawStringARGB32(120, 100, "Total foods eaten", 0x00FFFF00);
        }
        char *str_total_foods_eaten = "";
        displayNumber(400, 100, 10, str_total_foods_eaten, 0x00000000);
        copyString(str_total_foods_eaten, numDisplay(time));
        displayNumber(400, 100, 10, str_total_foods_eaten, 0x00FFFF00);
        break;
    case 1: // Special foods consume
        if (time == 0)
        {
            drawStringARGB32(120, 150, "Total special foods eaten", 0x00FFFF00);
        }
        char *str_total_special_foods_eaten = "";
        displayNumber(400, 150, 10, str_total_special_foods_eaten, 0x00000000);
        copyString(str_total_special_foods_eaten, numDisplay(time));
        displayNumber(400, 150, 10, str_total_special_foods_eaten, 0x00FFFF00);
        break;
    case 2: // Ghosts eaten
        if (time == 0)
        {
            drawStringARGB32(120, 200, "Total ghosts caught", 0x00FFFF00);
        }
        char *str_total_ghosts_eaten = "";
        displayNumber(400, 200, 10, str_total_ghosts_eaten, 0x00000000);
        copyString(str_total_ghosts_eaten, numDisplay(time));
        displayNumber(400, 200, 10, str_total_ghosts_eaten, 0x00FFFF00);
        break;
    // case 4: // Time remaining
    //     drawStringARGB32(240, 330 / 13.0f * row, "You Won", 0x00FFFF00);
    //     break;
    default: // Total score
        if (time == 0)
        {
            for (int i = 3; i < 18; i++) {
                drawRectARGB32(10 + i * 25, 10 + 10 * 24, 10 + i * 25 + 24, 10 + 10 * 24 + 5, 0x00FFFF00, 1);
            }
            drawStringARGB32(120, 295, "Total score", 0x00FFFF00);
        }
        char *str_total_points = "";
        displayNumber(400, 295, 10, str_total_points, 0x00000000);
        copyString(str_total_points, numDisplay(time));
        displayNumber(400, 295, 10, str_total_points, 0x00FFFF00);
        break;
    }
}

void display_rating(int value) {
    switch (value)
    {
    case 0:
        drawObjectARGB32(120, 350, 32, 32, star_icon);
        drawStringARGB32(200, 366, "Eat all the foods", 0x00FFFF00);
        break;

    case 1: 
        drawObjectARGB32(120, 400, 32, 32, star_icon);
        drawStringARGB32(200, 416, "Score at least 1100 pts", 0x00FFFF00);
        break;
    
    case 2:
        drawObjectARGB32(120, 450, 32, 32, star_icon);
        drawStringARGB32(200, 466, "Caught at least 4 ghosts", 0x00FFFF00);
        break;

    case 3:
        if (end_game == 1) { 
            drawObjectARGB32(120, 350, 32, 32, star_fill_icon);
        }
        break;
    
    case 4:
        if (total_points >= 1100) {
            drawObjectARGB32(120, 400, 32, 32, star_fill_icon);
        }
        break;

    default:
        if (total_ghosts_eaten >= 4) {
            drawObjectARGB32(120, 450, 32, 32, star_fill_icon);
        }
        break;
    }
}
