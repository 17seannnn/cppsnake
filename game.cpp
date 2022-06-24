#include <string.h>
#include <unistd.h>
#include <curses.h>

#include "curses.h"
#include "snake.h"
#include "apple.h"

#include "game.h"

const char msg_win[] = "You won!";
const char msg_defeat[] = "You lose...";

void Game::Start() {
    int max_score = curses.game_win_width * curses.game_win_height;
    int quit = 0;
    Snake snake(curses.game_win_width/2, curses.game_win_height/2);
    Apple apple;

    DisplayBorder();
    do {
        apple.Spawn();
    } while (snake.IsSnake(apple.GetX(), apple.GetY()));

    while (!quit) {
        DisplayScore();
        if (snake.SelfCollision())
            break;
        if (snake.CheckCollision(apple.GetX(), apple.GetY())) {
            snake.Add();
            snake.Move();
            if (score == max_score)
                break;
            do {
                apple.Spawn();
            } while (snake.IsSnake(apple.GetX(), apple.GetY()));
            score++;
        } else {
            snake.Move();
        }
        curses.Refresh();

        int ch = wgetch(curses.game_win);
        switch (ch) {
        case KEY_UP:    case 'W': case 'w': case 'K': case 'k':
            snake.SetDirection(0, -1);
            break;
        case KEY_LEFT:  case 'A': case 'a': case 'H': case 'h':
            snake.SetDirection(-1, 0);
            break;
        case KEY_DOWN:  case 'S': case 's': case 'J': case 'j':
            snake.SetDirection(0, 1);
            break;
        case KEY_RIGHT: case 'D': case 'd': case 'L': case 'l':
            snake.SetDirection(1, 0);
            break;
        case 'Q': case 'q':
            quit = 1;
            break;
        default:
            break;
        }

        usleep(50000); // 50 milliseconds
    }

    DisplayMsg(score == max_score ? "You win!" : "You lose...");
    curses.Refresh();
    sleep(3);
}

void Game::DisplayScore() const {
    wclear(curses.score_win);
    wattrset(curses.score_win, A_BOLD);
    mvwprintw(curses.score_win, 0, 0, "Score: %d", score);
    wattrset(curses.score_win, A_NORMAL);
}

void Game::DisplayBorder() {
    wclear(curses.screen_win);
    int ch = ' ' | A_REVERSE;
    for (int y = 0; y < curses.screen_win_height; y++) {
        if (y == 0 || y == curses.screen_win_height-1) {
            wmove(curses.screen_win, y, 0);
            for (int x = 0; x < curses.screen_win_width; x++)
                waddch(curses.screen_win, ch);
        } else {
            mvwaddch(curses.screen_win, y, 0, ch);
            mvwaddch(curses.screen_win, y, curses.screen_win_width-1, ch);
        }
    }
}

void Game::DisplayMsg(const char* msg) {
    int len = strlen(msg);
    int msg_x = (curses.game_win_width - len)/2, msg_y = curses.game_win_height/2;

    for (int y = msg_y - 3; y <= msg_y + 3; y++) {
        wmove(curses.game_win, y, msg_x - 5);
        for (int x = msg_x - 5; x <= msg_x + len + 4; x++)
            waddch(curses.game_win, ' ' | A_REVERSE);
    }
    mvwprintw(curses.game_win, msg_y, msg_x, "%s", msg);
}
