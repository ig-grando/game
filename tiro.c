#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>


struct arma{
    unsigned int tiros;
    unsigned int cooldown;
    struct bala *primeira_bala;
};

struct bala{
    int x;
    int y;
    int angulo;
    //char trajeto; //W, A, S, D, Q, E, Z, C
    struct bala *proxima;
};

struct arma *inicia_arma(){
    struct arma *arma_nova = (struct arma *)malloc(sizeof(struct arma));
    if(!arma_nova){
        printf("ERRO MALLOC ARMA\n");
        exit(1);
    }
    arma_nova->cooldown = 0;
    arma_nova->tiros = 0;
    arma_nova->primeira_bala = NULL;
    return arma_nova;
}

struct bala *inicia_bala(struct bala *prox, int x, int y, int angulo){
    struct bala *b = (struct bala *)malloc(sizeof(struct bala));
    if(!b){ 
        printf("ERRO MALLOC BALA\n");
        exit(1);
    }
    b->x = x;
    b->y = y;
    b->angulo = angulo;
    b->proxima = prox;
    return b;
}

void avança_bala(struct bala *bullet, int velocidade){
    bullet->x += cos(bullet->angulo) * velocidade;
    bullet->y += sin(bullet->angulo) * velocidade;
}

void destroi_bala(struct bala *bullet){
    free(bullet);
}

void destroi_todas_balas(struct bala *bullet){
    struct bala *aux;
    while(bullet != NULL){
        aux = bullet;
        bullet = bullet->proxima;
        free(aux);
    }
}

void destroi_arma(struct arma *gun){
    destroi_todas_balas(gun->primeira_bala);
    free(gun);
}