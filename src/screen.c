#include "../include/screen.h"
#include <curses.h>

WINDOW *init_screen() {
    WINDOW *window = initscr();
    keypad(window, true);
    nodelay(window, true);
    curs_set(0);

    return window;
}

void print_border(Screen *screen) {
    // Corners
    mvprintw(0, 0, "+");
    mvprintw(0, screen->x - 1, "+");
    mvprintw(screen->y - 1, 0, "+");
    mvprintw(screen->y - 1, screen->x - 1, "+");

    // Top border
    for (int i = 1; i < screen->x - 1; ++i) {
        if (i == screen->x/2 - 5) {
            mvprintw(0, i, "|>CNAKES<|");
            i += 9;
            continue;
        }
        mvprintw(0, i, "-");
    }

    // Bottom border
    for (int i = 1; i < screen->x - 1; ++i)
        mvprintw(screen->y - 1, i, "-");

    // Left border
    for (int i = 1; i < screen->y - 1; ++i)
        mvprintw(i, 0, "|");

    // Right border
    for (int i = 1; i < screen->y - 1; ++i)
        mvprintw(i, screen->x - 1, "|");

    refresh();
}
