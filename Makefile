CC := clang
WARNINGS := -Wall
CFLAGS = -g -I$(INCLUDE)

SRC = source/
BUILD := build/
INCLUDE := include/

all: TickyTack

TickyTack: TickyTack.o Game.o Board.o Player.o
	$(CC) $(WARNINGS) $(CFLAGS) $(BUILD)*.o -o $(BUILD)TickyTack -lncurses

TickyTack.o: $(SRC)TickyTack.c
	$(CC) $(WARNINGS) $(CFLAGS) -c $(SRC)TickyTack.c -o $(BUILD)TickyTack.o

Game.o: $(SRC)Game.c
	$(CC) $(WARNINGS) $(CFLAGS) -c $(SRC)Game.c -o $(BUILD)Game.o

Board.o: $(SRC)Board.c
	$(CC) $(WARNINGS) $(CFLAGS) -c $(SRC)Board.c -o $(BUILD)Board.o

Player.o: $(SRC)Player.c
	$(CC) $(WARNINGS) $(CFLAGS) -c $(SRC)Player.c -o $(BUILD)Player.o

clean:
	rm -f $(BUILD)*