#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "tiro.h"
#include "utils.h"

struct arma *inicia_arma(){
    struct arma *arma_nova = (struct arma *)malloc(sizeof(struct arma));
    if(!arma_nova){
        printf("ERRO MALLOC ARMA\n");
        exit(1);
    }
    arma_nova->cooldown = 0;
    arma_nova->tiros = 0;
    arma_nova->primeira_bala = NULL;
    arma_nova->ultima_bala = NULL;
    return arma_nova;
}

struct bala *inicia_bala(int x, int y, int angulo){
    struct bala *b = (struct bala *)malloc(sizeof(struct bala));
    if(!b){ 
        printf("ERRO MALLOC BALA\n");
        exit(1);
    }
    b->x = x;
    b->y = y;
    b->angulo = angulo;
    b->proxima = NULL;
    return b;
}

void atirou(struct boneco personagem, struct arma *gun){
    struct bala *bullet = inicia_bala(personagem.x, personagem.y, 0);//trocar 0 por persongem.angulo depois
    if(!gun->primeira_bala){
        gun->primeira_bala = bullet;
        gun->ultima_bala = bullet;
    }
    else{
        gun->ultima_bala->proxima = bullet;
        gun->ultima_bala = bullet;
    }
    gun->cooldown = 0.2;
}


void avança_bala(struct bala *bullet, int velocidade){
    bullet->x += cos(bullet->angulo) * velocidade;
    bullet->y += sin(bullet->angulo) * velocidade;
}

void atualiza_lista(struct arma *gun, int velocidade, int X_SCREEN, int Y_SCREEN){
    struct bala *atual = gun->primeira_bala;
    struct bala *anterior = NULL;
    while(atual != NULL){
        avança_bala(atual, velocidade);
        if(atual->x < 0 || atual->x > X_SCREEN || atual->y < 0 || atual->y > Y_SCREEN){
            struct bala *remover = atual;
            if(anterior == NULL){ //primeira
                atual = atual->proxima;
                gun->primeira_bala = atual;
            }
            else{
                anterior->proxima = atual->proxima;
                atual = atual->proxima;
            }
            destroi_bala(remover);
        }
        else{
            anterior = atual;
            atual = atual->proxima;
        }
    }
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