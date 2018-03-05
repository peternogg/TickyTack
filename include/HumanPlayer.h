#ifndef _HUMANPLAYER_H
#define _HUMANPLAYER_H

#include "Game.h"
#include "Player.h"

typedef struct {
    // The offsets of the members of base match the offsets of those
    // same members in Player_t because of C's struct layout stuff.
    Player_t base;
    int moves;
} HumanPlayer_t;

// Create or initialize a HumanPlayer with a particular game
// If player is NULL, then a new player will be allocated
// Otherwise, the player which is passed in will be used.
HumanPlayer_t* HumanPlayer_init(HumanPlayer_t* player, Game_t* game);
void HumanMove(Player_t* _this, int frameInput, MEVENT* mouseEvent);

#endif