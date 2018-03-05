#ifndef TICKYTACK_H
#define TICKYTACK_H

#include <stdint.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>

#include <ncurses.h>

#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"

enum Player { INVALID = -1, HUMAN = 0, RANDOM = 1, MINMAX = 2 };

typedef struct {
    enum Player xPlayer;
    enum Player oPlayer;

    int verbosity;
} TickyTackOptions_t;

// Initialize the game and environment
void TickyTack_initialize(TickyTackOptions_t* options);
// Initialize ncurses for gameplay
void Curses_init();
// The main driving loop for the game
void TickyTack_gameLoop();
// Cleanup for the game
// Call this after the game loop returns
void TickyTack_cleanup();
// Take input from the keyboard to move the cursor, and then place a piece
void PlayerMove(Player_t* this, int frameInput, MEVENT* mouseEvent);
// Choose a random spot on the board and, if it isn't occupied, place that piece
void RandomMove(Player_t* this, int frameInput, MEVENT* mouseEvent);

#endif