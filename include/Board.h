#ifndef _BOARD_H
#define _BOARD_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

#define SPACE_COUNT 9

typedef struct {
    char spaces[SPACE_COUNT];
    
} Board_t;

void Board_init(Board_t* this);
bool Board_isSpaceOccupied(Board_t* this, int space);
void Board_draw(Board_t* this, WINDOW* win, int yPosition, int xPosition);

#endif
