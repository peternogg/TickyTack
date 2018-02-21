#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "TickyTack.h"

void DrawBoard(Board_t*);

int main() {
    // Prep the screen
    initscr();
    // Poll inputs every 1/10th of a second
    cbreak();
    // Don't echo anything to the screen
    noecho();
    keypad(stdscr, true);

    // Ask for mouse position info
    mousemask(REPORT_MOUSE_POSITION | BUTTON1_CLICKED | BUTTON1_PRESSED, NULL);

    Game_t game;
    MEVENT mouseEvent;

    Game_init(&game);

    while(game.keepPlaying) {
        int c = getch();

        if (c == KEY_MOUSE) {
            // Whoa! Mouse event!
            if (getmouse(&mouseEvent) == OK) {
                if (mouseEvent.bstate & REPORT_MOUSE_POSITION)
                    move(mouseEvent.y, mouseEvent.x);
                
                if (mouseEvent.bstate & BUTTON1_CLICKED || mouseEvent.bstate & BUTTON1_PRESSED)
                    addch('c');
            }
        }

        if (c == 'q')
            game.keepPlaying = false;

        refresh();
    }

    endwin();
}
