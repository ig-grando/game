#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "utils.h"

void desenha_menu(ALLEGRO_BITMAP *fundo_menu , ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN){
    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), (X_SCREEN*0.25), Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Iniciar");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), (X_SCREEN*0.5), Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Configurações");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), (X_SCREEN*0.75), Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Sair");
    al_flip_display();
}

void desenha_config(ALLEGRO_BITMAP *fundo_menu , ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN){
    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, "Video");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.40, ALLEGRO_ALIGN_CENTER, "Audio");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.45, ALLEGRO_ALIGN_CENTER, "Controle");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.60, ALLEGRO_ALIGN_CENTER, "Voltar");
    al_flip_display();
}

void desenha_video(ALLEGRO_BITMAP *fundo_menu, ALLEGRO_BITMAP *check, ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN, unsigned int resolucao, unsigned int tela_cheia){
    struct coordenada coord0, coord1, coord2, coord3;
    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, "1280 x 720");
    desenha_retangulo_option(font_base, "1280 x 720", X_SCREEN/2, Y_SCREEN*0.35, &coord0);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.40, ALLEGRO_ALIGN_CENTER, "1920 x 1080");
    desenha_retangulo_option(font_base, "1920 x 1080", X_SCREEN/2, Y_SCREEN*0.40, &coord1);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.45, ALLEGRO_ALIGN_CENTER, "2560 x 1440");
    desenha_retangulo_option(font_base, "2560 x 1440", X_SCREEN/2, Y_SCREEN*0.45, &coord2);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.55, ALLEGRO_ALIGN_CENTER, "FULL-SCREEN");
    desenha_retangulo_option(font_base, "FULL-SCREEN", X_SCREEN/2, Y_SCREEN*0.55, &coord3);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN*0.55, Y_SCREEN*0.60, ALLEGRO_ALIGN_CENTER, "Voltar");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN*0.45, Y_SCREEN*0.60, ALLEGRO_ALIGN_CENTER, "Aplicar");

    if(resolucao == 0) al_draw_bitmap(check, coord0.x, coord0.y, 0);
    if(resolucao == 1) al_draw_bitmap(check, coord1.x, coord1.y, 0);
    if(resolucao == 2) al_draw_bitmap(check, coord2.x, coord2.y, 0);
    if(tela_cheia == 1) al_draw_bitmap(check, coord3.x, coord3.y, 0);
    al_flip_display();
}

void desenha_boneco(int x, int y){
    al_draw_filled_rectangle(x, y, x+15, y+15, al_map_rgb(255, 0, 0));
    al_flip_display();
}