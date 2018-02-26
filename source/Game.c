#include "Game.h"

static int Game_createWindows(Game_t* game) {
    int playHeight = (2 * LINES) / 3; // Give playField 2/3rds of the screen

    game->playFieldHeight = playHeight;
    game->logFieldHeight = LINES - playHeight;

    game->playField = newwin(playHeight, COLS, 0, 0);
    game->logField = newwin(LINES - playHeight, COLS, playHeight, 0);

    if (game->playField && game->logField) {
        // Set up scrolling for logField
        // Scrolling area is the area around the border
        wsetscrreg(game->logField, 1, game->logFieldHeight - 1);
        scrollok(game->logField, TRUE);

        // Put the cursor for logField on the second line to start
        wmove(game->logField, 1, 1);
        return OK;
    }
    else    
        return ERR;
}

static void Game_drawBorders(Game_t* this) {
    box(this->playField, ACS_VLINE, ACS_HLINE);
    box(this->logField, ACS_VLINE, ACS_HLINE);
}

int Game_init(Game_t* this) {
    if (!this)
        return ERR;
    
    if ((this->board = malloc(sizeof(Board_t))) == NULL)
        return ERR;

    Board_init(this->board);
    this->board->width = 19;
    this->board->height = 10;

    NullPlayer.currentGame = this;

    this->moveCount = 0;
    this->xPlayer = &NullPlayer;
    this->oPlayer = &NullPlayer;
    this->keepPlaying = 1;

    if (Game_createWindows(this) != OK)
        return ERR;

    // Center the board, and then move it 10 spaces to the left
    Board_centerOnWindow(this->board, this->playField);
    this->board->xPosition -= 10;

    return OK;
}

void Game_handleCharacter(Game_t* this, int ch) {
    MEVENT mouseEvent;
    bool handled = false;
    Player_t* currentPlayer = this->moveCount & 1 ? this->oPlayer : this->xPlayer;

    switch(ch) {
        case KEY_MOUSE:
            if (getmouse(&mouseEvent) == OK) {
                Game_handleMouseEvent(this, &mouseEvent);
            }
        break;

        case KEY_UP:
            Board_moveCursorRelative(this->board, 0, -1);
        break;

        case KEY_DOWN:
            Board_moveCursorRelative(this->board, 0, 1);
        break;

        case KEY_LEFT:
            Board_moveCursorRelative(this->board, -1, 0);
        break;

        case KEY_RIGHT:
            Board_moveCursorRelative(this->board, 1, 0);
        break;

        case 'Q':
        case 'q':
            handled = true;
            this->keepPlaying = false;
        break;

        case 'F':
        case 'f':
            handled = true;
            for (int i = 0; i < SPACE_COUNT; i++)
                this->board->spaces[i] = (rand() % 26) + 'A';
        break;
    }

    // Pass the input on to whoever is playing now
    // If the input was handled, then pass ERR
    currentPlayer->handleUpdate(currentPlayer, handled ? ERR : ch, ch == KEY_MOUSE ? &mouseEvent : NULL);
}

void Game_handleMouseEvent(Game_t* this, MEVENT* mouseEvent) {
    #define BUF_SZ 100
    char buffer[BUF_SZ];

    if (mouseEvent->bstate & BUTTON1_CLICKED) {
        if (wenclose(this->playField, mouseEvent->y, mouseEvent->x)) {
            mvwaddch(this->playField, mouseEvent->y, mouseEvent->x, 'c');
        }
    }
    
    if (mouseEvent->bstate & REPORT_MOUSE_POSITION) {
        snprintf(buffer, BUF_SZ, "Mouse moved to (%d, %d)", mouseEvent->x, mouseEvent->y);
        Game_log(this, buffer);
    }

    #undef BUF_SZ
}

void Game_log(Game_t* this, const char* message) {
    int x, y;
    getyx(this->logField, y, x);

    // Print 1 character into the field to avoid the border
    mvwprintw(this->logField, y, 1, "%s\n", message);
}

void Game_draw(Game_t* this) {
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

        this->xPlayer = NULL;
        this->oPlayer = NULL;
        this->board = NULL;

        delwin(this->playField);
        delwin(this->logField);
    }
}

void Game_moveAtCursor(Game_t* this) {
    Board_t* board = this->board;
    int selectedSpace = board->cursorX + (board->cursorY * 3);

    Game_processMove(this, selectedSpace);
}

void Game_processMove(Game_t* this, int space) {
    char ch = (this->moveCount & 1 ? 'O' : 'X');
    char buffer[100];

    if (Board_isSpaceOccupied(this->board, space)) {
        Game_log(this, "Sorry! You can't put a piece there.");
    } else {
        this->board->spaces[space] = ch;
        snprintf(buffer, 100, "Move %d: Player %d placed %c at %d", 
            this->moveCount,
            this->moveCount & 1 ? 2 : 1,
            ch,
            space);

        this->moveCount++;
        Game_log(this, buffer);
    }
}
