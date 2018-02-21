#include "Board.h"

void Board_init(Board_t* this) {
    for(int i = 0; i < SPACE_COUNT; i++)
        this->spaces[i] = ' ';
}

void Board_draw(Board_t* this) {
    // Try to place the board in the center of the screen
    
}

bool Board_isSpaceOccupied(Board_t* this, int space) {
    return (space < SPACE_COUNT && space >= 0
            && this->spaces[space]);
}
