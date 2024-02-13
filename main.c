#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/snake.h"

int speed = 125000;
#define VERSION "v1.0"

int score = 0;
vec2 snake[256];
void print_version(const char *version);
void handle_pause(bool paused);

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
        print_version(VERSION);
    } else if (strcmp(argv[1], "-s") == 0 && argc == 3) {
        if (strcmp(argv[2], "normal") == 0) speed = 125000;
        if (strcmp(argv[2], "fast") == 0) speed = 80000;
        if (strcmp(argv[2], "faster") == 0) speed = 60000;
    }

    WINDOW *window = init_screen();
    ScreenX screen = {.x = 0, .y = 0};

    getmaxyx(window, screen.y, screen.x);
    print_border(&screen, score);

    vec2 food = {
        .x = 1 + rand() % (screen.x / 2 - 2),
        .y = 1 + rand() % (screen.y - 2)
    };

    vec2 dir = {
        .x = 1,
        .y = 0
    };

    vec2 position = {.x = 1, .y = 1};
    bool paused = false;

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
        // escape == game over
        if (key == 27) {
            paused = !paused;
        }

        if (paused) {
            mvaddstr(screen.y, screen.x * 2, "Paused");
            continue;
        }

        // Update
        for (int i = score; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        snake[0] = position;

        position.x += dir.x;
        position.y += dir.y;

        if (food.x == position.x && food.y == position.y) {
            score++;
            food.x = 1 + rand() % (screen.x / 2 - 2);
            food.y = 1 + rand() % (screen.y - 2);
        }

        // Drawing
        erase();
        mvaddch(food.y, food.x * 2, '@');

        // Draw snake
        for (int i = 0; i < score; i++) {
            mvaddch(snake[i].y, snake[i].x * 2, '*');
            if (snake[i].y == position.y && snake[i].x == position.x) {
                gameover(score);
                return 0;
            }
        }
        mvaddch(position.y, position.x * 2, '0');

        usleep(speed);
        print_border(&screen, score);
    }

    printf("Position: x = %d, Y = %d\n", position.x, position.y);

    gameover(score);
    return 0;
}

void print_version(const char *version) {
    printf("Cnake | Simple terminal snake game in C\nVersion: %s-stable\nCreator: Vidoje Sevic\n", version);
    printf("Usage: ./build/snake -s normal/fast/faster\n");
    exit(EXIT_FAILURE);
}
