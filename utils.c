#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "utils.h"

void verifica_init(bool flag, const char *string){
    if(!flag){
        printf("Não foi possível inicializar: %s\n", string);
        exit(1);
    }
}

void init_basico(){
    verifica_init(al_init(), "al_init"); //inicia as funções da biblioteca
    verifica_init(al_init_primitives_addon(), "primitives_addon");
    verifica_init(al_install_keyboard(), "teclado");
    verifica_init(al_install_mouse(), "mouse");
    verifica_init(al_init_image_addon(), "image_addon");
    verifica_init(al_init_font_addon(), "font addon");
    verifica_init(al_init_ttf_addon(), "ttf addon");
}


struct tela dimensoes(){
    int X_SCREEN;
    int Y_SCREEN;
    struct tela t;
    ALLEGRO_DISPLAY_MODE monitor_config;
    al_get_display_mode(0, &monitor_config);
    X_SCREEN = monitor_config.width;
    Y_SCREEN = monitor_config.height; 
    t.X_SCREEN = X_SCREEN;
    t.Y_SCREEN = Y_SCREEN;
    return t;
}

ALLEGRO_DISPLAY *configura_display(ALLEGRO_DISPLAY *display, int X_SCREEN, int Y_SCREEN){
    if(display)
        al_destroy_display(display);
    if(!X_SCREEN){
        struct tela t;
        t = dimensoes();
        X_SCREEN = t.X_SCREEN;
        Y_SCREEN = t.Y_SCREEN;
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    }
    display = al_create_display(X_SCREEN, Y_SCREEN);
    verifica_init(display, "display");
    return display;
}


int altura_texto(ALLEGRO_FONT *fonte) {
    int bbx, bby, bbw, bbh;
    al_get_text_dimensions(fonte, "Ay", &bbx, &bby, &bbw, &bbh);
    return bbh;
}

bool mouse_no_botao(ALLEGRO_FONT *fonte, const char *texto, int x, int y, int mouse_x, int mouse_y){
    int altura = al_get_font_line_height(fonte);
    int largura = al_get_text_width(fonte, texto);
    return (mouse_x <= largura/2+x && mouse_x >= x-largura/2 
        && mouse_y <= y+altura/2 && mouse_y >= y - altura/2);
}


void desenha_retangulo_option(ALLEGRO_FONT *fonte, const char *texto, int x, int y, struct coordenada *coord){
    int altura_fonte =  altura_texto(fonte);
    int x2 = (x - (al_get_text_width(fonte, texto)/2) - 10);
    int x1 = x2 - altura_fonte;
    int y2 =  y+altura_fonte;
    int y1 = y;
    coord->x = x1;
    coord->y = y1;
    al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 0), 3);
}

bool colide_x(int personagem_x, int personagem_y, int largura, int altura, struct obstacle predio) {
    int personagem_direita = personagem_x + largura;
    int personagem_topo = personagem_y - altura;

    return (personagem_x < predio.x2 &&
           personagem_direita > predio.x1 &&
           personagem_y > predio.y1 &&
           personagem_topo < predio.y2);
}


bool colide_y(int personagem_x, int personagem_y, int largura, int altura, struct obstacle predio) {
    int personagem_direita = personagem_x + largura;
    int personagem_topo = personagem_y - altura;

    return (personagem_x < predio.x2 &&
           personagem_direita > predio.x1 &&
           personagem_y >= predio.y1 &&
           personagem_topo <= predio.y2); //o sinal de igual resolve travar na plataforma
}