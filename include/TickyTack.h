#ifndef TICKYTACK_H
#define TICKYTACK_H

#include <stdint.h>
#include <stdlib.h>

#include <unistd.h>
#include <ncurses.h>

#include "Game.h"
#include "Board.h"
#include "Player.h"

// Initialize ncurses for gameplay
void Curses_init();

// Take input from the keyboard to move the cursor, and then place a piece
void PlayerMove(Player_t* this, int frameInput, MEVENT* mouseEvent);
// Choose a random spot on the board and, if it isn't occupied, place that piece
void RandomMove(Player_t* this, int frameInput, MEVENT* mouseEvent);

#endif