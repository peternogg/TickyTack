#ifndef _PLAYER_H
#define _PLAYER_H

#include <stdlib.h>
#include <ncurses.h>

struct Player_t; // Forward declaration

typedef void (*UpdateHandler_t)(struct Player_t* this, int frameInput, MEVENT* mouseInput);

// A structure to hold Player logic and information
typedef struct Player_t {
    // A reference to the game this Player is associated with
    struct Game_t* currentGame;
    // The logic to handle a frame of input, including an optional pressed character and mouse event
    // This is called once for every frame of the game, so it may be called _a lot_
    UpdateHandler_t handleUpdate;
} Player_t;

// The NullPlayer is a player which does nothing but echo its non-ERR input to the log window of its currentGame
extern Player_t NullPlayer;

#endif