#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "menu.h"
#include "utils.h"

#define PIXEL 8




void desenha_boneco_andando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite){
    int ini= PIXEL*2;
    int ini2 = PIXEL*35;
    if(personagem.lado >= 0){
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, ini, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, 0);
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 *PIXEL + ini, ini2, PIXEL*3, PIXEL*2, personagem.x, personagem.y+4 * PIXEL, 105, 70, 0);
    }
    else{
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, ini, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_scaled_bitmap(sprite_sheet, ini, ini2, PIXEL*3, PIXEL*2, personagem.x-4*PIXEL-4, personagem.y+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    al_flip_display();
}

void desenha_boneco_parado(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem){
    int ini= PIXEL*2;
    int ini2 = PIXEL*31;
    if(personagem.lado >= 0){
        al_draw_scaled_bitmap(sprite_sheet, ini, ini, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, 0);
        al_draw_scaled_bitmap(sprite_sheet, ini, ini2, PIXEL*3, PIXEL*2, personagem.x, personagem.y+4 * PIXEL, 105, 70, 0);
    }
    else{
        al_draw_scaled_bitmap(sprite_sheet, ini, ini, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_scaled_bitmap(sprite_sheet, ini, ini2, PIXEL*3, PIXEL*2, personagem.x-4*PIXEL-4, personagem.y+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    al_flip_display();
}

void desenha_boneco_abaixado_andando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite){
    int ini= PIXEL*26;
    int ini2 = PIXEL*31;
    if(personagem.lado >= 0){
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, PIXEL*2, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, 0);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x+PIXEL, personagem.y+ 5*PIXEL, 105, 70, 0);
    }
    else{
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, PIXEL*2, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x-5*PIXEL, personagem.y+ 5*PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    al_flip_display();
}

void desenha_boneco_abaixado(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem){
    int ini= PIXEL*26;
    int ini2 = PIXEL*31;
    if(personagem.lado >= 0){
        al_draw_scaled_bitmap(sprite_sheet, ini, PIXEL*2, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, 0);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x+PIXEL, personagem.y+ 5*PIXEL, 105, 70, 0);
    }
    else{
        al_draw_scaled_bitmap(sprite_sheet, ini, PIXEL*2, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x-5*PIXEL, personagem.y+ 5*PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    al_flip_display();
}

void desenha_boneco_pulando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem){
    int ini= PIXEL*34;
    int ini2 = PIXEL*31;
    //printf("Velociade Y: %d\n", personagem.velocidade_y);
    if(personagem.lado >= 0){
        if(personagem.velocidade_y > 0) al_draw_scaled_bitmap(sprite_sheet, ini + 4*PIXEL, PIXEL*10, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, 0);
        else al_draw_scaled_bitmap(sprite_sheet, ini, PIXEL*10, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, 0);
        al_draw_scaled_bitmap(sprite_sheet, 2*PIXEL, ini2, PIXEL*3, PIXEL*2, personagem.x, personagem.y+4 * PIXEL, 105, 70, 0);
    }
    else{
        if(personagem.velocidade_y > 0) al_draw_scaled_bitmap(sprite_sheet, ini + 4*PIXEL, PIXEL*10, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        else al_draw_scaled_bitmap(sprite_sheet, ini, PIXEL*10, PIXEL*2, PIXEL*4, personagem.x, personagem.y, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x-4*PIXEL-4, personagem.y+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
        }
    al_flip_display();
}



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

void desenha_jogo(struct boneco personagem, struct fundo fundo1, struct fundo fundo2, struct fundo fundo3, ALLEGRO_BITMAP *fundo0, ALLEGRO_BITMAP *sprite_sheet, unsigned int sprite, int X_SCREEN, int Y_SCREEN){
    fundo1.scroll_offset = fundo1.scroll_x % X_SCREEN;
    if (fundo1.scroll_offset > 0) fundo1.scroll_offset -= X_SCREEN;
    fundo2.scroll_offset = fundo2.scroll_x % X_SCREEN;
    if (fundo2.scroll_offset > 0) fundo2.scroll_offset -= X_SCREEN;
    fundo3.scroll_offset = fundo3.scroll_x % X_SCREEN;
    if (fundo3.scroll_offset > 0) fundo3.scroll_offset -= X_SCREEN;
    

    al_draw_scaled_bitmap(fundo0, 0, 0, al_get_bitmap_width(fundo0), al_get_bitmap_height(fundo0), 0, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_scaled_bitmap(fundo1.bitmap, 0, 0, al_get_bitmap_width(fundo1.bitmap), al_get_bitmap_height(fundo1.bitmap), fundo1.scroll_offset, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_scaled_bitmap(fundo1.bitmap, 0, 0, al_get_bitmap_width(fundo1.bitmap), al_get_bitmap_height(fundo1.bitmap), X_SCREEN + fundo1.scroll_offset, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_scaled_bitmap(fundo2.bitmap, 0, 0, al_get_bitmap_width(fundo2.bitmap), al_get_bitmap_height(fundo2.bitmap), fundo2.scroll_offset, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_scaled_bitmap(fundo2.bitmap, 0, 0, al_get_bitmap_width(fundo2.bitmap), al_get_bitmap_height(fundo2.bitmap), X_SCREEN + fundo2.scroll_offset, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_scaled_bitmap(fundo3.bitmap, 0, 0, al_get_bitmap_width(fundo3.bitmap), al_get_bitmap_height(fundo3.bitmap), fundo3.scroll_offset, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_scaled_bitmap(fundo3.bitmap, 0, 0, al_get_bitmap_width(fundo3.bitmap), al_get_bitmap_height(fundo3.bitmap), X_SCREEN + fundo3.scroll_offset, 0, X_SCREEN, Y_SCREEN, 0);
    
    if(!personagem.chao)
        desenha_boneco_pulando(sprite_sheet, personagem);
    else{
        if(personagem.direcao){
            if(personagem.abaixado)
                desenha_boneco_abaixado_andando(sprite_sheet, personagem, sprite/5);
            else
                desenha_boneco_andando(sprite_sheet, personagem, sprite/5);
        }
        else
            if(personagem.abaixado)
                desenha_boneco_abaixado(sprite_sheet, personagem);
            else
                desenha_boneco_parado(sprite_sheet, personagem);
    }
    
}

