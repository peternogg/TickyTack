#ifndef _GAME_H
#define _GAME_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

#include "Board.h"
#include "Player.h"

enum GameState { PLAYING, X_WIN, O_WIN, DRAW, RESETTING };

typedef struct Game_t {
    // The board for the current game
    Board_t* board;
    // The number of moves since the start of the game.
    // The LSB also controls whose turn it is, and what piece is placed
    uint8_t moveCount;
    // Whether or not to keep playing
    bool keepPlaying;

    // The window where the board and UI elements are drawn
    WINDOW* playField;
    // The window where the informational log is drawn
    WINDOW* logField;

    // The player playing for X pieces
    Player_t* xPlayer;
    // The player playing for O pieces
    Player_t* oPlayer;

    // The height (in rows) of the play and log windows
    int playFieldHeight;
    int logFieldHeight;

    enum GameState state;
} Game_t;

// Initialize a Game object
// Default values:
//   board: Set up in full
//   moveCount: 0
//   keepPlaying: 1 (TRUE)
//   playField and logField: Set up in full
//   xPlayer and yPlayer: Set to &NullPlayer
//   playFieldHeight and logFieldHeight: Set to 2/3rds and 1/3rd of the height of the terminal, respectively
//   state: PLAYING
int  Game_init(Game_t* this);
// Clean up after a Game object
// This WILL set x and o players to NULL, so if they're allocated separately,
// make sure they're freed first.
void Game_free(Game_t* this);

// Draw the game to the screen
void Game_draw(Game_t* this);

// Put a message in the game's log window.
void Game_log(Game_t* this, const char* message);

// Handle events for the game
void Game_handleMouseEvent(Game_t* this, MEVENT* event);
void Game_handleCharacter(Game_t* this, int character);

// Place a piece at the Board's current cursor position
// Calls Game_processMove()
void Game_moveAtCursor(Game_t* this);
// Process a move (placing a piece in a space)
// Which piece depends on the value in moveCount
// Even moveCounts place an X, odd ones place an O
void Game_processMove(Game_t* this, int space);
// Reset the state of a game to its first move
// Sets the game's state to RESETTING
void Game_reset(Game_t* this);
// Check if the game has finished - either in a win or a draw
char Game_hasFinished(Game_t* this);

#endif