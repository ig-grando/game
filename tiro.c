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

void atirou(int x, int y, int angulo, float cooldown, struct arma *gun){
    struct bala *bullet = inicia_bala(x+20, y-35, angulo);//trocar 0 por persongem.angulo depois
    if(!gun->primeira_bala){
        gun->primeira_bala = bullet;
        gun->ultima_bala = bullet;
    }
    else{
        gun->ultima_bala->proxima = bullet;
        gun->ultima_bala = bullet;
    }
    gun->cooldown = cooldown;
}


void avança_bala(struct bala *bullet, int velocidade){
    bullet->x += (cos(bullet->angulo * (ALLEGRO_PI / 180.0))) * velocidade;
    bullet->y += (sin(bullet->angulo * (ALLEGRO_PI / 180.0))) * velocidade;
}

void atualiza_lista(struct arma *gun, struct obstacle estruturas[], int velocidade, int distancia_andada, int MAX_OBSTACULOS, int X_SCREEN, int Y_SCREEN){
    struct bala *atual = gun->primeira_bala;
    struct bala *anterior = NULL;
    struct obstacle temp;
    int obs_tela1, obs_tela2, x1, x2, y1, y2, x3, x4, y3, y4;
    bool colidiu;
    while(atual != NULL){
        avança_bala(atual, velocidade);
        colidiu = 0;
        for(int i=0;i<MAX_OBSTACULOS;i++){
            obs_tela1 = estruturas[i].x1 - distancia_andada; //valor convertido posição na tela
            obs_tela2 = estruturas[i].x2 - distancia_andada;
            if(obs_tela2 >= 0 && obs_tela1 <= X_SCREEN){
                temp.x1 = estruturas[i].x1;
                temp.x2 = estruturas[i].x2;
                temp.y1 = estruturas[i].y1;
                temp.y2 = estruturas[i].y2;
                x1 = atual->x;
                x2 =  7;
                y1 =  atual->y;
                y2 = 7;
                if(colide_x(x1, y1, x2, y2, temp))
                    colidiu = 1;
                if(estruturas[i].inimigo){
                    x3 = estruturas[i].enemy->x;
                    x4 = x3 + 67;
                    y3 = estruturas[i].enemy->y;
                    y4 = y3 + 80;
                    if(colide_bala_x(x1, y1, x2, y2, x3, x4, y3, y4)){
                        estruturas[i].enemy->vida--;
                        colidiu = 1;
                    }
                }
            }
        }
        if(atual->x < 0+distancia_andada || atual->x > X_SCREEN+distancia_andada || atual->y < 0 || atual->y > Y_SCREEN || colidiu){
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

void atualiza_lista_inimigo(struct arma *gun, struct boneco *personagem, int velocidade, int distancia_andada,int X_SCREEN, int Y_SCREEN){
    struct bala *atual = gun->primeira_bala;
    struct bala *anterior = NULL;
    bool atinge_personagem;
    while(atual != NULL){
        avança_bala(atual, velocidade);
        atinge_personagem = colide_bala_x(personagem->x+distancia_andada, personagem->y, personagem->largura, personagem->altura, 
            atual->x-5, atual->x+5, atual->y-5, atual->y+5);//5 é o raio
        if(atual->x < 0+distancia_andada || atual->x > X_SCREEN+distancia_andada || atual->y < 0 || atual->y > Y_SCREEN || atinge_personagem){
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
            if(atinge_personagem){
                personagem->vida--;
                //printf("VIDA: %d\n", personagem->vida);
            }
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