#define SNAKE_H_IMPLEMENTATION
#ifdef SNAKE_H_IMPLEMENTATION

#include <curses.h>
#include "screen.h"

typedef struct vec2 {
    int x;
    int y;
} vec2;

void randomize_food(vec2 *food);
void gameover(int score);

#endif
