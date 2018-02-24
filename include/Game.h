#ifndef _GAME_H
#define _GAME_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

#include "Board.h"

#include "utringbuffer.h"

typedef int (*move_select_t)(Board_t*);

typedef struct {
    Board_t* board;
    uint8_t moveCount;
    move_select_t xMove, oMove;
    bool keepPlaying;

    WINDOW* playField;
    WINDOW* logField;

    int playFieldHeight;
    int logFieldHeight;
    
    UT_ringbuffer* log;
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

#endif