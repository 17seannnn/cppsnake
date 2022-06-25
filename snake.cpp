#include <curses.h>

#include "curses.h"

#include "snake.h"

static void check_coords(int& x, int& y) {
    if (x < 0)
        x = curses.game_win_width-1;
    else if (x >= curses.game_win_width)
        x = 0;

    if (y < 0)
        y = curses.game_win_height-1;
    else if (y >= curses.game_win_height)
        y = 0;
}

Snake::Snake(int first_x, int first_y) : ch(' ' | COLOR_PAIR(curses.snake_pair)), dx(0), dy(0) {
    first = new Tail;
    first->x = first->x;
    first->y = first->y;
    last = first;
}

Snake::~Snake() {
    Tail* temp;
    while (last) {
        temp = last;
        last = last->next;
        delete temp;
    }
}

void Snake::Add() {
    Tail* temp = new Tail;
    temp->next = last;
    last = temp;
}

void Snake::SetDirection(int n_dx, int n_dy) {
    if ((n_dx != -dx && n_dy != -dy) || (dx == 0 && dy == 0)) {
        dx = n_dx;
        dy = n_dy;
    }
}

bool Snake::SelfCollision() const {
    int coll_x = first->x + dx, coll_y = first->y + dy;
    check_coords(coll_x, coll_y);

    for (Tail* temp = last; temp != first; temp = temp->next)
        if (temp->x == coll_x && temp->y == coll_y)
            return true;
    return false;
}

bool Snake::CheckCollision(int x, int y) const {
    int coll_x = first->x + dx, coll_y = first->y + dy;
    check_coords(coll_x, coll_y);
    return x == coll_x && y == coll_y;
}

void Snake::Move() {
    Hide();

    for (Tail* temp = last; temp->next; temp = temp->next) {
        temp->x = temp->next->x;
        temp->y = temp->next->y;
    }

    first->x += dx;
    first->y += dy;
    check_coords(first->x, first->y);

    Show();
}

bool Snake::IsSnake(int x, int y) const {
    for (Tail* temp = last; temp; temp = temp->next)
        if (temp->x == x && temp->y == y)
            return true;
    return false;
}
