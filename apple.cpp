#include <stdlib.h>

#include "curses.h"

#include "apple.h"

void Apple::Spawn() {
    if (x != -1)
        Hide();
    x = rand() % curses.game_win_width;
    y = rand() % curses.game_win_height;
    Show();
}
