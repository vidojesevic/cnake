#include "../include/screen.h"
#include <math.h>
#include <curses.h>

WINDOW *init_screen() {
    WINDOW *window = initscr();
    keypad(window, true);
    nodelay(window, true);
    curs_set(0);

    return window;
}

void print_border(ScreenX *screen, int score) {
    // Corners
    mvprintw(0, 0, "+");
    mvprintw(0, screen->x - 1, "+");
    mvprintw(screen->y - 1, 0, "+");
    mvprintw(screen->y - 1, screen->x - 1, "+");

    char title[32];
    sprintf(title, "]>Cnake<[Score: %d<[", score);
    int length = sizeof(title)/sizeof(title[0]);
    // Top border
    for (int i = 1; i < screen->x - 1; ++i) {
        if (i == screen->x/2 - (int)(length / 2)) {
            mvprintw(0, i, title);
            i += length;
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
