#ifndef SNAKE_H
#define SNAKE_H

class Snake {
    struct tail {
        int x, y;
        struct tail* next;
    };

    int dx, dy;
    tail *first, *last;
public:
    Snake(int first_x, int first_y) : dx(0), dy(0), first(0), last(0)
        { Add(first_x, first_y); }
    ~Snake();

    void Add(int x = -1, int y = -1); // To add tail just snake.Add()
    void SetDirection(int n_dx, int n_dy) { dx = n_dx; dy = n_dy; }
    bool SelfCollision(); // True on self collision
    void Move();
private:
    void Show() const;
    void Hide() const;
};

#endif
