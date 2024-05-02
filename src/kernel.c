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

typedef struct {
    int x;
    int y;
} Pixel_Position;

typedef struct {
    int width;
    int height;
} Size;

typedef struct {
    Point point;
    Pixel_Position pixel_position;
    Size size;
    int current_frame;
    unsigned long* frames[7];
} Pacman;

typedef struct {
    Point point;
    Pixel_Position pixel_Position;
    Size size;
    Point target;
    int radar_radius;
    unsigned long* image[1];
} Ghost;

const int SCREEN_WIDTH = 524;
const int SCREEN_HEIGHT = 524;
const int OFFSET = 20;

int y_index = 0;
int x_index = 0;

typedef struct {
    int total_food;
    int ghost_ability_to_move;
    int score;
    int game_status;
} Game;

//GAME INFO
int total_food = 220;
int ghost_ability_to_move = 0;
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
    {5, 5, 5, 5, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 5, 5, 5, 5},
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {5, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 5},
    {1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {5, 5, 5, 5, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 5, 5, 5, 5},
    {5, 5, 5, 5, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 5, 5, 5, 5},
    {1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1},
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
void draw_pacman(Pacman* pacman);
void calculate_ghost_move(Ghost* ghost, Point point);
void move_pacman(Pacman* pacman, char c);
void draw_food_after_ghosts_move();
void game(Pacman pacman, Ghost ghost_1, Ghost ghost_2);
void find_shorest_path(Ghost* ghost);
void random_target(Ghost* ghost);
void move_ghosts(Ghost* ghost_1, Ghost* ghost_2);

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
        {1,1},
        {36,35},
        {20,20},
        0,
        {
            pacman_frame_0,
            pacman_frame_1,
            pacman_frame_2,
            pacman_frame_3,
            pacman_frame_4,
            pacman_frame_5,
            pacman_frame_6
        }
    };

    Ghost ghost_1 = {
        {10,9},
        {237,252},
        {22,20},
        {8,9},
        50,
        {ghost_1_image}
    };

    Ghost ghost_2 = {
        {10,11},
        {287,252},
        {22,20},
        {8,11},
        50,
        {ghost_1_image}
    };

    while (1)
    {   
        // drawImageARGB32(0, 0, x_index, y_index, image);
        // int flag = 1;

        // while(flag == 1){
        //     char c1 = getUart();
        //     move_image(c1, flag);
        // }

        game(pacman, ghost_1, ghost_2);
    }
}

void handle_delete(){
    // Move buffer index back
    buffer_index--;

    // Erase last character from console
    uart_puts("\b \b");

    // Shift characters after deleted character one position to the left
    for (int i = buffer_index; i < BUFFER_SIZE - 1; i++) {
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
    } else {
        flag =1;
    }
}

void move_pacman(Pacman* pacman, char c)
{   
    int pacman_old_x_position = pacman->pixel_position.x;
    int pacman_old_y_position = pacman->pixel_position.y;
    if (c == 's')
    {   
        //if the pacman is in the last row
        //it cannot go down any more
        if (pacman->point.row == 22)
        {
            return;
        }

        //if the under position is a wall
        //pacman cannot move down
        if (map[pacman->point.row + 1][pacman->point.col] == 1)
        {
            return;
        }
        
        //clearing the pacman's old position in the map
        map[pacman->point.row][pacman->point.col] = 0;

        //move to the new position
        //increasing the row
        pacman->point.row++;
        pacman->pixel_position.y += 24;
    }
    else if (c == 'w')
    {   
        //if the pacman is in the first row
        //it cannot go down any more
        if (pacman->point.row <= 1)
        {
            return;
        }

        //if the above position is a wall
        //pacman cannot move down
        if (map[pacman->point.row -1 ][pacman->point.col] == 1)
        {
            return;
        }

        //clearing the pacman's old position in the map
        map[pacman->point.row][pacman->point.col] = 0;

        //move to the new position
        //decreasing the row
        pacman->point.row--;
        pacman->pixel_position.y -= 24;
    }
    else if (c == 'd')
    {   
        //if the pacman is in the last collumn
        //it cannot go right any more
        if (pacman->point.col == 21)
        {
            return;
        }

        //if the right position is a wall
        //pacman cannot move right
        if (map[pacman->point.row][pacman->point.col + 1] == 1)
        {
            return;
        }

        //clearing the pacman's old position in the map
        map[pacman->point.row][pacman->point.col] = 0;

        //move to the new position
        //increasing the collumn
        pacman->point.col++;
        pacman->pixel_position.x += 25;
    }
    else if (c == 'a')
    {   
        //if the pacman is in the first collumn
        //it cannot go left any more
        if (pacman->point.col == 0)
        {
            return;
        }

        //if the left position is a wall
        //pacman cannot move left
        if (map[pacman->point.row][pacman->point.col -1] == 1)
        {
            return;
        }

        //clearing the pacman's old position in the map
        map[pacman->point.row][pacman->point.col] = 0;

        //move to the new position
        //decreasing the collumn
        pacman->point.col--;
        pacman->pixel_position.x -= 25;
    }

    //if the new position has a food
    if (map[pacman->point.row][pacman->point.col] == 2)
    {   
        //decrease the total food 
        total_food -= 1;
    }

    //mark the new position of pacman on the map
    map[pacman->point.row][pacman->point.col] = 4;

    //clearing the old pacman in the screen
    clearObject(pacman_old_x_position, pacman_old_y_position, pacman->size.width, pacman->size.height);
}

