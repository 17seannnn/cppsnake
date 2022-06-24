#include <curses.h>

#include "curses.h"

#include "snake.h"

Snake::~Snake() {
    Tail* temp;

    while (first) {
        temp = first;
        first = first->next;
        delete temp;
    }
}

void Snake::Add(int x, int y) {
    Tail* temp = new Tail;

    temp->next = 0;
    if (x == -1) {
        last->next = temp;
        last = temp;
    } else {
        temp->x = x;
        temp->y = y;
        first = temp;
        last = temp;
    }
}

bool Snake::SelfCollision() const {
    return false;
}

void Snake::Move() {
    Hide();
    first->x += dx;
    if (first->x < 0)
        first->x = curses.game_win_width-1;
    else if (first->x >= curses.game_win_width)
        first->x = 0;
    first->y += dy;
    if (first->y < 0)
        first->y = curses.game_win_height-1;
    else if (first->y >= curses.game_win_height)
        first->y = 0;
    Show();
}

void Snake::Show() const {
    for (Tail* temp = first; temp; temp = temp->next)
        mvwaddch(curses.game_win, temp->y, temp->x, '#');
}

void Snake::Hide() const {
    for (Tail* temp = first; temp; temp = temp->next)
        mvwaddch(curses.game_win, temp->y, temp->x, ' ');
}
