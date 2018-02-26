#ifndef TICKYTACK_H
#define TICKYTACK_H

#include <stdint.h>

#include "Game.h"
#include "Board.h"
#include "Player.h"

void Curses_init();

void PlayerMove(Player_t* this, int frameInput, MEVENT* mouseEvent);
void RandomMove(Player_t* this, int frameInput, MEVENT* mouseEvent);

#endif