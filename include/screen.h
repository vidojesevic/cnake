#define SCREEN_H_IMPLEMENTATION
#ifdef SCREEN_H_IMPLEMENTATION

#include <curses.h>

typedef struct screen {
    int x;
    int y;
} Screen;

WINDOW *init_screen(void);
void print_border(Screen *screen);

#endif
