#ifndef GAME_H
#define GAME_H

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
    
    UT_ringbuffer* log;
} Game_t;

int  Game_init(Game_t* this);
void Game_free(Game_t* this);

void Game_draw(Game_t* this);

#endif