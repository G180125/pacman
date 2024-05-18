//------------------------------main.h---------------------
#include "framebf.h"
#include "uart0.h"
#include "image.h"
#include "game.h"

#define MAX_SIZE 500
#define preText "Group7> "
char *buffer = "";    // buffer string for input
int buffer_index = 0; // index for buffer string
int case_one = 0;     // flag for case 1 (image viewer)
int restart_flag = 0; // restart flag for game
int threshold = 0;    // goal to win the game

const int SCREEN_WIDTH = 524;
const int SCREEN_HEIGHT = 524;
const int OFFSET = 20;

int y_index = 0;
int x_index = 0;
int session = 0;
int page = 0;

void move_image(char c, int flag);
void intro();
void process(char *input);

void main()
{
    // set up serial console
    uart_init();
    // say hello
    uart_puts("\n\nWELCOME TO GROUP 7 BARE OS, CHECK THE MONITOR FOR INSTRUCTION\n");
    // Initialize frame buffer
    framebf_init();
    uart_puts("UART default state (Baud rate: 115200 , Parity: None, Word length: 8 bits, Stop bit: 1 bit, Handshaking Protocol: None) \n");
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
        session = 0;
    }

    //------------------------------move image---------------------
    else if (stringcompare(buffer, "1") == 0 && session == 0)
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

    //------------------------------game's home screen---------------------
    else if (stringcompare(buffer, "3") == 0 && session == 0)
    {
        clearScreen();
        display_home_screen();
        session = 1;
        uart_puts("\n Type exit to exit out of the game, any button to replay the game");
    }

    //------------------------------select level---------------------
    else if ((stringcompare(buffer, "1") == 0 && session == 1))
    {
        clearScreen();
        level = 0;
        level_preview();
        uart_puts("\n Type exit to exit out of the game, any button to replay the game");
    }
    else if ((stringcompare(buffer, "a") == 0 && session == 1))
    {
        clearScreen();
        if (level > 0)
        {
            level--;
        }
        level_preview();
        uart_puts("\n Type exit to exit out of the game, any button to replay the game");
    }
    else if ((stringcompare(buffer, "d") == 0 && session == 1))
    {
        clearScreen();
        if (level < 4)
        {
            level++;
        }
        level_preview();
        uart_puts("\n Type exit to exit out of the game, any button to replay the game");
    }

    //------------------------------play game---------------------
    else if (((stringcompare(buffer, "\0") == 0) && session == 1) || restart_flag)
    {
        if (level != 0 && !map_data[level - 1].mission1.is_done)
        {
            uart_puts("Please finished previous map by eating all the food first");
        }
        else
        {
            //////////////////////////////////////
            clearScreen();

            uart_puts("\nGame activated\n");

            game_init();

            game(pacman, pinky, blinky, clyde, inky);
            restart_flag = 1;
            uart_puts("\n Type exit to exit out of the game, any button to replay the game");
        }
    }

    //------------------------------see instruction---------------------
    else if (((stringcompare(buffer, "2") == 0) && session == 1))
    {
        clearScreen();
        session = 2;
        page = 0;
        display_instruction(page);
    }
    else if (((stringcompare(buffer, "a") == 0) && session == 2))
    {
        clearScreen();
        clearScreen();
        if (page > 0)
        {
            page--;
        }
        display_instruction(page);
    }
    else if (((stringcompare(buffer, "d") == 0) && session == 2))
    {
        clearScreen();
        clearScreen();
        if (page < 5)
        {
            page++;
        }
        display_instruction(page);
    }

    //------------------------------clear cli---------------------
    else if (stringcompare(buffer, "clear") == 0)
    {
        uart_clear();
    }
    else
    {
        uart_puts("\nError: Unidentified command");
    }
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
