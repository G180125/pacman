// ----------------------------------- framebf.c -------------------------------------
#include "mbox.h"
#include "uart.h"
// Use RGBA32 (32 bits for each pixel)
#define COLOR_DEPTH 32
// Pixel Order: BGR in memory order (little endian --> RGB in byte order)
#define PIXEL_ORDER 0
// Screen info
unsigned int width, height, pitch;
/* Frame buffer address
 * (declare as pointer of unsigned char to access each byte) */
unsigned char *fb;
/**
 * Set screen resolution to 1024x768
 */
// Contiguous block of memory that stores pixel data
void framebf_init() // initialize the frame buffer (screen setting and frame buffer allocation).
{
    mBuf[0] = 35 * 4; // Length of message in bytes
    mBuf[1] = MBOX_REQUEST;
    ///////////////////////////////////////////////
    mBuf[2] = MBOX_TAG_SETPHYWH; // Set physical width-height (see tags.pdf)
    mBuf[3] = 8;                 // Value size in bytes (see tags.pdf)
    mBuf[4] = 0;                 // REQUEST CODE = 0
    mBuf[5] = 1024;              // Value(width)
    mBuf[6] = 768;               // Value(height)
    ///////////////////////////////////////////////
    mBuf[7] = MBOX_TAG_SETVIRTWH; // Set virtual width-height
    mBuf[8] = 8;
    mBuf[9] = 0;
    mBuf[10] = 1024;
    mBuf[11] = 768;
    //////////////////////////////////////////////
    mBuf[12] = MBOX_TAG_SETVIRTOFF; // Set virtual offset
    mBuf[13] = 8;
    mBuf[14] = 0;
    mBuf[15] = 0; // x offset
    mBuf[16] = 0; // y offset
    ///////////////////////////////////////////////
    mBuf[17] = MBOX_TAG_SETDEPTH; // Set color depth
    mBuf[18] = 4;
    mBuf[19] = 0;
    mBuf[20] = COLOR_DEPTH; // Bits per pixel
    /////////////////////////////////////////////
    mBuf[21] = MBOX_TAG_SETPXLORDR; // Set pixel order
    mBuf[22] = 4;
    mBuf[23] = 0;
    mBuf[24] = PIXEL_ORDER;
    //////////////////////////////////////////
    mBuf[25] = MBOX_TAG_GETFB; // Get frame buffer
    mBuf[26] = 8;
    mBuf[27] = 0;
    mBuf[28] = 16; // alignment in 16 bytes
    mBuf[29] = 0;  // will return Frame Buffer size in bytes
    /////////////////////////////////////////
    mBuf[30] = MBOX_TAG_GETPITCH; // Get pitch
    mBuf[31] = 4;
    mBuf[32] = 0;
    mBuf[33] = 0; // Will get pitch value here
    //////////////////////////////////////
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

/* The function drawPixelARGB32(int x, int y, unsigned int attr) is to draw a single pixel
point at location (x, y) on green with attr is the color setting (32 bits in ARGB32 word order).*/

void drawPixelARGB32(int x, int y, unsigned int attr) // draw a single pixel point at location (x, y) on green with attr is the color setting
{
    int offs = (y * pitch) + (COLOR_DEPTH / 8 * x);
    // Access and assign each byte
    *(fb + offs) = (attr >> 0) & 0xFF;      // BLUE (get the least significant byte)
    *(fb + offs + 1) = (attr >> 8) & 0xFF;  // GREEN
    *(fb + offs + 2) = (attr >> 16) & 0xFF; // RED
    *(fb + offs + 3) = (attr >> 24) & 0xFF; // ALPHA

    // Access 32-bit together
    *((unsigned int *)(fb + offs)) = attr;
}

/*The function drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int
fill) is to draw a rectangle from (x1, y1) to (x2, y2) with color setting attr and option fill

*/
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill)
{
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
        {
            if ((x == x1 || x == x2) || (y == y1 || y == y2))
                drawPixelARGB32(x, y, attr);
            else if (fill)
                drawPixelARGB32(x, y, attr);
        }
}

double sqroot(double square)
{
    double root = square / 3;
    int i;
    if (square <= 0)
        return 0;
    for (i = 0; i < 32; i++)
        root = (root + square / root) / 2;
    return root;
}


void drawCircleARGB32(int x, int y, int r, unsigned int attr) {
    int d = 3 - (2 * r);
    int drawX = 0;
    int drawY = r;
    
    while (drawX <= drawY) {
        // Draw eight symmetric points for each quadrant
        drawPixelARGB32(x + drawX, y + drawY, attr); // White color
        drawPixelARGB32(x - drawX, y + drawY, attr);
        drawPixelARGB32(x + drawX, y - drawY, attr);
        drawPixelARGB32(x - drawX, y - drawY, attr);
        drawPixelARGB32(x + drawY, y + drawX, attr);
        drawPixelARGB32(x - drawY, y + drawX, attr);
        drawPixelARGB32(x + drawY, y - drawX, attr);
        drawPixelARGB32(x - drawY, y - drawX, attr);
        
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

void drawLineARGB32(int x1, int y1, int x2, int y2, unsigned int attr)
{
    int temp_x = x1;
    int temp_y = y1;
    double calculation = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));

    if ((x2 - x1) == 0)
    {
        for (int index = 0; index <= (int)sqroot(calculation); index++)
        {

            drawPixelARGB32(x1, temp_y, attr);
            if (y2 < y1)
            {
                temp_y--;
            }
            else
            {
                temp_y++;
            }
        }
    }

    else if ((y2 - y1) == 0)
        for (int index = 0; index <= (int)sqroot(calculation); index++)
        {
            drawPixelARGB32(temp_x, y1, attr);
            if (x2 < x1)
            {
                temp_x--;
            }
            else
            {
                temp_x++;
            }
        }

    else
    {
        for (int index = 0; index <= (int)sqroot(calculation); index++)
        {
            drawPixelARGB32(temp_x, temp_y, attr);

            if (y2 < y1)
            {
                temp_y--;
            }
            else
            {
                temp_y++;
            }

            if (x2 < x1)
            {
                temp_x--;
            }
            else
            {
                temp_x++;
            }
        }
    }
}
