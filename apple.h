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

    int GetX() const;
    int GetY() const;
    void Spawn();
private:
    void Show() const;
    // Apple doesn't need to hide itself, because snake will cover it
};

int Apple::GetX() const {
    return x;
}

int Apple::GetY() const {
    return y;
}

inline void Apple::Spawn() {
    x = rand() % curses.game_win_width;
    y = rand() % curses.game_win_height;
    Show();
}

inline void Apple::Show() const {
    mvwaddch(curses.game_win, y, x, ' ' | COLOR_PAIR(curses.apple_pair));
}

#endif
