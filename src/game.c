#include "game.h"
// #include "homescreen.h"

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
int level = 0;
int cnt = 0;
int map[ROWS][COLS];
int ghost_speed = 15;
int total_moves = 0;

int reversed_time = 0;
int freeze_ghosts_time = 0;
int invisible_time = 0;
int power_up_time = 0;
int double_score_time = 0;
int speed_up_time = 0;

int reversed_time_track = 0;
int freeze_ghosts_time_track = 0;
int invisible_time_track = 0;
int power_up_time_track = 0;
int double_score_time_track = 0;
int speed_up_time_track = 0;

void display_instruction(int page)
{
    if (page != 0)
    {
        drawObjectARGB32(27, 270, 60, 110, back_button);
    }
    if (page != 4)
    {
        drawObjectARGB32(464, 270, 60, 110, forward_button);
    }
    if (page == 0)
    {
        drawStringARGB32(253, 30, "Pacman", 0x00FFFF00);
        drawObjectARGB32(90, 60, PAGE_WIDTH, PAGE_HEIGHT, pacman_help);
        drawStringARGB32(90, 250, "Press a/w/s/d buttons to go up/left/down/right.", 0x00FFFF00);
        drawStringARGB32(165, 540, "Try to move around the maze", 0x00FFFF00);
        drawStringARGB32(127, 560, "and eat all the food to win the game!", 0x00FFFF00);
    }
    if (page == 1)
    {
        drawStringARGB32(253, 30, "Ghosts", 0x0000FF00);
        drawObjectARGB32(90, 60, PAGE_WIDTH, PAGE_HEIGHT, ghost_help);
        drawStringARGB32(145, 200, "Pac-Man isn't alone in the maze.", 0x0000FF00);
        drawStringARGB32(100, 220, "Four colorful ghosts chase him relentlessly.", 0x0000FF00);
        drawStringARGB32(135, 540, "Try to avoid them while eating food.", 0x0000FF00);
        drawStringARGB32(80, 560, "The game will end once a ghost catches the pacman!", 0x0000FF00);
    }
    if (page == 2)
    {
        drawStringARGB32(225, 30, "Special items", 0x00FF0000);
        drawObjectARGB32(90, 60, PAGE_WIDTH, PAGE_HEIGHT, special_foods_help);
        drawStringARGB32(190, 105, "(+)Invincible for 10s.", 0x000000FF);
        drawStringARGB32(190, 195, "(+)Double score for 10s.", 0x000000FF);
        drawStringARGB32(190, 285, "(+)Freeze ghosts for 10s.", 0x000000FF);
        drawStringARGB32(190, 375, "(-)Pacman's moves are reversed.", 0x00FF0000);
        drawStringARGB32(190, 465, "(-)Ghosts' speed is increased.", 0x00FF0000);
    }
    if (page == 3)
    {
        drawStringARGB32(225, 30, "Special items", 0x00FF0000);
        drawObjectARGB32(90, 60, PAGE_WIDTH, PAGE_HEIGHT, power_up_help);
        drawStringARGB32(35, 180, "Eating this Power Pellet grants Pac-Man a temporary ability", 0x0000FF00);
        drawStringARGB32(135, 200, "to turn the tables on his pursuers.", 0x0000FF00);
        drawStringARGB32(145, 425, "When pacman eat the power potion,", 0x0000FF00);
        drawStringARGB32(70, 445, "the ghost will stop chasing pacman and running away.", 0x0000FF00);
        drawStringARGB32(70, 485, "Catch these frightened blue ghosts for extra points.", 0x0000FF00);
    }
    if (page == 4)
    {
        drawStringARGB32(240, 60, "That's it!", 0x00FFFF00);
        drawStringARGB32(140, 100, "You can now freely explore the game", 0x00FFFF00);
        drawStringARGB32(155, 120, "for more features and mechanism.", 0x00FFFF00);
        drawStringARGB32(90, 160, "Hopes you enjoy our game and rate us 5 stars :D", 0x00FFFF00);
        drawObjectARGB32(90, 210, PAGE_WIDTH, PAGE_WIDTH, team_logo);
        drawStringARGB32(120, 620, "Type 3 to go back to game's main menu.", 0x0000FF00);
    }
}

