#include "game.h"

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

void game(Pacman pacman, Ghost pinky, Ghost blinky, Ghost clyde, Ghost inky)
{
    // clearScreen();
    // draw the map
    draw_map(map);
    draw_ghost(&pinky);
    draw_ghost(&blinky);
    draw_ghost(&clyde);
    draw_ghost(&inky);
    int cnt = 0;
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
            if (time > total_points)
            {
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
            for (int i = 3; i < 18; i++)
            {
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

void display_rating(int value)
{
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
        if (total_food == 0)
        {
            drawObjectARGB32(120, 350, 32, 32, star_fill_icon);
        }
        break;

    case 4:
        if (total_points >= 1100)
        {
            drawObjectARGB32(120, 400, 32, 32, star_fill_icon);
        }
        break;

    default:
        if (total_ghosts_eaten >= 4)
        {
            drawObjectARGB32(120, 450, 32, 32, star_fill_icon);
        }
        break;
    }
}