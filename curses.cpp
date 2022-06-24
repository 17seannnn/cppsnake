#include <curses.h>

#include "curses.h"

static const int min_screen_width  = 5;
static const int min_screen_height = 6;

void Curses::Init() {
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
        throw "Increase your terminal size to play";
    }

    // TODO all stuff with win_width/height

    score_win  = newwin(0, 0, 1, width);
    screen_win = newwin(1, 0, height-1, width);
    game_win   = newwin(2, 1, height-3, width-2);

    keypad(game_win, 1);
}

void Curses::Refresh() {
    wnoutrefresh(score_win);
    wnoutrefresh(screen_win);
    wnoutrefresh(game_win);
    doupdate();
}
