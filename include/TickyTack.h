#ifndef TICKYTACK_H
#define TICKYTACK_H

#include <stdint.h>

#include "Game.h"
#include "Board.h"

void Update();
void DrawBoard(Board_t*);

int CreateWindows(WINDOW** play, WINDOW** log);

int PlayerMove(Board_t* board);
int RandomMove(Board_t* board);

#endif