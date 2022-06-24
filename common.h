#ifndef COMMON_H
#define COMMON_H

#include <curses.h>

class Curses {
    int screen_width, screen_height;
    WINDOW* screen;
public:
    Curses();
    ~Curses() { delwin(screen); endwin(); };

    int GetWidth()  { return screen_width; }
    int GetHeight() { return screen_height; }
};

extern Curses curses;

#endif
