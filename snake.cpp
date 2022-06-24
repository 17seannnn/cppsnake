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

void Snake::SetDirection(int n_dx, int n_dy) {
    if ((n_dx != -dx && n_dy != -dy) || (dx == 0 && dy == 0)) {
        dx = n_dx;
        dy = n_dy;
    }
}

bool Snake::SelfCollision() const {
    int coll_x = first->x + dx, coll_y = first->y + dy;
    check_coords(coll_x, coll_y);

    for (Tail* temp = first->next; temp; temp = temp->next)
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

    int last_x = first->x, last_y = first->y;
    first->x += dx;
    first->y += dy;
    check_coords(first->x, first->y);

    int save_last_x, save_last_y;
    for (Tail* temp = first->next; temp; temp = temp->next) {
        save_last_x = temp->x;
        save_last_y = temp->y;
        temp->x = last_x;
        temp->y = last_y;
        last_x = save_last_x;
        last_y = save_last_y;
    }

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

bool Snake::IsSnake(int x, int y) const {
    for (Tail* temp = first; temp; temp = temp->next)
        if (temp->x == x && temp->y == y)
            return true;
    return false;
}
