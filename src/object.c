#include "object.h"

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
    {pinky_frame,
    frightened_ghost_frame,
    eaten_ghost_frame}};

Ghost blinky = {
    {10, 11},
    {287, 252},
    {22, 20},
    {-4, 20},
    {0, 0},
    0,
    0,
    0,
    {blinky_frame,
    frightened_ghost_frame,
    eaten_ghost_frame}};

Ghost clyde = {
    {11, 9},
    {237, 275},
    {22, 20},
    {23, 0},
    {0, 0},
    0,
    0,
    0,
    {clyde_frame,
    frightened_ghost_frame,
    eaten_ghost_frame}};

Ghost inky = {
    {11, 11},
    {287, 275},
    {22, 20},
    {23, 22},
    {0, 0},
    0,
    0,
    0,
    {inky_frame,
    frightened_ghost_frame,
    eaten_ghost_frame}};

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
    if (ghost->status != 0 && ghost->status != 5)
    {
        if (ghost->status == 1)
        {
            drawObjectARGB32(ghost->pixel_position.x, ghost->pixel_position.y, ghost->size.width, ghost->size.height, ghost->image[1]);
        }
        else
        {
            drawObjectARGB32(ghost->pixel_position.x, ghost->pixel_position.y, ghost->size.width, ghost->size.height, ghost->image[2]);
        }
    }
    else
    {
        // drawCircleARGB32(ghost_1_x_position + (GHOST_WIDTH / 2), ghost_1_y_position + (GHOST_HEIGHT /2), ghost_radar_radius);
        drawObjectARGB32(ghost->pixel_position.x, ghost->pixel_position.y, ghost->size.width, ghost->size.height, ghost->image[0]);
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
    if (map[pacman->point.row][pacman->point.col] == 2 || map[pacman->point.row][pacman->point.col] == 3)
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
        if (distance_square(blinky->point.row, blinky->point.col, pinky->point.row, pinky->point.col) > 5)
        {
            blinky->is_move = 1;
        }
        if (distance_square(blinky->point.row, blinky->point.col, clyde->point.row, clyde->point.col) > 5 && !clyde->is_move)
        {
            clyde->is_move = 1;
            clyde->scatter_position.row = blinky->scatter_position.row;
            clyde->scatter_position.col = blinky->scatter_position.col;
        }
        if (distance_square(clyde->point.row, clyde->point.col, inky->point.row, inky->point.col) > 5 && !inky->is_move)
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
    if (pinky->status == 0)
    {
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
    }
    move_ghost_execute(pacman, pinky);

    // Blinky -> Follow pacman
    if (blinky->status == 0)
    {
        blinky->target_position.row = pacman->point.row;
        blinky->target_position.col = pacman->point.col;
    }
    move_ghost_execute(pacman, blinky);

    // Clyde -> outside 8 tiles around pacman -> chase like blinky; otherwise, scatter
    if (clyde->status == 0)
    {
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
    }
    move_ghost_execute(pacman, clyde);

    // Inky
    if (inky->status == 0)
    {
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
    }
    move_ghost_execute(pacman, inky);
}

void move_ghost_frighten(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    move_ghost_execute(pacman, pinky);
    move_ghost_execute(pacman, blinky);
    move_ghost_execute(pacman, clyde);
    move_ghost_execute(pacman, inky);
}

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
                (ghost->point.row + 1 != map_data[level].gate.row || ghost->point.col != map_data[level].gate.col || ghost->status != 1))
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

void ghost_turn_around(Ghost *ghost)
{
    ghost->previous_move = (ghost->previous_move - 2) < 0 ? ghost->previous_move + 2 : ghost->previous_move - 2;
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
                ghost->target_position.row = map_data[level].gate.row;
                ghost->target_position.col = map_data[level].gate.col;
                ghost->status = 3;
            }
            else if (ghost->point.row == map_data[level].gate.row && ghost->point.col == map_data[level].gate.col && ghost->status == 3)
            {
                // uart_puts("To house\n");
                ghost->target_position.row = map_data[level].gate.row + 2;
                ghost->target_position.col = map_data[level].gate.col;
                ghost->status = 4;
            }
            else if (ghost->point.row == map_data[level].gate.row + 2 && ghost->point.col != map_data[level].gate.col && ghost->status == 4)
            {
                // uart_puts("Alive\n");
                ghost->target_position.row = map_data[level].gate.row;
                ghost->target_position.col = map_data[level].gate.col;
                ghost->status = 5;
            } else if (ghost->point.row == map_data[level].gate.row && ghost->point.col != map_data[level].gate.col && ghost->status == 5) {
                ghost->target_position.row = pacman->point.row;
                ghost->target_position.col = pacman->point.col;
                ghost->status = 0;
            }
        }
        PriorityQueue descending_dis[4];

        // Find and sort the distance from surrounding tiles to the target (by distance and priority of directions)
        move_priority(ghost, &descending_dis);

        process_next_move(ghost, descending_dis);
    }
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
        if (ghost->previous_move != 3 && ghost->point.col > 0 && map[ghost->point.row][ghost->point.col - 1] != 1 &&
            map[ghost->point.row][ghost->point.col - 1] != 5)
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
            (ghost->point.row + 1 != map_data[level].gate.row || ghost->point.col != map_data[level].gate.col))
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
        if (ghost->previous_move != 1 && ghost->point.col < 22 && map[ghost->point.row][ghost->point.col + 1] != 1 && 
            map[ghost->point.row][ghost->point.col + 1] != 5)
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