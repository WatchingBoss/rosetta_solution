CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -ggdb

OUT = go
SRC = 100_doors.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(@F) $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT)
