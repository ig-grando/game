#ifndef UTILS_H
#define UTILS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

struct coordenada{
    int x;
    int y;
};

struct boneco{
    int x;
    int y;
    //int velocidade_x;
    int velocidade_y;
    int direcao;
    int lado;
    bool abaixado;
    bool chao;
    bool atirando;
};

struct tela{
    int X_SCREEN;
    int Y_SCREEN;
};

struct fundo{
    ALLEGRO_BITMAP *bitmap;
    int x_screen;
    int scroll_x;
    int scroll_offset;
};

void verifica_init(bool flag, const char *string);

void init_basico();

struct tela dimensoes();

ALLEGRO_DISPLAY *configura_display(ALLEGRO_DISPLAY *display, int X_SCREEN, int Y_SCREEN);

int altura_texto(ALLEGRO_FONT *fonte);

bool mouse_no_botao(ALLEGRO_FONT *fonte, const char *texto, int x, int y, int mouse_x, int mouse_y);

void desenha_retangulo_option(ALLEGRO_FONT *fonte, const char *texto, int x, int y, struct coordenada *coord);


#endif