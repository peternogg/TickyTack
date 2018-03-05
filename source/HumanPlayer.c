#include "HumanPlayer.h"

HumanPlayer_t* HumanPlayer_init(HumanPlayer_t* player, Game_t* game) {
    if (player == NULL) 
        player = malloc(sizeof(HumanPlayer_t));
    
    
    player->base.currentGame = game;
    player->base.handleUpdate = &HumanMove;
    player->moves = 0;

    return player;
}

void HumanMove(Player_t* this, int frameInput, MEVENT* mouseEvent) {
    HumanPlayer_t* hum = (HumanPlayer_t*)this;
    char buffer[100];

    // Tell the game to make a move wherever the cursor is now
    if (frameInput == '\n') {
        Game_moveAtCursor(this->currentGame);

        hum->moves++;
        snprintf(buffer, 100, "Human has made %d moves.", hum->moves);
        //Game_log(hum->base.currentGame, buffer);
    } else if (frameInput == KEY_MOUSE) {
        // Mouse input!
        if (mouseEvent->bstate & BUTTON1_CLICKED || mouseEvent->bstate &  BUTTON1_PRESSED)
            Game_moveAtCursor(this->currentGame);
    }
}