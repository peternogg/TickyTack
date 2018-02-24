#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "TickyTack.h"

int main() {
    Game_t game;

    Curses_init();
    
    if (Game_init(&game) == ERR)
    {
        endwin();
        perror("Unable to start game");
        exit(1);
    }

    while(game.keepPlaying) {
        Game_handleCharacter(&game, getch());
        Game_draw(&game);
    }

    Game_free(&game);

    endwin();
}

void Curses_init() {
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
}
