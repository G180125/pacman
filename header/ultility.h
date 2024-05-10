#define NULL ((void *)0)

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
int distance_square(int x0, int y0, int x1, int y1);
void bubbleSort(PriorityQueue arr[], int n);
int stringcompare(char *a, char *b);
void copyArray(int t[], int s[]);
void memcpy(void *dest, const void *src, int n);