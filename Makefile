CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lm -lcjson

# Définir les dossiers source
SRCDIR = . lib
SRC = $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.c))
OBJ = $(SRC:.c=.o)
EXEC = Blitzerilla

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean