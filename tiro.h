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

void atirou(struct boneco personagem, struct arma *gun);

void avança_bala(struct bala *bullet, int velocidade);

void destroi_bala(struct bala *bullet);

void destroi_todas_balas(struct bala *bullet);

void destroi_arma(struct arma *gun);

#endif