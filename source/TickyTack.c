#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "TickyTack.h"

void DrawBoard(Board_t*);

int main() {
    // Prep the screen
    initscr();
    // Poll inputs every 1/10th of a second
    halfdelay(1);
    // Don't echo anything to the screen
    noecho();

    Game_t game;

    Game_init(&game);

    while(game.keepPlaying) {
        char c = getch();

        if (c != ERR)
            mvprintw(0, 0, "You typed %c\n", c);
        else
            mvprintw(0, 0, "Ah, no input?");

        if (c == 'q')
            game.keepPlaying = false;

        refresh();
    }

    endwin();
}

void DrawBoard(Board_t* board) {
    mvprintw(0, 0, "%c | %c | %c\n", board->spaces[0], board->spaces[1], board->spaces[2]);
    printw("%c | %c | %c\n", board->spaces[3], board->spaces[4], board->spaces[5]);
    printw("%c | %c | %c\n", board->spaces[6], board->spaces[7], board->spaces[8]);
}