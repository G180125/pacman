#include "uart.h"
#include "mbox.h"
#include "framebf.h"
 #include "timer_and_interrupt.h"
volatile int moving;
unsigned long _regs[38];

void drawBackground()
{
    drawRectARGB32(0, 0, 1023, 767/2, 0x00FFFFFF, 1); 
    drawRectARGB32(0, 767/2, 1023, 767, 0x00000000, 1);
}
void drawCar(int in)
{
    drawRectARGB32(0 + in, 200, 200 + in, 350, 0x000000CC, 1);
    drawCircleARGB32(0 + in, 350, 40, 0xFFA500);
    drawCircleARGB32(200 + in, 350, 40, 0xFFA500);
}
void main()
{

    // set up serial console
    uart_init();
    // say hello
    uart_puts("\n\nHello World!\n");
    // Initialize frame buffer
    framebf_init();
  drawBackground();
    uart_init();
    enable_tmr_irq();
    // welcome from the uart !!!
    int interval = 200;
    int count = 0;
    while (1)
    {
        if(count == 4){ //RESTART THE DRAWING
            count == 0;
        } 
        if (moving)
        {
            drawCar(interval * count);
            moving = 0;
            count++;
        }
         drawBackground(); //clear 
    }
}
