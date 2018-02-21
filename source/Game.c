#include "Game.h"

int noMove(Board_t* board) {
    return 0;
}

void Game_init(Game_t* this) {
    this->board = malloc(sizeof(Board_t));
    Board_init(this->board);

    this->moveCount = 0;
    this->xMove = noMove;
    this->oMove = noMove;
    this->keepPlaying = 1;
}

void Game_draw(Game_t* this) {

}