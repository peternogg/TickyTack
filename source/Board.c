#include "Board.h"

void Board_init(Board_t* this) {
    for(int i = 0; i < SPACE_COUNT; i++)
        this->spaces[i] = ' ';

    // Default to 5x5 characters
    this->width = 5;
    this->height = 5;

    this->cellWidth = this->width / 3;
    this->cellHeight = this->height / 3;

    this->cursorX = 1;
    this->cursorY = 1;

    this->cursorAttributes = A_REVERSE | A_BLINK;
}

void Board_draw(Board_t* this, WINDOW* win) {
    // Initial position of top left corner
    int x = this->xPosition;
    int y = this->yPosition - 1;

    // The size of a step to take between placing a character
    int xStride = this->cellWidth + 1;
    int yStride = this->cellHeight + 1;

    int cur_attr = 0;

    for (int placeY = 0; placeY < 3; placeY++) {
        for (int placeX = 0; placeX < 3; placeX++) {
            // Turn on reverse video if we're drawing the cell the cursor is on
            if (this->cursorX == placeX && this->cursorY == placeY)
                cur_attr = this->cursorAttributes; 
            else   
                cur_attr = 0;

            // Draw a box at (placeX, placeY) which fills the
            // square it sits in
            for (int i = 0; i < yStride - 1; i++)
                for (int j = 0; j < xStride - 1; j++) {
                    wmove(win, y + (placeY * yStride) + i, x + (placeX * xStride) + j);
                    waddch(win, this->spaces[placeX + 3 * placeY] | cur_attr);
                }
        }
    }

    // Draw the grid
    // Put two vertical and horizontal lines, and then put crosses at the crossings
    wmove(win, y + yStride - 1, x - 1);
    whline(win, ACS_HLINE, this->width + 3);
    wmove(win, y + 2 * yStride - 1, x - 1);
    whline(win, ACS_HLINE, this->width + 3);

    wmove(win, y, x + xStride - 1);
    wvline(win, ACS_VLINE, this->height + 1);
    wmove(win, y, x + 2 * xStride - 1);
    wvline(win, ACS_VLINE, this->height + 1);

    // The crosses are at (1, 1), (2, 1), (1, 2), and (2, 2)
    wmove(win, y + yStride - 1, x + xStride - 1);
    waddch(win, ACS_PLUS);
    wmove(win, y + 2 * yStride - 1, x + xStride - 1);
    waddch(win, ACS_PLUS);
    wmove(win, y + 2 * yStride - 1, x + 2 * xStride - 1);
    waddch(win, ACS_PLUS);
    wmove(win, y + yStride - 1, x + 2 * xStride - 1);
    waddch(win, ACS_PLUS);
}

void Board_centerOnWindow(Board_t* this, WINDOW* win) {
    int winWidth, winHeight;
    // Get the window's size
    getmaxyx(win, winHeight, winWidth);

    this->xPosition = (winWidth / 2) - (this->width / 2);
    this->yPosition = (winHeight / 2) - (this->height / 2);

    this->cellWidth = this->width / 3;
    this->cellHeight = this->height / 3;
}

bool Board_isSpaceOccupied(Board_t* this, int space) {
    return (space < SPACE_COUNT && space >= 0
            && this->spaces[space]);
}

void Board_moveCursorRelative(Board_t* this, int dX, int dY) {
    Board_setCursorPosition(this, this->cursorX + dX, this->cursorY + dY);
}

void Board_setCursorPosition(Board_t* this, int x, int y) {
    if (x >= 0 && x <= 2)
        if (y >= 0 && y <= 2) {
            this->cursorX = x;
            this->cursorY = y;
        }
}