#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "tiro.h"
#include "utils.h"

void desenha_menu(ALLEGRO_BITMAP *fundo_menu , ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN);

void desenha_config(ALLEGRO_BITMAP *fundo_menu , ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN);

void desenha_video(ALLEGRO_BITMAP *fundo_menu, ALLEGRO_BITMAP *check, ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN, unsigned int resolucao, unsigned int tela_cheia);

void desenha_dificuladade(ALLEGRO_BITMAP *fundo_menu, ALLEGRO_BITMAP *check, ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN, unsigned int dificuldade);

int desenha_jogo(struct boneco *personagem, struct arma *gun, struct obstacle estruturas[], struct fundo fundo1, struct fundo fundo2, struct fundo fundo3, 
    ALLEGRO_BITMAP *fundo0, ALLEGRO_BITMAP *sprite_sheet, ALLEGRO_BITMAP *sprite_inimigo, ALLEGRO_BITMAP *sprite_bala[], ALLEGRO_BITMAP *predio,
    unsigned int sprite, int distancia_andada, double velocidade, double delta, int MAX_OBSTACULOS,int X_SCREEN, int Y_SCREEN);

void desenha_boss_fight(struct arma *gun, struct boneco *personagem, struct inimigo *final_boss, struct obstacle estrutura_boss, struct conjunto_sprites_boss sprites_boss,
    ALLEGRO_BITMAP *sprite_bala[], ALLEGRO_BITMAP *fundo_menu, ALLEGRO_BITMAP *sprite_sheet,  int sprite, int altura_boss, int largura_boss, int X_SCREEN, int Y_SCREEN);

int desenha_estruturas(ALLEGRO_BITMAP *sprite_inimigo, ALLEGRO_BITMAP *sprite_bala[], ALLEGRO_BITMAP *predio, struct obstacle estruturas[], struct boneco *personagem, 
    int distancia_andada, int sprite, double velocidade, double delta, int MAX_OBSTACULOS, int X_SCREEN, int Y_SCREEN);

void desenha_boss(struct inimigo *final_boss, struct conjunto_sprites_boss sprites_boss, int altura_boss, int largura_boss, int sprite);

void desenha_heart(ALLEGRO_BITMAP *coracao_cheio, int vida_atual, int x_screen, int y_screen);

void desenha_bala(struct arma *gun, ALLEGRO_BITMAP *sprite_bala[], int distancia_andada, int bala, int sprite);

void desenha_boneco_andando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_boneco_parado(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_inimigo_parado(ALLEGRO_BITMAP *sprite_sheet, int x, int y, double atirando);

void desenha_boneco_abaixado_andando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_boneco_abaixado(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_boneco_pulando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite);

void desenha_arma_rotacionada(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite, int flag);


#endif