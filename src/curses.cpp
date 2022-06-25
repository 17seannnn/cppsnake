#include <curses.h>

#include "curses.h"

static const int min_screen_width  = 32;
static const int min_screen_height = 16;

Curses::~Curses() {
    delwin(score_win);
    delwin(screen_win);
    delwin(game_win);
    endwin();
}

void Curses::Init() {
    // Basics
    initscr();
    if (has_colors()) {
        use_default_colors();
        start_color();
    }
    noecho();
    raw();
    curs_set(0);
    clear();

    // Windows
    int width, height;
    getmaxyx(stdscr, height, width);
    if (width < min_screen_width || height < min_screen_height) {
        endwin();
        throw "Increase your terminal size to play";
    }

    score_win_width  = width;
    score_win_height = 1;
    screen_win_width  = width;
    screen_win_height = height - 1;
    game_win_width  = width - 2;
    game_win_height = height - 3;

    score_win  = newwin(score_win_height, score_win_width, 0, 0);
    screen_win = newwin(screen_win_height, screen_win_width, 1, 0);
    game_win   = newwin(game_win_height, game_win_width, 2, 1);

    keypad(game_win, true);
    wtimeout(game_win, 0);

    // Colors
    init_pair(snake_pair, -1, COLOR_GREEN);
    init_pair(apple_pair, -1, COLOR_RED);
    init_pair(msg_pair, -1, COLOR_BLUE);
    init_pair(score_pair, -1, COLOR_CYAN);
}

void Curses::Refresh() {
    wnoutrefresh(score_win);
    wnoutrefresh(screen_win);
    wnoutrefresh(game_win);
    doupdate();
}
