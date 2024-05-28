//------------------------------main.h---------------------
#include "framebf.h"
#include "uart0.h"
#include "image.h"
#include "game.h"
#include "timer_and_interrupt.h"
#include "./video/frame1-10.h"
#include "./video/frame11-20.h"
#include "./video/frame21-30.h"
#include "./video/frame31-40.h"
#include "./video/frame41-50.h"
#include "./video/frame51-60.h"
#include "./video/frame61-70.h"
#include "./video/frame71-80.h"
#include "./video/frame81-90.h"
#include "./video/frame91-100.h"
#include "./video/frame101-110.h"
#include "./video/frame111-120.h"
#include "./video/frame121-130.h"
#include "./video/frame131-140.h"
#include "./video/frame141-146.h"

#define MAX_SIZE 500
#define preText "Group7> "
char *buffer = "";    // buffer string for input
int buffer_index = 0; // index for buffer string
int case_one = 0;     // flag for case 1 (image viewer)
int restart_flag = 0; // restart flag for game
int threshold = 0;    // goal to win the game
unsigned long _regs[38];
const int SCREEN_WIDTH = 524;
const int SCREEN_HEIGHT = 524;
const int OFFSET = 20;

int y_index = 0;
int x_index = 0;
int session = 0;
int page = 0;
volatile int is_refresh;
volatile int system_time;

void move_image(char c, int flag);
void intro();
void process();
int draw_video();

