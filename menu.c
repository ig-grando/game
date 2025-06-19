#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "menu.h"
#include "utils.h"
#include "tiro.h"

#define PIXEL 8


void desenha_arma_rotacionada(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite, int flag){
    int ini= PIXEL*2;
    int ini2 = PIXEL*31;

    ALLEGRO_BITMAP *arma_sprite = al_create_sub_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, ini2, PIXEL*3, PIXEL*2);
    float cx = (PIXEL * 3) / 2.0; //Define centro do sprite (para rotacionar no meio)
    float cy = (PIXEL * 2) / 2.0;
    float escala_x = 105.0 / (PIXEL * 3); //Escalas desejadas
    float escala_y = 70.0 / (PIXEL * 2);
    int angulo_graus = 0;
    float radianos = angulo_graus * (ALLEGRO_PI / 180.0);
    al_draw_scaled_rotated_bitmap(arma_sprite, cx, cy, personagem.x+7*PIXEL, personagem.y-108+8*PIXEL, escala_x, escala_y, radianos, flag); 
    al_destroy_bitmap(arma_sprite);
}

void desenha_boneco_andando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite){
    int ini= PIXEL*2;
    int ini2 = PIXEL*31;
    if(personagem.lado >= 0){
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, ini, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, 0);
        if(personagem.atirando)
            desenha_arma_rotacionada(sprite_sheet, personagem, sprite, 0);
            
        else
            al_draw_scaled_bitmap(sprite_sheet, ini, ini2, PIXEL*3, PIXEL*2, personagem.x, personagem.y-108+4 * PIXEL, 105, 70, 0);
    }
    else{
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, ini, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        if(personagem.atirando)
            al_draw_scaled_bitmap(sprite_sheet,  sprite * 4 *PIXEL + ini, ini2, PIXEL*3, PIXEL*2, personagem.x-4*PIXEL-4, personagem.y-108+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_scaled_bitmap(sprite_sheet, ini, ini2, PIXEL*3, PIXEL*2, personagem.x-4*PIXEL-4, personagem.y-108+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    
}

void desenha_boneco_parado(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite){
    int ini= PIXEL*2;
    int ini2 = PIXEL*31;
    if(personagem.lado >= 0){
        al_draw_scaled_bitmap(sprite_sheet, ini, ini, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, 0);
        if(personagem.atirando)
            al_draw_scaled_bitmap(sprite_sheet, sprite * 4 *PIXEL + ini, ini2, PIXEL*3, PIXEL*2, personagem.x, personagem.y-108+4 * PIXEL, 105, 70, 0);
        else
            al_draw_scaled_bitmap(sprite_sheet, ini, ini2, PIXEL*3, PIXEL*2, personagem.x, personagem.y-108+4 * PIXEL, 105, 70, 0);
            
    }
    else{
        al_draw_scaled_bitmap(sprite_sheet, ini, ini, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        if(personagem.atirando)
            al_draw_scaled_bitmap(sprite_sheet, sprite * 4 *PIXEL + ini, ini2, PIXEL*3, PIXEL*2, personagem.x-4*PIXEL-4, personagem.y-108+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_scaled_bitmap(sprite_sheet, ini, ini2, PIXEL*3, PIXEL*2, personagem.x-4*PIXEL-4, personagem.y-108+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    
}

void desenha_inimigo_parado(ALLEGRO_BITMAP *sprite_sheet, int x, int y, bool atirando, int sprite){
    int ini= PIXEL*2;
    int ini2 = PIXEL*54;
    al_draw_scaled_bitmap(sprite_sheet, ini, ini, PIXEL*2, PIXEL*4, x, y-9, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
    if(atirando){
        al_draw_scaled_bitmap(sprite_sheet, ini, ini2, PIXEL*3, PIXEL*3, x-4*PIXEL-4, y-9+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    else
        al_draw_scaled_bitmap(sprite_sheet, (ini + 3*PIXEL), ini2, PIXEL*4, PIXEL*2, x- 3*PIXEL-4, y-4, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
}


void desenha_boneco_abaixado_andando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem, int sprite){
    int ini= PIXEL*26;
    int ini2 = PIXEL*31;
    if(personagem.lado >= 0){
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, PIXEL*2, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, 0);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x+PIXEL, personagem.y-108+ 5*PIXEL, 105, 70, 0);
    }
    else{
        al_draw_scaled_bitmap(sprite_sheet, sprite * 4 * PIXEL + ini, PIXEL*2, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x-5*PIXEL, personagem.y-108+ 5*PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    
}

void desenha_boneco_abaixado(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem){
    int ini= PIXEL*26;
    int ini2 = PIXEL*31;
    if(personagem.lado >= 0){
        al_draw_scaled_bitmap(sprite_sheet, ini, PIXEL*2, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, 0);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x+PIXEL, personagem.y-108+ 5*PIXEL, 105, 70, 0);
    }
    else{
        al_draw_scaled_bitmap(sprite_sheet, ini, PIXEL*2, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x-5*PIXEL, personagem.y-108+ 5*PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
    }
    
}

void desenha_boneco_pulando(ALLEGRO_BITMAP *sprite_sheet, struct boneco personagem){
    int ini= PIXEL*34;
    int ini2 = PIXEL*31;
    //printf("Velociade Y: %d\n", personagem.velocidade_y);
    if(personagem.lado >= 0){
        if(personagem.velocidade_y > 0) al_draw_scaled_bitmap(sprite_sheet, ini + 4*PIXEL, PIXEL*10, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, 0);
        else al_draw_scaled_bitmap(sprite_sheet, ini, PIXEL*10, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, 0);
        al_draw_scaled_bitmap(sprite_sheet, 2*PIXEL, ini2, PIXEL*3, PIXEL*2, personagem.x, personagem.y-108+4 * PIXEL, 105, 70, 0);
    }
    else{
        if(personagem.velocidade_y > 0) al_draw_scaled_bitmap(sprite_sheet, ini + 4*PIXEL, PIXEL*10, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        else al_draw_scaled_bitmap(sprite_sheet, ini, PIXEL*10, PIXEL*2, PIXEL*4, personagem.x, personagem.y-108, 70, 140, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_scaled_bitmap(sprite_sheet, PIXEL*2, ini2, PIXEL*3, PIXEL*2, personagem.x-4*PIXEL-4, personagem.y-108+4 * PIXEL, 105, 70, ALLEGRO_FLIP_HORIZONTAL);
        }
    
}

void desenha_bala(struct arma *gun, int distancia_andada){
    struct bala *bullet;
    if(!gun->primeira_bala) return;
    bullet = gun->primeira_bala;
    while(bullet != NULL){
        int x = bullet->x;
        int y = bullet->y;
        al_draw_filled_rectangle(x, y, x+7, y+7, al_map_rgb(255, 125, 250));
        bullet = bullet->proxima;
    }
}

void desenha_estruturas(ALLEGRO_BITMAP *sprite_inimigo, struct obstacle estruturas[], int distancia_andada, int sprite, double velocidade, double delta, int MAX_OBSTACULOS, int X_SCREEN, int Y_SCREEN){
    int obs_tela1, obs_tela2, enemy_tela1, enemy_tela2;
    for(int i=0;i<MAX_OBSTACULOS;i++){
        obs_tela1 = estruturas[i].x1 - distancia_andada; //valor convertido posição na tela
        obs_tela2 = estruturas[i].x2 - distancia_andada;
        if(obs_tela2 >= 0 && obs_tela1 <= X_SCREEN){
            al_draw_filled_rectangle(obs_tela1, estruturas[i].y1, obs_tela2, estruturas[i].y2, al_map_rgb(128, 128, 128)); //predio
            //printf("inimigo: %d\n", estruturas[i].inimigo);
            if(estruturas[i].inimigo){
                struct inimigo *temp;
                temp = estruturas[i].enemy;
                enemy_tela1 = temp->x - distancia_andada;
                enemy_tela2 = temp->x + 80 - distancia_andada;
                //al_draw_filled_rectangle(enemy_tela1, temp->y, enemy_tela2, temp->y+100, al_map_rgb(255, 0, 0));
                desenha_inimigo_parado(sprite_inimigo, enemy_tela1, temp->y, temp->atirando, sprite);
                temp->gun->cooldown -= delta;
                desenha_bala(temp->gun, distancia_andada);
                if(temp->gun->cooldown <= 0)
                    atirou(enemy_tela1, temp->y+40, 180, 1.0, temp->gun);
                atualiza_lista(temp->gun, velocidade*delta*1.2, X_SCREEN, Y_SCREEN);
            }   
        }
    }
}


void desenha_menu(ALLEGRO_BITMAP *fundo_menu , ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN){
    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), (X_SCREEN*0.25), Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Iniciar");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), (X_SCREEN*0.5), Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Configurações");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), (X_SCREEN*0.75), Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Sair");
    
}

void desenha_config(ALLEGRO_BITMAP *fundo_menu , ALLEGRO_FONT *font_base, int X_SCREEN, int Y_SCREEN){
    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, "Video");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.40, ALLEGRO_ALIGN_CENTER, "Audio");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.45, ALLEGRO_ALIGN_CENTER, "Controle");
    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN*0.60, ALLEGRO_ALIGN_CENTER, "Voltar");
    
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
    
}

void desenha_jogo(struct boneco personagem, struct arma *gun, struct obstacle estruturas[], struct fundo fundo1, struct fundo fundo2, struct fundo fundo3, ALLEGRO_BITMAP *fundo0, ALLEGRO_BITMAP *sprite_sheet, ALLEGRO_BITMAP *sprite_inimigo, 
    unsigned int sprite, int distancia_andada, double velocidade, double delta, int MAX_OBSTACULOS,int X_SCREEN, int Y_SCREEN){
    
        fundo1.scroll_offset = fundo1.scroll_x % X_SCREEN;
    if (fundo1.scroll_offset > 0) fundo1.scroll_offset -= X_SCREEN; //Corrige casos em que o resto é positivo, garantindo que o offset seja sempre negativo, para quando andar para esquerda
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
    
    desenha_estruturas(sprite_inimigo, estruturas, distancia_andada, sprite, velocidade, delta, MAX_OBSTACULOS, X_SCREEN, Y_SCREEN);
    desenha_bala(gun, distancia_andada);
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
                desenha_boneco_parado(sprite_sheet, personagem, sprite/5);
    }
}