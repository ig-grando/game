#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "tiro.h"
#include "utils.h"

void desenha_menu(ALLEGRO_BITMAP *fundo_menu , ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN);

void desenha_config(ALLEGRO_BITMAP *fundo_menu , ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN);

void desenha_video(ALLEGRO_BITMAP *fundo_menu, ALLEGRO_BITMAP *check, ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN, unsigned int resolucao, unsigned int tela_cheia);

int desenha_jogo(struct boneco *personagem, struct arma *gun, struct obstacle estruturas[], struct fundo fundo1, struct fundo fundo2, struct fundo fundo3, 
    ALLEGRO_BITMAP *fundo0, ALLEGRO_BITMAP *sprite_sheet, ALLEGRO_BITMAP *sprite_inimigo, ALLEGRO_BITMAP *sprite_bala[],
    unsigned int sprite, int distancia_andada, double velocidade, double delta, int MAX_OBSTACULOS,int X_SCREEN, int Y_SCREEN);

void desenha_boneco_andando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_boneco_parado(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_boneco_abaixado_andando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_boneco_abaixado(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_boneco_pulando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

#endif