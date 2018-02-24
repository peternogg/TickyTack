#include "Player.h"
#include "Game.h"

static void DoNothing(Player_t* player, int input) {
    #define BUF_SZ 100
    char buffer[BUF_SZ];

    if (player && player->currentGame) {
        if (input != ERR) {
            snprintf(buffer, BUF_SZ, "Pressed '%c'", input);
            Game_log(player->currentGame, buffer);
        }
    }
}

Player_t NullPlayer = { NULL, &DoNothing };
