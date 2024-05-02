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

int compare_strings(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return 1; // Strings are different
        }
        str1++;
        str2++;
    }
    
    // Check if both strings have reached the end simultaneously
    if (*str1 == '\0' && *str2 == '\0') {
        return 0; // Strings are equal
    } else {
        return 1; // Strings are different lengths
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

