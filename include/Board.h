#ifndef _BOARD_H
#define _BOARD_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

#define SPACE_COUNT 9

typedef struct {
    // The board space data arranged linearly
    // The information in a cell is at spaces[x + y * 3]
    char spaces[SPACE_COUNT];
    
    // Drawing information for the board
    // The X and Y position (in character cells) of the
    // top left corner of the board
    int xPosition, yPosition;
    // The width and height of the board to draw on screen
    int width, height;

    // The width and height (in character cells) of each board cell
    int cellWidth, cellHeight;

    // The location on the board where the cursor is
    int cursorX, cursorY;
    // The attributes to activate when drawing the cursor
    int cursorAttributes;
} Board_t;

// Initialize a board object
void Board_init(Board_t* this);
// Check if a particular space is occupied - i.e. whether it has a space character or not
bool Board_isSpaceOccupied(Board_t* this, int space);
// Center a board on a particular window
void Board_centerOnWindow(Board_t* this, WINDOW* win);
// Draw a board to a window
void Board_draw(Board_t* this, WINDOW* win);

// Move the board's selected cell cursor relative to its current position
// If the resulting position is not on the board, the cursor does not move
void Board_moveCursorRelative(Board_t* this, int dX, int dY);
// Move the board's selected cell cursor to a location on the board
// If the location (x, y) is not on the board (i.e. x and y are not in [0, 2]) then
// the cursor doesn't move
void Board_setCursorPosition(Board_t* this, int x, int y);
// Check if all the spaces in the board are occupied
bool Board_isFull(Board_t* this);
// Reset the board state to its initial one - all spaces open, and
// the cursor is in the center
void Board_reset(Board_t* this);

#endif
