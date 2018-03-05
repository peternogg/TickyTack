#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <unistd.h>
#include <getopt.h>

#include "TickyTack.h"

#define OPTIONS_STRING "x:o:vh"

static void showHelp();
static enum Player getPlayer(char* input);

int main(int argc, char** argv) {
    // Load options from the command line
    // Set various settings and options
    // Call TickyTack_gameLoop() to start the game
    // Clean up resources
    TickyTackOptions_t options = { 
        .xPlayer = HUMAN, 
        .oPlayer = RANDOM, 
        .verbosity = 0 
    };

    int option;
    enum Player player;

    while((option = getopt(argc, argv, OPTIONS_STRING)) != -1) {
        switch(option) {
            case 'x': // Set the X player
                player = getPlayer(optarg);
                if (player != INVALID) {
                    options.xPlayer = player;
                } else {
                    fprintf(stderr, "Invalid player %s specified for X\n", optarg);
                    showHelp(argv[0]);
                    exit(1);
                }
            break;
            case 'o': // Set the Y player
                player = getPlayer(optarg);
                if (player != INVALID) {
                    options.oPlayer = player;
                } else {
                    fprintf(stderr, "Invalid player %s specified for O\n", optarg);
                    showHelp(argv[0]);
                    exit(1);
                }
            break;
            case 'v': // Increase the verbosity level
                options.verbosity++;
            break;
            case 'h': // Show help, and then exit
                showHelp(argv[0]);
                exit(0);
            break;
        }
    }

    TickyTack_initialize(&options);
    TickyTack_gameLoop();
    TickyTack_cleanup();
}

static void showHelp(char* programName) {

}

static enum Player getPlayer(char* input) {
    static const char* validPlayers[] = { "human", "random", "minmax" };
    static const int vpSize = sizeof(validPlayers) / sizeof(validPlayers[0]);
    enum Player chosenPlayer = INVALID;

    // Search for the string which matches the user's input
    // The array is set up such that the indices match the values in the enum
    for (int i = 0; chosenPlayer == INVALID && i < vpSize; i++) {
        if (strcasecmp(input, validPlayers[i]) == 0)
            chosenPlayer = i;
    }

    return chosenPlayer;
}