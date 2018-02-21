#ifndef TICKYTACK_H
#define TICKYTACK_H

#include <stdint.h>

#include "Game.h"
#include "Board.h"

void Update();
void Draw(Board_t* board);

int PlayerMove(Board_t* board);
int RandomMove(Board_t* board);

#endif