#include "Board.h"

void Board_init(Board_t* this) {
    for(int i = 0; i < SPACE_COUNT; i++)
        this->spaces[i] = ' ';
}

void Board_draw(Board_t* this, WINDOW* win, int y, int x) {
    // Try to place the board in the center of the screen
    wmove(win, y, x);
    for (int i = 1; i <= SPACE_COUNT; i++) {
        waddch(win, this->spaces[i - 1]);
        

        if (i % 3 == 0)
            wmove(win, ++y, x);
        else
            waddch(win, '|');
    }

    wrefresh(win);
}

bool Board_isSpaceOccupied(Board_t* this, int space) {
    return (space < SPACE_COUNT && space >= 0
            && this->spaces[space]);
}
