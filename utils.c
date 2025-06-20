#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "utils.h"
#include "tiro.h"

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
        al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    }
    display = al_create_display(X_SCREEN, Y_SCREEN);
    verifica_init(display, "display");
    return display;
}


struct inimigo *gera_inimigo(int x, int y){
    struct inimigo *enemy = (struct inimigo *)malloc(sizeof(struct inimigo));
    if(!enemy)
    verifica_init(enemy, "inimigo");
    enemy->x = x;
    enemy->y = y;
    enemy->atirando=0;
    enemy->lado = 1;
    enemy->vida = 5;
    enemy->gun = inicia_arma();
    return enemy;
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

bool colide_bala_x(int personagem_x, int personagem_y, int largura, int altura, int x1, int x2, int y1, int y2){
    int personagem_direita = personagem_x + largura;
    int personagem_topo = personagem_y - altura;

    return (personagem_x < x2 &&
           personagem_direita > x1 &&
           personagem_y > y1 &&
           personagem_topo < y2);
}

bool colide_x(int personagem_x, int personagem_y, int largura, int altura, struct obstacle predio){
    int personagem_direita = personagem_x + largura;
    int personagem_topo = personagem_y - altura;

    return (personagem_x < predio.x2 &&
           personagem_direita > predio.x1 &&
           personagem_y > predio.y1 &&
           personagem_topo < predio.y2);
}


bool colide_y(int personagem_x, int personagem_y, int largura, int altura, struct obstacle predio){
    int personagem_direita = personagem_x + largura;
    int personagem_topo = personagem_y - altura;

    return (personagem_x < predio.x2 &&
           personagem_direita > predio.x1 &&
           personagem_y >= predio.y1 &&
           personagem_topo <= predio.y2); //o sinal de igual resolve travar na plataforma
}

void gera_estruturas(struct obstacle estruturas[], int MAX_OBSTACULOS, int Y_SCREEN){
    int altura;
    int x_inimigo;
    unsigned int inimigo;
    for(int i=1;i<MAX_OBSTACULOS;i++){
        estruturas[i].x1 = estruturas[i-1].x2 + 150 + rand() % (75);
        estruturas[i].x2 = estruturas[i].x1 + 350 + rand() % (500);
        if (rand() % 2 == 0)
            altura = -125 + rand() % (51);   // -150 a -100 (inclusive)
        else
            altura = 75 + rand() % (51);
        if(estruturas[i-1].y1 + altura > Y_SCREEN - 100)
            estruturas[i].y1 = Y_SCREEN - 100;
        else if(estruturas[i-1].y1 + altura < 100)
            estruturas[i].y1 = 100;
        else
            estruturas[i].y1 = estruturas[i-1].y1 + altura;
        estruturas[i].y2 = Y_SCREEN;
        inimigo = rand() % 2; //aqui está 50%
        x_inimigo = estruturas[i].x1+20 + rand() % (estruturas[i].x2 - estruturas[i].x1 - 120);
        //printf("X Inimigo %d\n", x_inimigo);
        //printf("Inimigo %d\n", inimigo);
        if(inimigo == 0){
            estruturas[i].inimigo = 1;
            estruturas[i].enemy = gera_inimigo(x_inimigo, estruturas[i].y1-100);
        }
        else estruturas[i].inimigo = 0;
    }
}

struct boneco reseta_game(struct boneco personagem, struct obstacle estruturas[], int MAX_OBSTACULOS, int X_SCREEN, int Y_SCREEN){
    personagem.x = X_SCREEN/2;
    personagem.y = Y_SCREEN/2;
    personagem.velocidade_y = 0;
    personagem.chao = 1;
    personagem.vida = 3;
    gera_estruturas(estruturas, MAX_OBSTACULOS, Y_SCREEN);
    return personagem;
}

void destroi_inimigo(struct inimigo *enemy){
    destroi_arma(enemy->gun);
    free(enemy);
}