#include <stdint.h>


typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;


struct Color create_color(uint8_t red, uint8_t green, uint8_t blue);

extern struct Color RED;
extern struct Color GREEN;
extern struct Color BLUE;
extern struct Color WHITE;
extern struct Color BLACK;
extern struct Color YELLOW;