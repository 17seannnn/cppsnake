#ifndef APPLE_H
#define APPLE_H

#include <curses.h>

#include "curses.h"

class Apple {
    int x, y;
public:
    Apple() : x(-1), y(-1) {}
    ~Apple() {}

    int GetX() const { return x; }
    int GetY() const { return y; }
    void Spawn();
private:
    void Show() { mvwaddch(curses.game_win, y, x, '@'); }
    void Hide() { mvwaddch(curses.game_win, y, x, ' '); }
};

#endif
