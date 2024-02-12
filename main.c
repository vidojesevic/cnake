#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/snake.h"

int score = 0;
vec2 snake[256];

int main(void) {
    WINDOW *window = init_screen();
    ScreenX screen = {.x = 40, .y = 20};

    getmaxyx(window, screen.y, screen.x);
    print_border(&screen);

    vec2 food = {
        .x = rand() % 20,
        .y = rand() % 20
    };

    vec2 dir = {
        .x = 1,
        .y = 0
    };
    vec2 position = {.x = 1, .y = 1};

    while (true) {
        int key = wgetch(window);
        if (key == KEY_LEFT) {
            if (dir.x == 1) continue;
            dir.x = -1;
            dir.y = 0;
        }
        if (key == KEY_RIGHT) {
            if (dir.x == -1) continue;
            dir.x = 1;
            dir.y = 0;
        }
        if (key == KEY_UP) {
            if (dir.y == -1) continue;
            dir.x = 0;
            dir.y = -1;
        }
        if (key == KEY_DOWN) {
            if (dir.y == 1) continue;
            dir.x = 0;
            dir.y = 1;
        }
        if (key == 27) {
            break;
        }

        // Snake
        for (int i = score; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        snake[0].x = position.x;
        snake[0].y = position.y;

        position.x += dir.x;
        position.y += dir.y;

        if (food.x == position.x && food.y == position.y) {
            score++;
            food.x = rand() % 20;
            food.y = rand() % 20;
        }

        erase();
        mvaddch(food.y, food.x * 2, "@");

        // Draw snake
        for (int i = 0; i < score; i++) {
            mvaddch(snake[i].y, snake[i].x * 2, '*');
        }
        mvaddch(position.y, position.x * 2, "0");

        usleep(125000);
        print_border(&screen);
    }

    printf("Position: x = %d, Y = %d\n", position.x, position.y);

    endwin();
    printf("Score: %d\n", score);
    return 0;
}
