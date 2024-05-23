#define NULL ((void *)0)
#ifndef _SIZE_T_DEFINED
#ifdef  _WIN64
typedef unsigned __int64    size_t;
#else
typedef unsigned int        size_t;
#endif
#define _SIZE_T_DEFINED
#endif

typedef struct {
    int distance;
    int direction;
} PriorityQueue;

int string_length(const char *str);
int get_font_index(char character);
int sqrt_int(int n);
int pow_int(int base, int exponent);
int calculate_distance(int x1, int y1, int x2, int y2);
unsigned int random_number();
unsigned random_small_number();
int distance_square(int x0, int y0, int x1, int y1);
void bubbleSort(PriorityQueue arr[], int n);
int stringcompare(char *a, char *b);
void *memcpy(void *restrict dest, const void *restrict src, size_t len);
char *numDisplay(int input);
void copyString(char *t, char *s);
void clearString(char* str, int bufferSize);
char* reverseString(char* str);
