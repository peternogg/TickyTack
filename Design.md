TickyTack will be written around a regular game loop, except the update method will pause until it gets user input via the mouse cursor or keyboard. 

The board is represented as a 9 unit char array, which is redrawn every frame

## Screen Layout
See "ScreenLayout.txt" for an example.

The console is divided into two parts: A play area, and a log area. The play area will take up most of the screen and resides on the upper half. The log uses the remaining amount on the bottom. The screen should be split into thirds, and the play area takes the upper two, while the log takes the bottom one.