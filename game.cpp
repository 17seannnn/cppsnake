#include <unistd.h>
#include <curses.h>

#include "curses.h"
#include "snake.h"

#include "game.h"

void Game::Start() {
    int quit = 0;
    Snake snake(curses.game_win_width/2, curses.game_win_height/2);
    //Apple apple();

    DisplayBorder();
    while (!quit) {
        DisplayScore();
        if (snake.SelfCollision())
            break;
        // if collision with apple
            // snake.Add();
        snake.Move();
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
}

void Game::DisplayScore() const {
    wclear(curses.score_win);
    wattrset(curses.score_win, A_BOLD);
    mvwprintw(curses.score_win, 0, 0, "Score: %d", score);
    wattrset(curses.score_win, A_NORMAL);
}

void Game::DisplayBorder() const {
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
