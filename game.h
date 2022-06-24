#ifndef GAME_H
#define GAME_H

#include "snake.h"

class Game {
    Snake snake;
public:
    Game() {}
    ~Game() {}

    void Start();
};

#endif
