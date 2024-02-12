#include <curses.h>
#include "include/screen.h"
#include "include/snake.h"

int main(void) {
    WINDOW *window = init_screen();
    Screen screen = {.x = getmaxx(window), .y = getmaxy(window)};

    getmaxyx(window, screen.y, screen.x);

    print_border(&screen);

    while (true) {
        //
    }

    endwin();
    return 0;
}
