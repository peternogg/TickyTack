# Directories
INCLUDE = include
SOURCE  = source
BUILD   = build

# Build flags
CC := clang
WARNINGS := -Wall
CFLAGS := -g -I$(INCLUDE) --std=c11
LDFLAGS = -lncurses

# What to build
SRC = $(wildcard $(SOURCE)/*.c) # Every .c file in source/
OBJ = $(foreach object, $(SRC), $(BUILD)/$(notdir $(object:.c=.o))) # Swap "source/" for "build/" and .c for .o
#OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

TickyTack: $(OBJ)
	$(CC) $^ -o $(BUILD)/$@ $(LDFLAGS)

$(BUILD)/%.o: $(SOURCE)/%.c
	$(CC) $(WARNINGS) $(CFLAGS) -c $< -o $@

-include $(DEP)
$(BUILD)/%.d: $(SOURCE)/%.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$(BUILD)/$(notdir $@)

.PHONY: clean
clean:
	rm -f $(BUILD)/*