#ifndef _PLAYER_H
#define _PLAYER_H

#include <stdlib.h>
#include <ncurses.h>

struct Player_t;

typedef void (*UpdateHandler_t)(struct Player_t* this, int frameInput, MEVENT* mouseInput);

typedef struct Player_t {
    struct Game_t* currentGame;
    UpdateHandler_t handleUpdate;
} Player_t;

extern Player_t NullPlayer;

#endif