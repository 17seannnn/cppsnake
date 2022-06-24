#include <curses.h>

#include "common.h"

static const int min_screen_width = 5;
static const int min_screen_height = 5;

Curses::Curses() {
    initscr();
    if (has_colors()) {
        use_default_colors();
        start_color();
    }
    noecho();
    raw();
    curs_set(0);
    clear();

    int width, height;
    getmaxyx(stdscr, height, width);
    if (width < min_screen_width || height < min_screen_height) {
        endwin();
        throw "Your screen is too small to play this game";
    }

    screen_width = width - 2;
    screen_height = height - 2;
    screen = newwin(1, 1, screen_height, screen_width);
}
