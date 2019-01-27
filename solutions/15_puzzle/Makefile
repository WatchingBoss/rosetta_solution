CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -ggdb

SDL_INCLUDE = -I../req/SDL2/include
SDL_LINK = -L../req/SDL2/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

CCFLAGS = $(CFLAGS) $(SDL_INCLUDE)
LFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LINK)

OUT = go
SRC = 15_puzzle.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $(@F) $<

$(OUT): $(OBJ)
	$(CC) $(CCFLAGS) -o $(OUT) $(OBJ) $(LFLAGS)

clean:
	$(RM) $(OBJ) $(OUT)
