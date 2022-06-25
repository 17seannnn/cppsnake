#ifndef APPLE_H
#define APPLE_H

#include <curses.h>
#include <stdlib.h>

#include "curses.h"

class Apple {
    int x, y;
public:
    Apple() : x(-1), y(-1) {}
    ~Apple() {}

    int GetX() const { return x; }
    int GetY() const { return y; }
    void Spawn() {
        x = rand() % curses.game_win_width;
        y = rand() % curses.game_win_height;
        Show();
    }
private:
    void Show() const { mvwaddch(curses.game_win, y, x, ' ' | COLOR_PAIR(curses.apple_pair)); }
    // Apple doesn't need to hide itself, because snake will cover it
};

#endif
