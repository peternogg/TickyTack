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

    // Set up the windows
    WINDOW* play;
    WINDOW* log;

    if (CreateWindows(&play, &log) == ERR)
    {
        endwin();
        fputs("Failed to create windows", stderr);
        exit(1);
    }

    Game_t game;
    MEVENT mouseEvent;

    Game_init(&game);

    while(game.keepPlaying) {
        box(play, '|', '-');
        box(log, '|', '-');

        wrefresh(play);
        wrefresh(log);

        int c = getch();

        if (c == KEY_MOUSE) {
            // Whoa! Mouse event!
            if (getmouse(&mouseEvent) == OK) {
                if (mouseEvent.bstate & BUTTON1_CLICKED) {
                    // If the mouse was clicked on the play window, then 
                    if (wenclose(play, mouseEvent.y, mouseEvent.x)) {
                        mvwaddch(play, mouseEvent.y, mouseEvent.x, 'c');
                    }
                }
            }
        }

        if (c == 'q')
            game.keepPlaying = false;

        if (c == 'd')
            DrawBoard(game.board, play, 4, 4);

        if (c == 'f') {
            for (int i = 0; i < SPACE_COUNT; i++)
                game.board->spaces[i] = (rand() % 26) + 'A';

            DrawBoard(game.board, play, 4, 4);
        }
    }

    delwin(play);
    delwin(log);
    endwin();
}

int CreateWindows(WINDOW** play, WINDOW** log) {
    int playHeight = (2 * LINES) / 3;
    *play = newwin(playHeight, COLS, 0, 0);
    *log = newwin(LINES - playHeight, COLS, playHeight, 0);

    if (*log && *play)
        return OK;
    else    
        return ERR;
}

void DrawBoard(Board_t* board, WINDOW* win, int x, int y) {
    wmove(win, y, x);
    for (int i = 1; i <= SPACE_COUNT; i++) {
        waddch(win, board->spaces[i - 1]);
        

        if (i % 3 == 0)
            wmove(win, ++y, x);
        else
            waddch(win, '|');
    }

    wrefresh(win);
}