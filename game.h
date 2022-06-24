#ifndef GAME_H
#define GAME_H

class Game {
    int score;
public:
    Game() : score(1) {}
    ~Game() {}

    void Start();
private:
    void DisplayScore() const;
    static void DisplayBorder();
    static void DisplayMsg(const char* msg);
};

#endif
