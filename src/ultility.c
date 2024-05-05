#include "ultility.h"
#include "uart0.h"

int string_length(const char *str){
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

// Comparing both the strings using pointers
int stringcompare(char *a, char *b)
{
    int flag = 0;
    int index = 0;
    if (string_length(a) != string_length(b))
    { // IF THE LENGTH IS NOT THE SAME
        return 1;
    }
    while (a[index] != '\0' && b[index] != '\0') // while loop
    {
        if (a[index] != b[index])
        {
            flag = 1;
            break;
        }
        index++;
    }

    if (flag == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int get_font_index(char character) {
    int ascii_value = (int)character;
    // Check if the character is within the ASCII range of your font
    if (ascii_value >= 0 && ascii_value < 224) {
        return ascii_value;
    } else {
        // Return an index for an undefined character
        return -1;
    }
}

int sqrt_int(int n) {
    int x = n;
    int y = 1;
    while (x > y) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

// Calculate power of an integer
int pow_int(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int calculate_distance(int x1, int y1, int x2, int y2){
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt_int(pow_int(dx, 2) + pow_int(dy, 2));
}

unsigned int random_number() {
    static unsigned int seed = 0;
    seed = (seed * 1103515245 + 12345) & 0x7fffffff; // Linear congruential generator formula
    return seed;
}

int distance_square(int x0, int y0, int x1, int y1) {
    return (x1-x0) * (x1-x0) + (y1-y0) * (y1-y0);
}

// Function to swap two elements in the array
void swap(PriorityQueue *a, PriorityQueue *b) {
    PriorityQueue temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort function to sort the array of structs
void bubbleSort(PriorityQueue arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            // Compare first variables
            if (arr[j].distance < arr[j+1].distance) {
                swap(&arr[j], &arr[j+1]);
            }
            // If first variables are equal, compare second variables
            else if (arr[j].distance == arr[j+1].distance && arr[j].direction < arr[j+1].direction) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}