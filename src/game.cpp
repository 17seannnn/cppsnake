#include <string.h>
#include <unistd.h>
#include <curses.h>

#include "curses.h"
#include "snake.h"
#include "apple.h"

#include "game.h"

const char msg_win[] = "You won!";
const char msg_defeat[] = "You lose...";
const char msg_play_again[] = "Play again? [y/n/q]";

bool Game::Start() {
    int ch;
    int max_score = curses.game_win_width * curses.game_win_height;
    int quit = 0;
    Snake snake(curses.game_win_width/2, curses.game_win_height/2);
    Apple apple;

    DisplayBorder();
    DisplayScore();
    do {
        apple.Spawn();
    } while (snake.IsSnake(apple.GetX(), apple.GetY()));

    while (!quit) {
        if (snake.SelfCollision())
            break;
        if (snake.CheckCollision(apple.GetX(), apple.GetY())) {
            snake.Add();
            snake.Move();
            score++;
            DisplayScore();
            if (score == max_score)
                break;
            do {
                apple.Spawn();
            } while (snake.IsSnake(apple.GetX(), apple.GetY()));
        } else {
            snake.Move();
        }
        curses.Refresh();

        ch = wgetch(curses.game_win);
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
    do {
        ch = wgetch(curses.game_win);
    } while (ch != 'Y' && ch != 'y' &&
             ch != 'N' && ch != 'n' &&
             ch != 'Q' && ch != 'q');
    return ch == 'Y' || ch == 'y';
}

void Game::DisplayScore() const {
    char str[80];

    wclear(curses.score_win);
    wattrset(curses.score_win, A_BOLD | COLOR_PAIR(curses.score_pair));

    snprintf(str, 80, "Score: %d", score);
    mvwprintw(curses.score_win, 0, (curses.score_win_width - strlen(str))/2,
              "%s", str);

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

    wattrset(curses.game_win, A_BOLD | A_BLINK | COLOR_PAIR(curses.msg_pair));
    for (int y = msg_y - 3; y <= msg_y + 4; y++) {
        wmove(curses.game_win, y, msg_x - 5);
        for (int x = msg_x - 5; x <= msg_x + len + 4; x++)
            waddch(curses.game_win, ' ');
    }
    mvwprintw(curses.game_win, msg_y, msg_x, "%s", msg);

    msg_x = (curses.game_win_width - strlen(msg_play_again))/2;
    msg_y = curses.game_win_height/2;
    wattrset(curses.game_win, A_BOLD | COLOR_PAIR(curses.msg_pair));
    mvwprintw(curses.game_win, msg_y+2, msg_x, "%s", msg_play_again);
    wattrset(curses.game_win, A_NORMAL);
}
