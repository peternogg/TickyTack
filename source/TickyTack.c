#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "TickyTack.h"

int main() {
    Game_t game;
    Player_t humanPlayer = { &game, &PlayerMove },
             botPlayer   = { &game, &RandomMove };

    char buffer[512];
    int counter = 1000;

    Curses_init();
    
    if (Game_init(&game) == ERR)
    {
        endwin();
        perror("Unable to start game");
        exit(1);
    }

    game.xPlayer = &humanPlayer;
    game.oPlayer = &botPlayer;

    while(game.keepPlaying) {
        int ch = getch();

        if (ch == 'd') {
            snprintf(buffer, 512, "Hello! Message #%d", counter++);
            Game_log(&game, buffer);
        } else if (ch == 'r') {
            // Reset the board to spaces
            for (int i = 0; i < SPACE_COUNT; i++)
                game.board->spaces[i] = ' ';

            Game_log(&game, "Reset board!");
        }

        Game_handleCharacter(&game, ch);
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

void PlayerMove(Player_t* this, int frameInput, MEVENT* mouseEvent) {
    // Tell the game to make a move wherever the cursor is now
    if (frameInput == '\n') {
        Game_moveAtCursor(this->currentGame);
    } else if (frameInput == KEY_MOUSE) {
        // Mouse input!
        if (mouseEvent->bstate & BUTTON1_CLICKED)
            Game_moveAtCursor(this->currentGame);
    }
}

void RandomMove(Player_t* this, int frameInput, MEVENT* mouseEvent) {
    int space;
    int tries = 0;
    do {
        space = rand() % SPACE_COUNT;
        tries++;
    } while(tries < 9 && Board_isSpaceOccupied(this->currentGame->board, space));

    if (tries >= 9)
        Game_log(this->currentGame, "RandomMove failed to find an open spot.");
    else {
        Game_processMove(this->currentGame, space);
    }
}