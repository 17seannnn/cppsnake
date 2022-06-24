#ifndef SNAKE_H
#define SNAKE_H

class Snake {
    struct tail {
        int x, y;
        struct tail* next;
    };

    int dx, dy;
    tail* first;
public:
    Snake() : dx(0), dy(0), first(0) {}
    ~Snake();

    void SetDX(int n_dx) { dx = n_dx; }
    void SetDY(int n_dy) { dy = n_dy; }
    void SetDXY(int n_dx, int n_dy) { dx = n_dx; dy = n_dy; }
    void Move();
private:
    void Show() const;
    void Hide() const;
};

#endif
