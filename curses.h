#ifndef COMMON_H
#define COMMON_H

#include <curses.h>

struct Curses {
    enum color_pairs {
        snake_pair = 1,
        apple_pair,
        msg_pair,
        score_pair
    };

    int score_win_width, score_win_height;   // Read-only
    int screen_win_width, screen_win_height; // Read-only
    int game_win_width,  game_win_height;    // Read-only

    WINDOW* score_win;  // Current score
    WINDOW* screen_win; // Borders
    WINDOW* game_win;   // Game without borders

    Curses() {}
    ~Curses();

    void Init();
    void Refresh();
};

extern Curses curses;

#endif