void display_home_screen()
{
    drawObjectARGB32(12, 5, 524, 639, home_screen);
    drawStringARGB32(170, 490, "Press 1 to play game", 0x00FFFF00);
    drawStringARGB32(170, 533, "Press 2 to see instruction", 0x00F07420);
    drawStringARGB32(170, 576, "Press 3 to return main menu", 0x00FF00000);
}

void level_preview()
{
    draw_map_preview();
    if (level != 0 && !map_data[level - 1].mission1.is_done)
    {
        drawObjectARGB32(198, 380, 145, 200, lock);
        drawStringARGB32(20, 600, "Finished previous map by eating all the food to unlock this map.", 0x0000FFFF);
    }
    else
    {
        display_statistic_overall();
        drawStringARGB32(160, 600, "Press enter to play this map.", 0x0000FFFF);
    }

    if (level != 0)
    {
        drawObjectARGB32(27, 270, 60, 110, back_button);
    }
    if (level != 4)
    {
        drawObjectARGB32(464, 270, 60, 110, forward_button);
    }

    drawStringARGB32(125, 620, "Type 3 to go back to game's main menu.", 0x0000FF00);
}

void draw_map_preview()
{
    // loop through the 2D map
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            // calculate x1, y1, x2, y2 of every box in the map
            // each box has a width of 25 and height of 24
            int start_x = 115 + (15 * j);
            int end_x = start_x + 15;
            int start_y = 5 + (14 * i);
            int end_y = start_y + 14;

            if (map_data[level].map[i][j] == 1)
            { // if this is a wall
                // draw a bule rectangal
                drawRectARGB32(start_x, start_y, end_x, end_y, map_data[level].color_code, 2);
            }
            else if (i == map_data[level].gate.row && j == map_data[level].gate.col)
            { // if this is a wall
                // draw a bule rectangal
                drawRectARGB32(start_x, start_y, end_x, end_y - 10, map_data[level].color_code, 2);
            }
            else if (map_data[level].map[i][j] == 5)
            { // teleport gate
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, teleport_gate);
            }
            else if (map_data[level].map[i][j] != -1 && map_data[level].map[i][j] != 0)
            {
                // draw the food
                // the food is place in the middle of the reactangle
                // the food has a width of 8 and a height of 6
                int food_start_x = (start_x + end_x) / 2 - 4;
                int food_end_x = (start_x + end_x) / 2 + 4;
                int food_start_y = (start_y + end_y) / 2 - 3;
                int food_end_y = (start_y + end_y) / 2 + 3;
                drawRectARGB32(food_start_x, food_start_y, food_end_x, food_end_y, 0xFFFFAA88, 1);
            }
        }
    }
}

void display_statistic_overall()
{
    drawStringARGB32(120, 380, "Highest score", 0x00FFFF00);
    char *str_highest_score = "";
    copyString(str_highest_score, numDisplay(map_data[level].highest_score));
    displayNumber(250, 380, 10, str_highest_score, 0x00FFFF00);

    if (map_data[level].mission1.is_done)
    {
        drawObjectARGB32(120, 430, 32, 32, star_fill_icon);
    }
    else
    {
        drawObjectARGB32(120, 430, 32, 32, star_icon);
    }
    drawStringARGB32(200, 446, map_data[level].mission1.description, 0x00FFFF00);

    if (map_data[level].mission2.is_done)
    {
        drawObjectARGB32(120, 480, 32, 32, star_fill_icon);
    }
    else
    {
        drawObjectARGB32(120, 480, 32, 32, star_icon);
    }
    drawStringARGB32(200, 496, map_data[level].mission2.description, 0x00FFFF00);

    if (map_data[level].mission3.is_done)
    {
        drawObjectARGB32(120, 530, 32, 32, star_fill_icon);
    }
    else
    {
        drawObjectARGB32(120, 530, 32, 32, star_icon);
    }
    drawStringARGB32(200, 546, map_data[level].mission3.description, 0x00FFFF00);
}

