# TickyTack design information

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

## Object Design

It's worth looking into, in order to generalize the game a bit, having an GameObject struct which has some sort of handleInput() method. GameObject could have a subclass DrawableGameObject which adds a draw(WINDOW*) method. The Game and Board would be a DrawableGameObject, while the Players would just be GameObjects.

The Player(s) in Game could then be placed in a GameObject array. The Game would keep track of whose turn it was, and the players would know what piece they were placing. The player calls the game's processMove method to actually put its piece down and advance the play counter

The board could still be a regular field, since there should only be the one board per game. It, in turn, would hold an array of Cells, which are Drawable, and a final Grid DrawableGameObject. The cells would know their X/Y positions and their index into the board.

This could allow the game to be generalized to take N players with M pieces, playing on an X by Y board. If the drawing algorithm is generalize-able (mostly such that the cells are always at least as big as 1 character cell) then this ought to work.

Doing this in C might lead to some extra work in manually handling objects and inheritance, but that's not terrible.

## Sequence of events

TickyTack is built around a game loop which fetches pending input and forwards it on to the game and any relevant, listening game objects.

The game is allowed a chance to respond to input, which it may 'handle' and then pass on to its subobjects.

### Main loop

1) Main initializes ncurses, the game object, and the two players.
1) While the game says to keep playing:
    1) The game fetches input from ncurses
    1) [DEBUG] if the input is 'd' or 'r', do something
    1) Forward the input on to the game
    1) Tell the game to redraw itself
    1) Repeat until the game ends
1) Free the game
1) Clean up ncurses

### Game (handling input)

When the game recieves input (via a call to Game_handleCharacter), then the game gets a chance to do general game-level things
1) If the game got mouse input, then handle the mouse input
1) If an arrow key was pressed, then move the board cursor in that direction
1) If the 'q' key was pressed, then quit
1) [DEBUG] If the 'f' key was pressed, fill the board with random characters
1) Forward the input on to whichever player is currently up

Mouse input:
1) [DEBUG] If the mouse was clicked, then put a 'c' at the current mouse location
1) [DEBUG] If the mouse moved, then print the new position in the log
