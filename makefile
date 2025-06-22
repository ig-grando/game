TARGET = game

CC = gcc
CFLAGS = -Wall -Wextra
PKG = allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5
LIBS = $(shell pkg-config $(PKG) --libs --cflags) -lm

OBJS = main.o menu.o utils.o tiro.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

main.o: main.c menu.h utils.h tiro.h
	$(CC) $(CFLAGS) -c main.c $(LIBS)

menu.o: menu.c menu.h utils.h tiro.h
	$(CC) $(CFLAGS) -c menu.c $(LIBS)

utils.o: utils.c utils.h tiro.h
	$(CC) $(CFLAGS) -c utils.c $(LIBS)

tiro.o: tiro.c tiro.h utils.h
	$(CC) $(CFLAGS) -c tiro.c $(LIBS)

clean:
	rm -f *.o $(TARGET)