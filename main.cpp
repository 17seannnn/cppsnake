#include <stdio.h>

#include "curses.h"
#include "game.h"

Curses curses;

int main() {
    try {
        curses.Init();
        for (;;) {
            Game game;
            game.Start();
            break;
        }
        return 0;
    } catch (const char* s) {
        fprintf(stderr, "%s\n", s);
    }
    return 1;
}
