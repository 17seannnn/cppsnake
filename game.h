#ifndef GAME_H
#define GAME_H

class Game {
    int score;
public:
    Game() : score(1) {}
    ~Game() {}

    void Start();
private:
    void DisplayBorder() const;
    void DisplayScore() const;
};

#endif
