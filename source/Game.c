#include "Game.h"

static int Game_createWindows(Game_t* game) {
    int playHeight = (2 * LINES) / 3; // Give playField 2/3rds of the screen

    game->playFieldHeight = playHeight;
    game->logFieldHeight = LINES - playHeight;

    game->playField = newwin(playHeight, COLS, 0, 0);
    game->logField = newwin(LINES - playHeight, COLS, playHeight, 0);

    if (game->playField && game->logField)
        return OK;
    else    
        return ERR;
}

static void Game_drawBorders(Game_t* this) {
    box(this->playField, ACS_VLINE, ACS_HLINE);
    box(this->logField, ACS_VLINE, ACS_HLINE);
}

static void Game_drawLog(Game_t* this) {
    char** current = NULL;
    int line = 1;

    // Move off the borders
    wmove(this->logField, line, 1);

    // Print the contents of the log (like, the last whatever lines)
    while((current = (char**)utringbuffer_next(this->log, current))) {
        
        mvwprintw(this->logField, line++, 1, "%s\n", *current);
    }
}

int Game_init(Game_t* this) {
    char* msg = "Hello";

    if (!this)
        return ERR;
    
    if (!(this->board = malloc(sizeof(Board_t))))
        return ERR;

    Board_init(this->board);
    this->board->width = 19;
    this->board->height = 10;

    this->moveCount = 0;
    this->xMove = NULL;
    this->oMove = NULL;
    this->keepPlaying = 1;

    if (Game_createWindows(this) != OK)
        return ERR;

    // Center the board, and then move it 10 spaces to the left
    Board_centerOnWindow(this->board, this->playField);
    this->board->xPosition -= 10;

    // Get space for 6 log items
    utringbuffer_new(this->log, 6, &ut_str_icd);

    utringbuffer_push_back(this->log, &msg);

    return OK;
}

void Game_handleCharacter(Game_t* this, int ch) {
    MEVENT mouseEvent;

    switch(ch) {
        case KEY_MOUSE:
            if (getmouse(&mouseEvent) == OK) {
                Game_handleMouseEvent(this, &mouseEvent);
            }
        break;

        case KEY_UP:
            mvwaddch(this->logField, 2, 2, 'u');
        break;

        case 'q':
            this->keepPlaying = false;
        break;

        case 'f':
            for (int i = 0; i < SPACE_COUNT; i++)
                this->board->spaces[i] = (rand() % 26) + 'A';
        break;
    }
}

void Game_handleMouseEvent(Game_t* this, MEVENT* mouseEvent) {
    if (mouseEvent->bstate & BUTTON1_CLICKED) {
        // If the mouse was clicked on the play window, then 
        if (wenclose(this->playField, mouseEvent->y, mouseEvent->x)) {
            mvwaddch(this->playField, mouseEvent->y, mouseEvent->x, 'c');
        }
    }
}

void Game_log(Game_t* this, const char* message) {
    utringbuffer_push_back(this->log, &message);
}

void Game_draw(Game_t* this) {
    Game_drawLog(this);
    Game_drawBorders(this);
    
    Board_draw(this->board, this->playField);

    wrefresh(this->playField);
    wrefresh(this->logField);
}

void Game_free(Game_t* this) {
    if (this) {
        free(this->board);
    
        this->moveCount = 0;
        this->keepPlaying = 0;

        this->xMove = NULL;
        this->oMove = NULL;
        this->board = NULL;

        utringbuffer_free(this->log);

        delwin(this->playField);
        delwin(this->logField);
    }
}
