// ----------------------------------- framebf.c -------------------------------------
#include "mbox.h"
#include "uart0.h"
#include "font.h"
#include "ultility.h"

// Use RGBA32 (32 bits for each pixel)
#define COLOR_DEPTH 32
// Pixel Order: BGR in memory order (little endian --> RGB in byte order)
#define PIXEL_ORDER 0
#define IMAGE_WIDTH 1366

const int FRAME_WIDTH = 640; // Define frame width
const int FRAME_HEIGHT = 320; // Define frame height


//Screen info
unsigned int width, height, pitch;


/* Frame buffer address
 * (declare as pointer of unsigned char to access each byte) */
unsigned char *fb;
/**
 * 
 */
void framebf_init()
{
    mBuf[0] = 35 * 4; // Length of message in bytes
    mBuf[1] = MBOX_REQUEST;
    mBuf[2] = MBOX_TAG_SETPHYWH;  // Set physical width-height
    mBuf[3] = 8;                  // Value size in bytes
    mBuf[4] = 0;                  // REQUEST CODE = 0
    mBuf[5] = 550;       // Value(width)
    mBuf[6] = 650;      // Value(height)
    mBuf[7] = MBOX_TAG_SETVIRTWH; // Set virtual width-height
    mBuf[8] = 8;
    mBuf[9] = 0;
    mBuf[10] = 550;
    mBuf[11] = 650;
    mBuf[12] = MBOX_TAG_SETVIRTOFF; // Set virtual offset
    mBuf[13] = 8;
    mBuf[14] = 0;
    mBuf[15] = 0;                 // x offset
    mBuf[16] = 0;                 // y offset
    mBuf[17] = MBOX_TAG_SETDEPTH; // Set color depth
    mBuf[18] = 4;
    mBuf[19] = 0;
    mBuf[20] = COLOR_DEPTH;         // Bits per pixel
    mBuf[21] = MBOX_TAG_SETPXLORDR; // Set pixel order
    mBuf[22] = 4;
    mBuf[23] = 0;
    mBuf[24] = PIXEL_ORDER;
    mBuf[25] = MBOX_TAG_GETFB; // Get frame buffer
    mBuf[26] = 8;
    mBuf[27] = 0;
    mBuf[28] = 16;                // alignment in 16 bytes
    mBuf[29] = 0;                 // will return Frame Buffer size in bytes
    mBuf[30] = MBOX_TAG_GETPITCH; // Get pitch
    mBuf[31] = 4;
    mBuf[32] = 0;
    mBuf[33] = 0; // Will get pitch value here
    mBuf[34] = MBOX_TAG_LAST;
    // Call Mailbox
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP) // mailbox call is successful ?
        && mBuf[20] == COLOR_DEPTH          // got correct color depth ?
        && mBuf[24] == PIXEL_ORDER          // got correct pixel order ?
        && mBuf[28] != 0                    // got a valid address for frame buffer ?
    )
    {
        /* Convert GPU address to ARM address (clear higher address bits)
         * Frame Buffer is located in RAM memory, which VideoCore MMU
         * maps it to bus address space starting at 0xC0000000.
         * Software accessing RAM directly use physical addresses
         * (based at 0x00000000)
         */
        mBuf[28] &= 0x3FFFFFFF;
        // Access frame buffer as 1 byte per each address
        fb = (unsigned char *)((unsigned long)mBuf[28]);
        uart_puts("Got allocated Frame Buffer at RAM physical address: ");
        uart_hex(mBuf[28]);
        uart_puts("\n");
        uart_puts("Frame Buffer Size (bytes): ");
        uart_dec(mBuf[29]);
        uart_puts("\n");
        width = mBuf[5];  // Actual physical width
        height = mBuf[6]; // Actual physical height
        pitch = mBuf[33]; // Number of bytes per line
    }
    else
    {
        uart_puts("Unable to get a frame buffer with provided setting\n");
    }
}
void drawPixelARGB32(int x, int y, unsigned int attr)
{
    int offs = (y * pitch) + (COLOR_DEPTH / 8 * x);
    /* //Access and assign each byte
     *(fb + offs ) = (attr >> 0 ) & 0xFF; //BLUE (get the least significant byte)
     *(fb + offs + 1) = (attr >> 8 ) & 0xFF; //GREEN
     *(fb + offs + 2) = (attr >> 16) & 0xFF; //RED
     *(fb + offs + 3) = (attr >> 24) & 0xFF; //ALPHA
     */
    // Access 32-bit together
    *((unsigned int *)(fb + offs)) = attr;
}
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill)
{
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
        {
            if ((x == x1 || x == x2) || (y == y1 || y == y2))
                drawPixelARGB32(x, y, attr);
            else if (fill == 2)
            {
                if ((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0))
                {
                    drawPixelARGB32(x, y, attr);
                }
            }
            else if (fill)
            {
                drawPixelARGB32(x, y, attr);
            }
        }
}
void drawCircleARGB32(int x, int y, int r) {
    int d = 3 - (2 * r);
    int drawX = 0;
    int drawY = r;
    
    while (drawX <= drawY) {
        // Draw eight symmetric points for each quadrant
        drawPixelARGB32(x + drawX, y + drawY, 0xFFFFFFFF); // White color
        drawPixelARGB32(x - drawX, y + drawY, 0xFFFFFFFF);
        drawPixelARGB32(x + drawX, y - drawY, 0xFFFFFFFF);
        drawPixelARGB32(x - drawX, y - drawY, 0xFFFFFFFF);
        drawPixelARGB32(x + drawY, y + drawX, 0xFFFFFFFF);
        drawPixelARGB32(x - drawY, y + drawX, 0xFFFFFFFF);
        drawPixelARGB32(x + drawY, y - drawX, 0xFFFFFFFF);
        drawPixelARGB32(x - drawY, y - drawX, 0xFFFFFFFF);
        
        // Update coordinates based on the algorithm
        if (d < 0) {
            d += (4 * drawX) + 6;
        } else {
            d += (4 * (drawX - drawY)) + 10;
            drawY--;
        }
        drawX++;
    }
}
void drawCharARGB32(int x, int y, char ch, unsigned int attr) {
    if (ch >= 32 && ch <= 126) { // Check if the character is printable
        int index = get_font_index(ch); // Calculate the index in the font array
        if (index != -1){
            unsigned char *glyph = font[index]; // Get the glyph data from the font
            for (int row = 0; row < FONT_HEIGHT; row++) {
                unsigned char line = glyph[row];
                for (int col = 0; col < FONT_WIDTH; col++) {
                    if (line & (1 << (col))) {
                        drawPixelARGB32(x + col, y + row, attr); // Draw the pixel
                    }
                }
            }
        }
    }
}
void drawStringARGB32(int x, int y, char *str, unsigned int attr) {
    int len = string_length(str);
    int offset = 0;
    
    for (int i = 0; i < len; i++) {
        char ch = str[i];
        drawCharARGB32(x + offset, y, ch, attr);
        offset += FONT_WIDTH; 
    }
}
void drawImageARGB32(int x, int y, int starting_x_index, int starting_y_index,unsigned long image[]){
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = IMAGE_WIDTH * (i + starting_y_index)  + j + starting_x_index; 
            drawPixelARGB32(x + j, y + i, image[index]);
        }
    }
}

