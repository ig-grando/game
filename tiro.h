#ifndef TIRO_H
#define TIRO_H

struct arma{
    unsigned int tiros;
    float cooldown;
    struct bala *primeira_bala;
    struct bala *ultima_bala;
};

struct bala{
    int x;
    int y;
    int angulo;
    //char trajeto; //W, A, S, D, Q, E, Z, C
    struct bala *proxima;
};



struct arma *inicia_arma();

struct bala *inicia_bala(int x, int y, int angulo);

void atirou(int x, int y, int angulo, float cooldown, struct arma *gun);

void avança_bala(struct bala *bullet, int velocidade);

void atualiza_lista(struct arma *gun, int velocidade, int distancia_andada, int X_SCREEN, int Y_SCREEN);

void atualiza_lista_inimigo(struct arma *gun, struct boneco *personagem, int velocidade, int distancia_andada,int X_SCREEN, int Y_SCREEN);

void destroi_bala(struct bala *bullet);

void destroi_todas_balas(struct bala *bullet);

void destroi_arma(struct arma *gun);

#endif