void main()
{
    is_refresh = 0;
    system_time = 0;

    uart_init();

    enable_tmr_irq();

    // set up serial console
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
            process();                       // Input processing
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

void process()
{
    if ((stringcompare(buffer, "exit") == 0) ||
        ((stringcompare(buffer, "3") == 0) && session == 1))
    {
        intro();
        buffer = " ";
        buffer_index = 0;
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
        uart_puts("Image Viewer activated, type 3 anytime to exit out of this feature");

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
                    *(buffer + buffer_index) = '\0';     // endline
                    if (stringcompare(buffer, "3") == 0) // clean up here
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
                        uart_puts("\n" preText);
                        buffer_index = 0;
                        buffer = " "; // reset buffer
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
                    else
                    {
                        buffer_index = 0;
                        buffer = " "; // reset buffer
                    }
                }
            }
        }
    }

    //------------------------------video player---------------------
    else if (stringcompare(buffer, "2") == 0 && session == 0)
    {
        buffer_index = 0;
        buffer = " "; // reset buffer
        uart_puts("\nType 3 to back to main menu");
        uart_puts("\n" preText);
        while (draw_video())
        {
            wait_msec(300);
        }

        uart_puts("\nThank you for viewing our video\n");
        intro();
    }

    //------------------------------game's home screen---------------------
    else if (stringcompare(buffer, "3") == 0)
    {
        clearScreen();
        display_home_screen();
        session = 1;
        uart_puts("\n Type 1 to play game");
        uart_puts("\n Type 2 to see instruction");
        uart_puts("\n Type 3 to exit game");
    }

    //------------------------------select level---------------------
    else if ((stringcompare(buffer, "1") == 0 && session == 1) ||
             ((stringcompare(buffer, "2") == 0) && session == 3))
    {
        clearScreen();
        level = 0;
        session = 2;
        level_preview();
        uart_puts("\n Type a/d to view level's detail");
        uart_puts("\n Press enter to play selected level");
        uart_puts("\n Type 3 to move back to game's home screen.");
    }
    else if ((stringcompare(buffer, "a") == 0 && session == 2))
    {
        clearScreen();
        if (level > 0)
        {
            level--;
        }
        level_preview();
        uart_puts("\n Type a/d to view level's detail");
        uart_puts("\n Press enter to play selected level");
        uart_puts("\n Type 3 to move back to game's home screen.");
    }
    else if ((stringcompare(buffer, "d") == 0 && session == 2))
    {
        clearScreen();
        if (level < 4)
        {
            level++;
        }
        level_preview();
        uart_puts("\n Type a/d to view level's detail");
        uart_puts("\n Press enter to play selected level");
        uart_puts("\n Type 3 to move back to game's home screen.");
    }

    //------------------------------play game---------------------
    else if (((stringcompare(buffer, "\0") == 0) && session == 2) ||
             ((stringcompare(buffer, "1") == 0) && session == 3))
    {
        if (level != 0 && !map_data[level - 1].mission1.is_done)
        {
            uart_puts("Finished previous map by eating all the food to unlock this map");
            uart_puts("\n Type a/d to view level's detail");
            uart_puts("\n Type 3 to move back to game's home screen.");
        }
        else
        {
            session = 3;
            //////////////////////////////////////
            clearScreen();

            uart_puts("\nGame activated\n");
            uart_puts("\nPress w/a/s/d to move around the maze\n");
            framebf_init();
            game_init();

            game(pacman, pinky, blinky, clyde, inky);
            uart_puts("\n Type 1 to replay this level");
            uart_puts("\n Type 2 to go to level selection");
            uart_puts("\n Type 3 to go back to game's main menu");
        }
    }

    //------------------------------see instruction---------------------
    else if (((stringcompare(buffer, "2") == 0) && session == 1))
    {
        clearScreen();
        session = 4;
        page = 0;
        display_instruction(page);
        uart_puts("\n Type a/d to move between instructions.");
        uart_puts("\n Type 3 to move back to game's home screen.");
    }
    else if (((stringcompare(buffer, "a") == 0) && session == 4))
    {
        clearScreen();
        clearScreen();
        if (page > 0)
        {
            page--;
        }
        display_instruction(page);
        uart_puts("\n Type a/d to move between instructions.");
        uart_puts("\n Type 3 to move back to game's home screen.");
    }
    else if (((stringcompare(buffer, "d") == 0) && session == 4))
    {
        clearScreen();
        clearScreen();
        if (page < 4)
        {
            page++;
        }
        display_instruction(page);
        uart_puts("\n Type a/d to move between instructions.");
        uart_puts("\n Type 3 to move back to game's home screen.");
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

// Function to draw video
int draw_video()
{
    clearScreen();

    unsigned long *frames[] = {frame1, frame2, frame3, frame4, frame5, frame6, frame7, frame8, frame9, frame10, frame11, frame12, frame13, frame14, frame15, frame16, frame17, frame18, frame19, frame20, frame21, frame22, frame23, frame24, frame25, frame26, frame27, frame28, frame29, frame30, frame31, frame32, frame33, frame34, frame35, frame36, frame37, frame38, frame39, frame40, frame41, frame42, frame43, frame44, frame45, frame46, frame47, frame48, frame49, frame50, frame51, frame52, frame53, frame54, frame55, frame56, frame57, frame58, frame59, frame60, frame61, frame62, frame63, frame64, frame65, frame66, frame67, frame68, frame69, frame70, frame71, frame72, frame73, frame74, frame75, frame76, frame77, frame78, frame79, frame80,
                               frame81, frame82, frame83, frame84, frame85, frame86, frame87, frame88, frame89, frame90, frame91, frame92, frame93, frame94, frame95, frame96, frame97, frame98,
                               frame99, frame100, frame101, frame102, frame103, frame104, frame105, frame106, frame107, frame108, frame109, frame110, frame111, frame112, frame113, frame114,
                               frame115, frame116, frame117, frame118, frame119, frame120, frame121, frame122, frame123, frame124, frame125, frame126, frame127, frame128, frame129, frame130, frame131,
                               frame132, frame133, frame134, frame135, frame136, frame137, frame138, frame139, frame140, frame141, frame142, frame143, frame144, frame145, frame146};

    int num_frames = sizeof(frames) / sizeof(frames[0]);
    // Draw each frame with a delay
    for (int i = 0; i < num_frames; i++)
    {
    
            // Call drawFrameARGB32 with the appropriate frame data and coordinates
            drawFrameARGB32(frames[i], 0, 0); // Assuming (0, 0) as the top-left corner
            // Delay to control the frame rate (assuming 3 frames per second)
            if (uart_isReadByteReady() == 0)
            {
                char c1 = uart_getc();
                uart_sendc(c1); // send back to terminal
                if (c1 == 10)
                {
                    *(buffer + buffer_index) = '\0';     // endline
                    if (stringcompare(buffer, "3") == 0) // clean up here
                    {
                        clearScreen();
                        case_one = 0;
                        return 0;
                        // break;
                    }
                    else
                    {
                        uart_puts("\nError: Unidentified command");
                        uart_puts("\n" preText);
                        buffer_index = 0;
                        buffer = " "; // reset buffer
                    }
                }
                else
                {
                    *(buffer + buffer_index) = c1;
                    buffer_index++;
                }
            }
            is_refresh = 0;
        }
      
    
    return 1;
}
