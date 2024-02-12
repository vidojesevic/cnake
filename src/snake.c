#include "../include/snake.h"
#include <curses.h>
#include <stdlib.h>
#include <time.h>

void randomize_food(vec2 *food) {
    time_t t;
    srand((unsigned) time(&t));

    int x = rand() % 50;
    int y = rand() % 50;

    // food->x = x == 0 || screen->x ? rand() % 20 : x;
    // food->y = y == 0 || screen->y ? rand() % 20 : y;
    food->x = x;
    food->y = y;
}
