#ifndef _BOARD_H
#define _BOARD_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

#define SPACE_COUNT 9

typedef struct {
    char spaces[SPACE_COUNT];
    
    int xPosition, yPosition;
    int width, height;

    int cellWidth, cellHeight;

    int cursorX, cursorY;
    int cursorAttributes;
} Board_t;

void Board_init(Board_t* this);
bool Board_isSpaceOccupied(Board_t* this, int space);
void Board_centerOnWindow(Board_t* this, WINDOW* win);
void Board_draw(Board_t* this, WINDOW* win);

void Board_moveCursorRelative(Board_t* this, int dX, int dY);
void Board_setCursorPosition(Board_t* this, int x, int y);

#endif
