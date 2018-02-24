#include "Board.h"

void Board_init(Board_t* this) {
    for(int i = 0; i < SPACE_COUNT; i++)
        this->spaces[i] = ' ';

    this->width = 5;
    this->height = 5;
}

void Board_draw(Board_t* this, WINDOW* win) {
    // Initial position of top left corner
    int x = this->xPosition;
    int y = this->yPosition - 1;

    // The size of a step to take between placing a character
    int xStride = this->width / 3 + 1;
    int yStride = this->height / 3 + 1;

    for (int placeY = 0; placeY < 3; placeY++) {
        for (int placeX = 0; placeX < 3; placeX++) {
            // Draw a box at (placeX, placeY) which fills the
            // square it sits in
            for (int i = 0; i < yStride - 1; i++)
                for (int j = 0; j < xStride - 1; j++) {
                    wmove(win, y + (placeY * yStride) + i, x + (placeX * xStride) + j);
                    waddch(win, this->spaces[placeX + 3 * placeY]);
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

    wrefresh(win);
}

void Board_centerOnWindow(Board_t* this, WINDOW* win) {
    int winWidth, winHeight;
    // Get the window's size
    getmaxyx(win, winHeight, winWidth);

    this->xPosition = (winWidth / 2) - (this->width / 2);
    this->yPosition = (winHeight / 2) - (this->height / 2);
}

bool Board_isSpaceOccupied(Board_t* this, int space) {
    return (space < SPACE_COUNT && space >= 0
            && this->spaces[space]);
}
