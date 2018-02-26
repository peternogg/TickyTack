#ifndef _GAME_H
#define _GAME_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

#include "Board.h"
#include "Player.h"

typedef struct Game_t {
    Board_t* board;
    uint8_t moveCount;
    bool keepPlaying;

    WINDOW* playField;
    WINDOW* logField;

    Player_t* xPlayer;
    Player_t* oPlayer;

    int playFieldHeight;
    int logFieldHeight;
} Game_t;

int  Game_init(Game_t* this);
void Game_free(Game_t* this);

// Draw the game to the screen
void Game_draw(Game_t* this);

// Put a message in the game's log window.
void Game_log(Game_t* this, const char* message);

// Handle events for the game
void Game_handleMouseEvent(Game_t* this, MEVENT* event);
void Game_handleCharacter(Game_t* this, int character);

void Game_moveAtCursor(Game_t* this);
void Game_processMove(Game_t* this, int space);

#endif