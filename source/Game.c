#include "Game.h"

static int Game_createWindows(WINDOW** play, WINDOW** log) {
    int playHeight = (2 * LINES) / 3;
    *play = newwin(playHeight, COLS, 0, 0);
    *log = newwin(LINES - playHeight, COLS, playHeight, 0);

    if (*log && *play)
        return OK;
    else    
        return ERR;
}

int Game_init(Game_t* this) {
    if (this) {
        this->board = malloc(sizeof(Board_t));
        Board_init(this->board);

        this->moveCount = 0;
        this->xMove = NULL;
        this->oMove = NULL;
        this->keepPlaying = 1;

        return Game_createWindows(&this->playField, &this->logField);
    }

    return ERR;
}

void Game_draw(Game_t* this) {
    Board_draw(this->board, this->playField, 4, 4);
}

void Game_free(Game_t* this) {
    if (this) {
        free(this->board);
    
        this->moveCount = 0;
        this->keepPlaying = 0;

        this->xMove = NULL;
        this->oMove = NULL;
        this->board = NULL;

        delwin(this->playField);
        delwin(this->logField);
    }
}
