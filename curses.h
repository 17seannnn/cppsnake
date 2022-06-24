#ifndef COMMON_H
#define COMMON_H

#include <curses.h>

class Curses {
    int game_win_width, game_win_height;
    WINDOW* score_win;  // Current score
    WINDOW* screen_win; // Borders
    WINDOW* game_win;   // Game without borders
public:
    Curses() {}
    ~Curses()
        { delwin(score_win); delwin(screen_win); delwin(game_win); endwin(); };

    void Init();
    int GetGameWinWidth()  { return game_win_width; }
    int GetGameWinHeight() { return game_win_height; }
    WINDOW*& GetScoreWin()  { return score_win; }
    WINDOW*& GetScreenWin() { return screen_win; }
    WINDOW*& GetGameWin()   { return game_win; }
};

extern Curses curses;

#endif
