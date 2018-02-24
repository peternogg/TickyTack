TickyTack will be written around a regular game loop, except the update method will pause until it gets user input via the mouse cursor or keyboard. 

The board is represented as a 9 unit char array, which is redrawn every frame

## Screen Layout
See "ScreenLayout.txt" for an example.

The console is divided into two parts: A play area, and a log area. The play area will take up most of the screen and resides on the upper half. The log uses the remaining amount on the bottom. The screen should be split into thirds, and the play area takes the upper two, while the log takes the bottom one.

## Input handling

The game contains a pair of methods - xMove and yMove - which are intended to be called to fetch the next move for a player. It might be more fruitful and general to change those fields to something like a `Player_t*`. Passing whatever input comes to the program and then having that `Player_t*` modify the state of the game or the board or something. 

Adding something like Game_makeMove(Game_t* this, int x, int y) which places the relevant piece (X or Y) onto the board and then advances the game counter. 

The flow of input should be like this:
    Main loop polls input and does what it feels like. Input that isn't used by this loop must be passed to the Game
    The game will handle that input and move a cursor or do something else. If that input isn't handled, then it must be passed to whichever player is current
    The player has final control over the user's input.

I could even do some kinda BSD networking thing and fake out inheritance if I needed to. I probably don't, but I could. _I could_
