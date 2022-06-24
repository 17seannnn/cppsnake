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
    Snake(int first_x, int first_y) : dx(0), dy(0), first(0), last(0)
        { Add(first_x, first_y); }
    ~Snake();

    void Add(int x = -1, int y = -1); // To add tail just snake.Add(), TODO for first self add
    void SetDirection(int n_dx, int n_dy);
    bool SelfCollision() const; // True on self collision
    void Move();
private:
    void Show() const;
    void Hide() const;
};

#endif
