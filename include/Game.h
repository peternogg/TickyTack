#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Board.h"

typedef int (*move_select_t)(Board_t*);

typedef struct {
    Board_t* board;
    uint8_t moveCount;
    move_select_t xMove, oMove;
    bool keepPlaying;
} Game_t;

void Game_init(Game_t* game);

#endif