void draw_food_after_ghosts_move(Ghost* ghost){
    //clearing the old ghosts in the screen
     //draw back the foods
    clearObject(ghost->pixel_Position.x, ghost->pixel_Position.y, ghost->size.width, ghost->size.height);
    if(map[ghost->point.row][ghost->point.col] == 2){
        drawRectARGB32(10 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 24, 10 + ghost->point.row * 24 + 23, 0xFF000000,1);
        int food_start_x = (2 * ghost->pixel_Position.x + 25) / 2 - 6;
        int food_end_x = (2 * ghost->pixel_Position.x + 25) / 2 + 2;
        int food_start_y = (2 * ghost->pixel_Position.y + 24) /2 - 3;
        int food_end_y = (2 * ghost->pixel_Position.y + 24) /2 + 3;
        drawRectARGB32(food_start_x, food_start_y, food_end_x, food_end_y, 0xFFFFAA88,1);
    } else {
        drawRectARGB32(9 + ghost->point.col * 25, 10 + ghost->point.row * 24, 10 + ghost->point.col * 25 + 25, 10 + ghost->point.row * 24 + 23, 0xFF000000,1);
    }
}

void draw_map(){
    //loop through the 2D map
    for (int i = 0; i < 23; ++i) {
        for (int j = 0; j < 22; ++j) { 
            //calculate x1, y1, x2, y2 of every box in the map
            //each box has a width of 25 and height of 24
            int start_x = 10 + (25 * j);
            int end_x = start_x + 25;
            int start_y = 10 + (24 * i);
            int end_y = start_y + 24;

            if(map[i][j] == 1){ //if this is a wall
                //draw a bule rectangal
                drawRectARGB32(start_x, start_y, end_x, end_y, 0x000000CC,1);
            } else if (map[i][j] == 2){ //if this is a road
                //draw a black rectangle
                drawRectARGB32(start_x , start_y , end_x, end_y, 0xFF000000,1);

                //draw the food
                //the food is place in the middle of the reactangle
                //the food has a width of 8 and a height of 6
                int food_start_x = (start_x + end_x) / 2 - 4;
                int food_end_x = (start_x + end_x) / 2 + 4;
                int food_start_y = (start_y + end_y) /2 - 3;
                int food_end_y = (start_y + end_y) /2 + 3;
                drawRectARGB32(food_start_x, food_start_y, food_end_x, food_end_y, 0xFFFFAA88,1);
            } else { //outside maze zone
                //drawing a black rectangle
                drawRectARGB32(start_x , start_y , end_x, end_y, 0xFF000000,1);
            } 
        }
    }
}

void draw_pacman(Pacman* pacman)
{
    // Define the duration (in milliseconds) between each frame update
    const unsigned int frame_duration_ms = 2000;


    // Update the frame
    if (pacman->current_frame < 6)
    {
        pacman->current_frame++;
    }
    else
    {   //reset the frame
        pacman->current_frame = 0;
    }

    set_wait_timer(1, frame_duration_ms);

    //Animate the pacman
    //Delete the old frame
    //Draw the current frame
    clearObject(pacman->pixel_position.x, pacman->pixel_position.y, pacman->size.width, pacman->size.height);
    drawObjectARGB32(pacman->pixel_position.x, pacman->pixel_position.y, pacman->size.width, pacman->size.height, pacman->frames[pacman->current_frame]);
        
    set_wait_timer(0, frame_duration_ms);
}

