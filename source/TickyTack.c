#include "TickyTack.h"

static Game_t game;
static TickyTackOptions_t gameOptions;

static Player_t* playerFor(enum Player player) {
    Player_t* constructedPlayer = &NullPlayer;

    switch(player) {
        case HUMAN:
            constructedPlayer = (Player_t*)HumanPlayer_init(NULL, &game);
        break;

        case MINMAX:
        case RANDOM:
            constructedPlayer = malloc(sizeof(Player_t));
            constructedPlayer->currentGame = &game;
            constructedPlayer->handleUpdate = &RandomMove;
        break;

        case INVALID:
            fputs("ERROR: Got INVALID as player in TickyTack_initialize", stderr);
            TickyTack_cleanup();
            exit(2);
        break;
    }

    return constructedPlayer;
}

void TickyTack_initialize(TickyTackOptions_t* options) {
    gameOptions = *options; // Copy the options from the invoker

    // Seed rand for botPlayer
    srand(time(NULL));

    // Set up curses
    Curses_init();
    
    // Try to initialize the game
    if (Game_init(&game) == ERR)
    {
        endwin();
        perror("Unable to start game");
        exit(2);
    }

    // Set NullPlayer's game to this game, just in case
    NullPlayer.currentGame = &game;

    // Pick the players based on the options
    game.xPlayer = playerFor(gameOptions.xPlayer);
    game.oPlayer = playerFor(gameOptions.oPlayer);
}

void TickyTack_gameLoop() {
    while(game.keepPlaying) {
        int ch = getch();

        Game_handleCharacter(&game, ch);
        Game_draw(&game);
    }
}

void TickyTack_cleanup() {
    if (game.xPlayer != &NullPlayer)
        free(game.xPlayer);
        
    if (game.xPlayer != &NullPlayer)    
        free(game.oPlayer);
        
    Game_free(&game);

    endwin();
}

void Curses_init() {
    // Prep the screen
    initscr();
    cbreak();
    // Don't echo anything to the screen
    noecho();
    // Make getch() return immediately
    nodelay(stdscr, TRUE);
    // Turn on keypad support to interpret special stuff
    keypad(stdscr, TRUE);
    // Hide the cursor
    curs_set(0);

    // Ask for mouse position info
    mousemask(REPORT_MOUSE_POSITION | BUTTON1_CLICKED | BUTTON1_PRESSED, NULL);
    //mouseinterval(1000); // Long mouse interval
}

void RandomMove(Player_t* this, int frameInput, MEVENT* mouseEvent) {
    int space;
    int tries = 0;
    do {
        space = rand() % SPACE_COUNT;
        tries++;
    } while(tries < 9 && Board_isSpaceOccupied(this->currentGame->board, space));

    if (tries >= 9)
        Game_log(this->currentGame, "RandomMove failed to find an open spot.");
    else {
        Game_processMove(this->currentGame, space);
    }
}