TARGET = game

CC = gcc
CFLAGS = -Wall -Wextra
PKG = allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5
SRC = main.c

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(shell pkg-config $(PKG) --libs --cflags) -lm

clean:
	rm -f *.o $(TARGET)