void draw_ghost(Ghost* ghost){
    //drawCircleARGB32(ghost_1_x_position + (GHOST_WIDTH / 2), ghost_1_y_position + (GHOST_HEIGHT /2), ghost_radar_radius);
    drawObjectARGB32(ghost->pixel_Position.x, ghost->pixel_Position.y, ghost->size.width, ghost->size.height, ghost->image[0]);
}

void game(Pacman pacman, Ghost ghost_1, Ghost ghost_2){
    //draw the map
    draw_map();

    while (1)
    {   
        set_wait_timer(1, 1000);
        //animate the pacman 
        draw_pacman(&pacman);
        set_wait_timer(0, 1000);

        //break the loop if the game is end.
        if(end_game == 1){
            wait_msec(1000);
            break;
        }

        // if(ghost_ability_to_move == 1){
        //     move_ghosts(&ghost_1, &ghost_2);

        // }
        draw_ghost(&ghost_1);
        draw_ghost(&ghost_2);

        // if(pacman_col == ghost_1_col && pacman_row == ghost_1_row){
        //     uart_puts("\nGame Over");
        //     end_game = 1;
        // }

        //if there is an input key
        if(uart_isReadByteReady() == 0){
            //get the input and execute
            char c = uart_getc();
            set_wait_timer(1, 1000);
            move_pacman(&pacman, c);
            set_wait_timer(0, 1000);
            if (ghost_ability_to_move == 0){
                ghost_ability_to_move = 1;
            }
        } 

        //calculate the distance between the pacman and the ghost
        // int distance = calculate_distance(pacman_x_position + (PACMAN_WIDTH / 2), pacman_y_position + (PACMAN_HEIGHT / 2), 237, 252);
        // if(distance < 50){
        //     //the ghost found the pacman
        // }

        //if all the foods are eaten, dislay winning message and end the game.
        if (total_food == 0)
        {
            uart_puts("\nWINNER! WINNER! CHICKEN! DINNER!");
            end_game = 1;
        }
    }
}

void find_shorest_path(Ghost* ghost) {
    int visited[ROWS][COLS];
    int distance[ROWS][COLS];
    Point parent[ROWS][COLS];
    Point start = ghost->point;
    Point end = ghost->target;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            visited[i][j] = 0;
            distance[i][j] = -1;
        }
    }

    Queue q, path;
    initialize_queue(&q);
    initialize_queue(&path);
    enqueue(&q, ghost->point);
    visited[start.row][start.col] = 1;
    distance[start.row][start.col] = 0;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    while (!is_queue_empty(&q)) {
        Point current = dequeue(&q);
        if (is_point_equal(current, end) == 0) {
            while (!(current.row == start.row && current.col == start.col)) {
                enqueue(&path, current);
                current = parent[current.row][current.col];
            }
            reverse_queue(&path);
            int index = path.front;
            for (int i = 0; i < path.size; i++) {
                Point next_move = path.items[index];
                draw_food_after_ghosts_move(ghost);
                calculate_ghost_move(ghost, next_move);
                ghost->point = next_move;
                draw_ghost(ghost);
                wait_msec(50000);

                index = (index + 1) % MAX_SIZE;
            }

            random_target(ghost);
            return;
        }
        for (int i = 0; i < 4; i++) {
            int newX = current.row + dx[i];
            int newY = current.col + dy[i];
            if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS && (map[newX][newY] == 0 || map[newX][newY] == 2) && !visited[newX][newY]) {
                visited[newX][newY] = 1;
                distance[newX][newY] = distance[current.row][current.col] + 1;
                parent[newX][newY] = current;
                Point next = {newX, newY};
                enqueue(&q, next);
            }
        }
    }
}

void calculate_ghost_move(Ghost* ghost, Point point){
    //left
    if(point.col - ghost->point.col < 0){
        ghost->pixel_Position.x -= 25;
        return;
    }

    //right
    if(point.col - ghost->point.col > 0){
        ghost->pixel_Position.x += 25;
        return;
    }

    //up
    if(point.row - ghost->point.row < 0){
        ghost->pixel_Position.y -= 24;
        return;
    }

    //down
    if(point.row - ghost->point.row > 0){
        ghost->pixel_Position.y += 24;
        return;
    }
}

void random_target(Ghost* ghost){
    int random_row = 0;
    int random_col = 0;

    while(map[random_row][random_col] == 1 || map[random_row][random_col] == 5){
        random_row = random_number() * random_number() % 23;
        random_col = random_number() * random_number() % 22;
    } 

    Point random_point = {random_row, random_col};
    ghost->target = random_point;
}

void move_ghosts(Ghost* ghost_1, Ghost* ghost_2){
    find_shorest_path(ghost_1);

    // find_shorest_path(ghost_2);
}