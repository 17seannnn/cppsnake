#ifndef SNAKE_H
#define SNAKE_H

class Snake {
    struct Tail {
        int x, y;
        struct Tail* next;
    };

    int dx, dy;
    Tail *first, *last;
public:
    Snake(int first_x, int first_y);
    ~Snake();

    void Add();
    void SetDirection(int n_dx, int n_dy);
    bool SelfCollision() const; // True on self collision
    bool CheckCollision(int x, int y) const;
    void Move();
    bool IsSnake(int x, int y) const;
private:
    void Show() const;
    void Hide() const;
};

inline void Snake::Show() const {
    mvwaddch(curses.game_win, first->y, first->x, ' ' | COLOR_PAIR(curses.snake_pair));
}

inline void Snake::Hide() const {
    mvwaddch(curses.game_win, last->y, last->x, ' ');
}

#endif
