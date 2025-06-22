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
    int angulo;
    int largura;
    int altura;
    unsigned int vida;
    bool abaixado;
    bool chao;
    bool atirando;
};

struct inimigo{
    struct arma *gun;
    int x;
    int y;
    int lado;
    unsigned int vida;
    int atirando;
};

struct tela{
    int X_SCREEN;
    int Y_SCREEN;
};


struct obstacle{
    int x1;
    int x2;
    int y1;
    int y2;
    bool inimigo;
    struct inimigo *enemy;
};

struct fundo{
    ALLEGRO_BITMAP *bitmap;
    int x_screen;
    int scroll_x;
    int scroll_offset;
};

struct conjunto_sprites_boss{
    ALLEGRO_BITMAP *parado;
    ALLEGRO_BITMAP *atirando;
    ALLEGRO_BITMAP *atirando_cima;
};

void verifica_init(bool flag, const char *string);

void init_basico();

struct tela dimensoes();

ALLEGRO_DISPLAY *configura_display(ALLEGRO_DISPLAY *display, int X_SCREEN, int Y_SCREEN);

int altura_texto(ALLEGRO_FONT *fonte);

bool mouse_no_botao(ALLEGRO_FONT *fonte, const char *texto, int x, int y, int mouse_x, int mouse_y);

void desenha_retangulo_option(ALLEGRO_FONT *fonte, const char *texto, int x, int y, struct coordenada *coord);

bool colide_x(int personagem_x, int personagem_y, int largura, int altura, struct obstacle predio);

//identico ao outro colide mas nçao quis mudar ele por causa struct
bool colide_bala_x(int personagem_x, int personagem_y, int largura, int altura, int x1, int x2, int y1, int y2);


#endif