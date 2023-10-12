#include "colors.h"
#include <stdint.h>

struct Color create_color(uint8_t red, uint8_t green, uint8_t blue) {
    struct Color color = {red, green, blue};
    return color;
}

struct Color RED = {255, 0, 0};
struct Color GREEN = {0, 255, 0};
struct Color BLUE = {0, 0, 255};
struct Color WHITE = {255, 255, 255};
struct Color BLACK = {0, 0, 0};
struct Color YELLOW = {255, 255, 0};