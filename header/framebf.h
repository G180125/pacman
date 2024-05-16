void framebf_init();
void drawPixelARGB32(int x, int y, unsigned int attr);
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill);
void drawCircleARGB32(int x, int y, int r);
void drawCharARGB32(int x, int y, char c, unsigned int attr);
void drawStringARGB32(int x, int y, char *str, unsigned int attr);
void drawImageARGB32(int x, int y, int starting_x_index, int starting_y_index, unsigned long image[]);
void clearScreen();
void drawObjectARGB32(int x, int y, int frame_width, int frame_height, unsigned long apac[]) ;
void clearObject(int start_x, int start_y, int width, int height);
void displayNumber(int x, int y, int offset, char *input, unsigned int attr);