void get_map()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            map[i][j] = map_data[level].map[i][j];
        }
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

            if (map_data[level].map[i][j] == 1)
            { // if this is a wall
                // draw a bule rectangal
                drawRectARGB32(start_x, start_y, end_x, end_y, map_data[level].color_code, 2);
            }
            else if (map_data[level].map[i][j] == 2 || map_data[level].map[i][j] == 3)
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
            else if (i == map_data[level].gate.row && j == map_data[level].gate.col)
            { // if this is a wall
                // draw a bule rectangal
                drawRectARGB32(start_x, start_y, end_x, end_y - 16, map_data[level].color_code, 2);
            }
            else if (map_data[level].map[i][j] == 5)
            { // teleport gate
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, teleport_gate);
            }
            else if (map_data[level].map[i][j] == 6)
            { // freeze ghost
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, freeze_ghosts_food);
            }
            else if (map_data[level].map[i][j] == 7)
            { // reversed food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, reverse_food);
            }
            else if (map_data[level].map[i][j] == 8)
            { // double score
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, double_score_food);
            }
            else if (map_data[level].map[i][j] == 9)
            { // invisible food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, invisible_food);
            }
            else if (map_data[level].map[i][j] == 10)
            { // power_food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, power_food);
            }
            else if (map_data[level].map[i][j] == 11)
            { // speed_up food
                // draw a black rectangle
                drawRectARGB32(start_x, start_y, end_x, end_y, 0xFF000000, 1);

                int food_start_x = (start_x + end_x) / 2 - 8;
                int food_start_y = (start_y + end_y) / 2 - 8;
                drawObjectARGB32(food_start_x, food_start_y, 16, 16, speed_up_food);
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

void game_init()
{
    scatter_mode = 1;
    chase_mode = 0;
    frighten_mode = 0;
    total_food = 0;
    total_points = 0;
    total_ghosts_eaten = 0;
    total_special_foods_eaten = 0;
    is_all_out_of_house = 0;
    end_game = 0;
    cnt = 0;
    ghost_speed = 15;
    total_moves = 0;
}

void game(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky)
{
    get_map();
    // draw the map
    draw_map();
    draw_ghost(&pinky);
    draw_ghost(&blinky);
    draw_ghost(&clyde);
    draw_ghost(&inky);
    // uart_sendc(total_food); total_food is correct
    char *str_total_points = "";
    // char *str_threshold = "";
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
            // Bonus points
            if (total_moves < BONUS_MOVES && total_food == 0)
            {
                total_points += (300 - total_moves) * FOOD_POINTS;
            }
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

        // if there is an input key
        if (uart_isReadByteReady() == 0)
        {
            // get the input and execute
            char c = uart_getc();
            move_pacman(&pacman, &pinky, &blinky, &clyde, &inky, c);
            total_moves++;
            if (!is_all_out_of_house && pinky.is_move == 0)
            {
                pinky.is_move = 1;
            }
        }

        // animate the pacman
        draw_pacman(&pacman);

        if (pinky.is_move && cnt % ghost_speed == 0)
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
                // After scatter_duration, change to chase mode
                if (((cnt - (map_data[level].scatter_duration * 1000 / 20)) % ((map_data[level].scatter_duration + map_data[level].scatter_duration) * 1000 / 20) == 0 &&
                     scatter_mode == 1))
                {
                    // uart_puts("chase\n");
                    scatter_mode = 0;
                    chase_mode = 1;
                }
                else if (cnt % ((map_data[level].scatter_duration + map_data[level].chase_duration) * 1000 / 20) == 0 && chase_mode == 1)
                { // After chase_duration, back to scatter mode
                    // uart_puts("scatter\n");
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
            total_points += FOOD_POINTS * 4;

            copyString(str_total_points, numDisplay(total_points));

            displayNumber(850, 600, 10, str_total_points, 0xFFFFFF);

            return 1;
        }
    }
    return 0;
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

void handle_special_food(Pacman *pacman, Ghost *pinky, Ghost *blinky, Ghost *clyde, Ghost *inky)
{
    int x_offset = 0;

    if (!pacman->special_foods.active)
    {
        for (int i = 0; i < 5; i++)
        {
            clearObject(10 + i * 40, 572, 32, 32);
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

        clock(&freeze_ghosts_time, &freeze_ghosts_time_track);
        if (!freeze_ghosts_time)
        {
            // freeze_ghosts_time = 15; // Reset time for next time pacman eat that item
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

        clock(&reversed_time, &reversed_time_track);
        if (!reversed_time)
        {
            // reversed_time = 15; // Reset time for next time pacman eat that item
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

        clock(&invisible_time, &invisible_time_track);
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

        clock(&power_up_time, &power_up_time_track);
        if (!power_up_time)
        {
            disable_frighten_mode(pinky, blinky, clyde, inky);
            // power_up_time = 10; // Reset time for next time pacman eat that item
            clearObject(10 + x_offset * 40, 572, 32, 32);
            pacman->special_foods.active--;
            pacman->special_foods.power_up = 0;
        }
    }

    if (pacman->special_foods.double_score)
    {
        if (x_offset < pacman->special_foods.active)
        {
            // set_wait_timer(1, 10);
            drawObjectARGB32(10 + x_offset * 40, 572, 32, 32, double_score_food_icon);
            // set_wait_timer(0, 10);
            x_offset++;
        }

        clock(&double_score_time, &double_score_time_track);
        if (!double_score_time)
        {
            // double_score_time = 10; // Reset time for next time pacman eat that item
            clearObject(10 + x_offset * 40, 572, 32, 32);
            pacman->special_foods.active--;
            pacman->special_foods.double_score = 0;
        }
    }

    if (pacman->special_foods.speed_up)
    {
        if (x_offset < pacman->special_foods.active)
        {
            // set_wait_timer(1, 10);
            drawObjectARGB32(10 + x_offset * 40, 572, 32, 32, speed_up_food_icon);
            // set_wait_timer(0, 10);
            x_offset++;
        }

        clock(&speed_up_time, &speed_up_time_track);
        if (!speed_up_time)
        {
            // speed_up_time = 10; // Reset time for next time pacman eat that item
            ghost_speed = 15;
            clearObject(10 + x_offset * 40, 572, 32, 32);
            pacman->special_foods.active--;
            pacman->special_foods.speed_up = 0;
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
        if (stage == 1 && cnt % 10 == 0 && result_row > 1)
        {
            result_row -= 1;
            display_ending_result(result_col, result_row);
            if (result_row == 1)
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
            }
        }
        if (wait == 0 && cnt % 5 == 0 && time <= total_moves && statistic == 3)
        {
            display_statistic(statistic, time);
            time++;
            if (time > total_moves)
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
            if (time > total_points)
            {
                if (map_data[level].highest_score == total_points)
                {
                    drawStringARGB32(485, 325, "New!", 0x00FF0000);
                }
                stage++;
                time = 0;
                wait = 200;
            }
        }
        if (wait == 0 && stage == 4 && cnt % 200 == 0)
        {
            display_rating(time);
            time++;
            if (time > 5)
            {
                // Data logging
                uart_puts("Total moves in this game: ");
                uart_dec(total_moves);
                uart_puts("\n");

                drawStringARGB32(120, 560, "Type 1 to replay this level.", 0x0000FF00);
                drawStringARGB32(120, 590, "Type 2 to go to level selection.", 0x0000FF00);
                drawStringARGB32(120, 620, "Type 3 to go back to game's main menu.", 0x0000FF00);
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
        drawStringARGB32(240, 330 / 13.0f * row, "You Won", 0x0000FF00);
    }
}

void display_statistic(int value, int time)
{
    switch (value)
    {
    case 0: // Total foods
        if (time == 0)
        {
            drawStringARGB32(120, 80, "Total foods eaten", 0x00FFFF00);
            if (total_food == 0 && !map_data[level].mission1.is_done)
            {
                map_data[level].mission1.is_done = 1;
            }
        }
        char *str_total_foods_eaten = "";
        displayNumber(400, 80, 10, str_total_foods_eaten, 0x00000000);
        copyString(str_total_foods_eaten, numDisplay(time));
        displayNumber(400, 80, 10, str_total_foods_eaten, 0x00FFFF00);
        break;
    case 1: // Special foods consume
        if (time == 0)
        {
            drawStringARGB32(120, 130, "Total special foods eaten", 0x00FFFF00);
        }
        char *str_total_special_foods_eaten = "";
        displayNumber(400, 130, 10, str_total_special_foods_eaten, 0x00000000);
        copyString(str_total_special_foods_eaten, numDisplay(time));
        displayNumber(400, 130, 10, str_total_special_foods_eaten, 0x00FFFF00);
        break;
    case 2: // Ghosts eaten
        if (time == 0)
        {
            drawStringARGB32(120, 180, "Total ghosts caught", 0x00FFFF00);
            if (total_food == 0 && !map_data[level].mission3.is_done && total_ghosts_eaten >= map_data[level].mission3.goal)
            {
                map_data[level].mission3.is_done = 1;
            }
        }
        char *str_total_ghosts_eaten = "";
        displayNumber(400, 180, 10, str_total_ghosts_eaten, 0x00000000);
        copyString(str_total_ghosts_eaten, numDisplay(time));
        displayNumber(400, 180, 10, str_total_ghosts_eaten, 0x00FFFF00);
        break;
    case 3: // Totoal moves
        if (time == 0)
        {
            drawStringARGB32(120, 230, "Total moves", 0x00FFFF00);
        }
        char *str_total_moves = "";
        displayNumber(400, 230, 10, str_total_moves, 0x00000000);
        copyString(str_total_moves, numDisplay(time));
        displayNumber(400, 230, 10, str_total_moves, 0x00FFFF00);
        break;
    default: // Total score
        if (time == 0)
        {
            if (total_points > map_data[level].highest_score)
            {
                map_data[level].highest_score = total_points;
            }
            if (!map_data[level].mission2.is_done && total_points >= map_data[level].mission2.goal)
            {
                map_data[level].mission2.is_done = 1;
            }
            for (int i = 3; i < 18; i++)
            {
                drawRectARGB32(10 + i * 25, 10 + 11 * 24, 10 + i * 25 + 24, 10 + 11 * 24 + 5, 0x00FFFF00, 1);
            }
            drawStringARGB32(120, 325, "Total score", 0x00FFFF00);
        }
        char *str_total_points = "";
        displayNumber(400, 325, 10, str_total_points, 0x00000000);
        copyString(str_total_points, numDisplay(time));
        displayNumber(400, 325, 10, str_total_points, 0x00FFFF00);
        break;
    }
}

void display_rating(int value)
{
    switch (value)
    {
    case 0:
        drawObjectARGB32(120, 380, 32, 32, star_icon);
        drawStringARGB32(200, 396, "Eat all the foods", 0x00FFFF00);
        break;

    case 1:
        drawObjectARGB32(120, 430, 32, 32, star_icon);
        drawStringARGB32(200, 446, map_data[level].mission2.description, 0x00FFFF00);
        break;

    case 2:
        drawObjectARGB32(120, 480, 32, 32, star_icon);
        drawStringARGB32(200, 496, map_data[level].mission3.description, 0x00FFFF00);
        break;

    case 3:
        if (total_food == 0)
        {
            drawObjectARGB32(120, 380, 32, 32, star_fill_icon);
        }
        break;

    case 4:
        if (total_food == 0 && total_points >= map_data[level].mission2.goal)
        {
            drawObjectARGB32(120, 430, 32, 32, star_fill_icon);
        }
        break;

    default:
        if (total_food == 0 && total_ghosts_eaten >= map_data[level].mission3.goal)
        {
            drawObjectARGB32(120, 480, 32, 32, star_fill_icon);
        }
        break;
    }
}