void clearScreen() {
    // Fill the screen with black color
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            drawPixelARGB32(x, y, 0xFF000000); // Black color
        }
    }
}

void drawObjectARGB32(int x, int y, int frame_width, int frame_height, unsigned long apac[]) {
    // Loop through each pixel of the frame
    for (int i = 0; i < frame_height; ++i) {
        for (int j = 0; j < frame_width; ++j) {
            // Calculate the index of the current pixel in the 1D array
            int index = frame_width * i + j;
            
            // Draw the pixel
            drawPixelARGB32(x + j, y + i, apac[index]);
        }
    }
}



void clearObject(int start_x, int start_y, int width, int height) {
    // Fill the screen with black color
    for (int y = start_y; y < start_y + width; ++y) {
        for (int x = start_x; x < start_x + height; ++x) {
            drawPixelARGB32(x, y, 0xFF000000); // Black color
        }
    }
}

//---------------Video Frame helper function------------------------------//
void drawFrameARGB32(unsigned long frame_index[], int x, int y) {
    // Draw the frame
    for (int i = 0; i < FRAME_HEIGHT; ++i) {
        for (int j = 0; j < FRAME_WIDTH; ++j) {
            int index = FRAME_WIDTH * i + j;
            drawPixelARGB32(x + j, y + i, frame_index[index]);
        }
    }
}

// Integer to string conversion function
void int_to_string(int num, char *str) {
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Generate digits in reverse order
    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num);

    // Add negative sign if needed
    if (is_negative) {
        str[i++] = '-';
    }

    // Terminate the string
    str[i] = '\0';

    // Reverse the string
    int len = i;
    for (int j = 0; j < len / 2; j++) {
        char temp = str[j];
        str[j] = str[len - j - 1];
        str[len - j - 1] = temp;
    }
}
typedef int bool;
#define true 1
#define false 0

/// Redefine bool, true, and false without using <stdbool.h>
typedef int bool;
#define true 1
#define false 0
#define va_start(args, param) (args = (va_list)&param + sizeof(param))
#define va_arg(args, type) (*(type*)((args += sizeof(type)) - sizeof(type)))
#define va_end(args) (args = NULL)

typedef char* va_list;
// Function to detect frame names like frame1 to frame15
// Define va_start, va_arg, and va_end macros
#define va_start(args, param) (args = (va_list)&param + sizeof(param))
#define va_arg(args, type) (*(type*)((args += sizeof(type)) - sizeof(type)))
#define va_end(args) (args = NULL)

// Function to detect frame names like frame1 to frame15
bool isFrameName(const char *str) {
    if (str == NULL || str[0] != 'f' || str[1] != 'r' || str[2] != 'a' || str[3] != 'm' || str[4] != 'e') {
        return false;
    }

    int i = 5;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
        i++;
    }

    return true;
}

// Implementation of sprintf
int sprintf(char *str, const char *format, ...) {
    int chars_written = 0;
    int arg_int;
    bool is_reading_num = false;

    // Initialize the variable arguments
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (is_reading_num) {
            if (*format >= '0' && *format <= '9') {
                // Accumulate the integer argument
                arg_int = arg_int * 10 + (*format - '0');
            } else {
                // Handle the format specifier
                int num_chars = 0;
                int temp = arg_int;
                do {
                    temp /= 10;
                    num_chars++;
                } while (temp != 0);

                temp = arg_int;
                for (int i = 0; i < num_chars; i++) {
                    str[chars_written + num_chars - i - 1] = temp % 10 + '0';
                    temp /= 10;
                }
                chars_written += num_chars;
                is_reading_num = false;
            }
        } else {
            if (*format == '%') {
                is_reading_num = true;
                arg_int = va_arg(args, int);
            } else {
                str[chars_written] = *format;
                chars_written++;
            }
        }
        format++;
    }

    // Add null terminator to the string
    str[chars_written] = '\0';

    // End the variable arguments processing
    va_end(args);

    return chars_written;
}






