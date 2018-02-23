#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "TickyTack.h"

int main() {
    // Prep the screen
    initscr();
    cbreak();
    // Don't echo anything to the screen
    noecho();
    // Make getch() return immediately
    nodelay(stdscr, TRUE);
    // Turn on keypad support to interpret special stuff
    keypad(stdscr, TRUE);
    // Hide the cursor
    curs_set(0);

    // Ask for mouse position info
    mousemask(REPORT_MOUSE_POSITION | BUTTON1_CLICKED | BUTTON1_PRESSED, NULL);

    Game_t game;
    MEVENT mouseEvent;

    if (Game_init(&game) == ERR)
    {
        endwin();
        fputs("Unable to start game.", stderr);
        exit(1);
    }

    while(game.keepPlaying) {
        box(game.playField, '|', '-');
        box(game.logField, '|', '-');

        wrefresh(game.playField);
        wrefresh(game.logField);

        int c = getch();

        if (c == KEY_MOUSE) {
            // Whoa! Mouse event!
            if (getmouse(&mouseEvent) == OK) {
                if (mouseEvent.bstate & BUTTON1_CLICKED) {
                    // If the mouse was clicked on the play window, then 
                    if (wenclose(game.playField, mouseEvent.y, mouseEvent.x)) {
                        mvwaddch(game.playField, mouseEvent.y, mouseEvent.x, 'c');
                    }
                }
            }
        }

        if (c == 'q')
            game.keepPlaying = false;

        if (c == 'f') {
            for (int i = 0; i < SPACE_COUNT; i++)
                game.board->spaces[i] = (rand() % 26) + 'A';
        }

        Game_draw(&game);
    }

    Game_free(&game);

    endwin();
}
