CC := clang
WARNINGS := -Wall -Wextra
CFLAGS = -g -I$(INCLUDE)

SRC = source/
BUILD := build/
INCLUDE := include/

all: TickyTack

TickyTack: TickyTack.o Game.o Board.o
	$(CC) $(WARNINGS) $(CFLAGS) $(BUILD)*.o -o $(BUILD)TickyTack -lncurses

TickyTack.o: $(SRC)TickyTack.c
	$(CC) $(WARNINGS) $(CFLAGS) -c $(SRC)TickyTack.c -o $(BUILD)TickyTack.o

Game.o: $(SRC)Game.c
	$(CC) $(WARNINGS) $(CFLAGS) -c $(SRC)Game.c -o $(BUILD)Game.o

Board.o: $(SRC)Board.c
	$(CC) $(WARNINGS) $(CFLAGS) -c $(SRC)Board.c -o $(BUILD)Board.o

clean:
	rm -f $(BUILD)*