#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "utils.c"
#include "menu.c"

#define FPS 60.0

#define KEY_SEEN 1 //A tecla foi detectada pelo menos uma vez.
#define KEY_DOWN 2 //A tecla está mantida pressionada


#define MENU 0
#define CONFIG 1
#define JOGO 2
#define VIDEO 3
#define AUDIO 4
#define CONTROLE 5
#define PAUSE 6
#define LOADING 7



int main(){
    init_basico();
    
    int X_SCREEN, Y_SCREEN;
    struct tela t;
    ALLEGRO_DISPLAY *display = NULL;
    display = configura_display(display, 0, 0);
    t = dimensoes();
    X_SCREEN = t.X_SCREEN;
    Y_SCREEN = t.Y_SCREEN;

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    verifica_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
    verifica_init(fila, "fila");
    
    ALLEGRO_FONT *font = al_create_builtin_font();
    verifica_init(font, "fonte");

    ALLEGRO_FONT *font_base = al_load_ttf_font("fontes/Pixellari.ttf", 30, 0);
    verifica_init(font_base, "fonte minha");

    ALLEGRO_BITMAP *fundo_menu = al_load_bitmap("usaveis/orig.png");
    verifica_init(fundo_menu, "usaveis/orig.png");

    ALLEGRO_BITMAP *check = al_load_bitmap("usaveis/check.png");
    verifica_init(check, "usaveis/check.png");

    ALLEGRO_BITMAP *fundo0 = al_load_bitmap("usaveis/1.png");
    verifica_init(fundo0, "usaveis/robo_bg.png");

    ALLEGRO_BITMAP *fundo1 = al_load_bitmap("usaveis/2.png");
    verifica_init(fundo1, "usaveis/robo_bg.png");

    ALLEGRO_BITMAP *fundo2 = al_load_bitmap("usaveis/4.png");
    verifica_init(fundo2, "usaveis/robo_bg.png");

    ALLEGRO_BITMAP *fundo3 = al_load_bitmap("usaveis/6.png");
    verifica_init(fundo3, "usaveis/robo_bg.png");

    ALLEGRO_BITMAP *sprite_sheet = al_load_bitmap("usaveis/sprite3.png");
    verifica_init(sprite_sheet, "usaveis/sprite3.png");

    ALLEGRO_BITMAP *cursor = al_load_bitmap("usaveis/cursor.png");
    verifica_init(fundo_menu, "usaveis/cursor.png");

    ALLEGRO_MOUSE_CURSOR *mouse = al_create_mouse_cursor(cursor, 0, 0);
    verifica_init(mouse, "create_mouse_cursor");
    
    //ALLEGRO_DISPLAY_MODE display_config;
    //al_get_display_mode(0, &display_config);


    verifica_init(al_set_mouse_cursor(display, mouse), "set_mouse_cursor");

    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_mouse_event_source());
    al_register_event_source(fila, al_get_display_event_source(display));
    al_register_event_source(fila, al_get_timer_event_source(timer));

    al_start_timer(timer);
    
    ALLEGRO_EVENT event;
    struct boneco personagem;
    personagem.x = personagem.y = 500;
    personagem.chao = 1;
    personagem.velocidade_y = 0;
    unsigned char quadro=0, sair=0;
    unsigned int tela = MENU; //começa no menu
    unsigned int resolucao = 1;
    unsigned int sprite = 1;
    bool tela_cheia = 1, aplicar = 0;
    double start_load, delta=1, velocidade = 250, gravidade = 1800, pulo = 700;
    double start_delta = al_get_time();
    unsigned char key[ALLEGRO_KEY_MAX]; //um indice do vetor para cada tecla, com máximo para todos as keys do Allegro
    memset(key, 0, sizeof(key)); //coloca 0 em todo o vetor
    while(1){
        al_wait_for_event(fila, &event);
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                //if(key[ALLEGRO_KEY_W])
                    //personagem.y -= (velocidade * delta);
                //if(key[ALLEGRO_KEY_S])
                    //personagem.y += (velocidade * delta);
                personagem.direcao = 0;
                if(key[ALLEGRO_KEY_A])
                    personagem.direcao -= 1;
                if(key[ALLEGRO_KEY_D])
                    personagem.direcao += 1;
                if(key[ALLEGRO_KEY_SPACE] && personagem.chao){
                    personagem.velocidade_y = -pulo;
                    personagem.chao = 0;
                }
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= ~KEY_SEEN; //&= faz a operação AND e ~faz um NOT, O resultado remove KEY_SEEN, mas mantém se KEY_DOWN.
                quadro = 1;
                double now_delta = al_get_time();
                delta = now_delta - start_delta;
                start_delta = now_delta;

                if(!personagem.chao)
                    personagem.velocidade_y += gravidade * delta; //para competir com o pulo, vai acumulando gravidade

                personagem.x += personagem.direcao * velocidade * delta;
                personagem.y += personagem.velocidade_y * delta;

                if(personagem.y >= Y_SCREEN*0.8){
                    personagem.y = Y_SCREEN*0.8;
                    personagem.velocidade_y = 0;
                    personagem.chao = 1;
                }
            break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_DOWN; //faz operação OU bit a bit, então ambos estão ativos (vista e pressionada)
                //colocar um if se estiver no game para dar
                switch(event.keyboard.keycode){
                    case ALLEGRO_KEY_ESCAPE:
                        switch(tela){
                            case MENU:
                                sair = 1;
                            break;
                            case CONFIG:
                                tela = MENU;
                            break;
                            case VIDEO:
                                tela = CONFIG;
                            break;
                            case AUDIO:
                                tela = CONFIG;
                            break;
                            case CONTROLE:
                                tela = CONFIG;
                            break;
                            case JOGO:
                                tela = CONFIG;
                            break;
                            case LOADING:
                                tela = MENU;
                            break;
                        }
                    break;
                }
            break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= ~KEY_DOWN; //fica 000... nenhum ativo
            break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                switch(tela){
                    case MENU:
                        if(mouse_no_botao(font_base, "Iniciar", (X_SCREEN*0.25), Y_SCREEN/2, event.mouse.x, event.mouse.y)){
                            start_load = al_get_time();
                            tela = LOADING;
                        }
                        if(mouse_no_botao(font_base, "Configurações", (X_SCREEN*0.50), Y_SCREEN/2, event.mouse.x, event.mouse.y))
                            tela = CONFIG;
                        if(mouse_no_botao(font_base, "Sair", (X_SCREEN*0.75), Y_SCREEN/2, event.mouse.x, event.mouse.y))
                            sair = 1;
                    break;
                    case CONFIG:
                        if(mouse_no_botao(font_base, "Video", X_SCREEN/2, Y_SCREEN*0.35, event.mouse.x, event.mouse.y))
                            tela = VIDEO;
                        if(mouse_no_botao(font_base, "Audio", X_SCREEN/2, Y_SCREEN*0.40, event.mouse.x, event.mouse.y))
                            tela = AUDIO;
                        if(mouse_no_botao(font_base, "Controle", X_SCREEN/2, Y_SCREEN*0.45, event.mouse.x, event.mouse.y))
                            tela =  CONTROLE;
                        if(mouse_no_botao(font_base, "Voltar", X_SCREEN/2, Y_SCREEN*0.60, event.mouse.x, event.mouse.y))
                            tela = MENU;
                    break;
                    case VIDEO:
                        if(mouse_no_botao(font_base, "1280 x 720", X_SCREEN/2, Y_SCREEN*0.35, event.mouse.x, event.mouse.y))
                            resolucao = 0;
                        if(mouse_no_botao(font_base, "1920 x 1080", X_SCREEN/2, Y_SCREEN*0.40, event.mouse.x, event.mouse.y))
                            resolucao = 1;
                        if(mouse_no_botao(font_base, "2560 x 1440", X_SCREEN/2, Y_SCREEN*0.45, event.mouse.x, event.mouse.y))
                            resolucao = 2;
                        if(mouse_no_botao(font_base, "FULL-SCREEN", X_SCREEN/2, Y_SCREEN*0.55, event.mouse.x, event.mouse.y))
                            tela_cheia = !tela_cheia;
                        if(mouse_no_botao(font_base, "Aplicar", X_SCREEN*0.45, Y_SCREEN*0.60, event.mouse.x, event.mouse.y))
                            aplicar = 1;
                        if(mouse_no_botao(font_base, "Voltar", X_SCREEN*0.55, Y_SCREEN*0.60, event.mouse.x, event.mouse.y))
                            tela = CONFIG;
                    break;
                break;
                }
                
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                sair = 1;
                break;
        }
        if(sair) break; //sai do loop se clicar para fechar ou apertar esq
        if(aplicar == 1){
            int current_flags = al_get_display_flags(display);
            bool fullscreen = (current_flags & ALLEGRO_FULLSCREEN_WINDOW);
            if (tela_cheia && !fullscreen) {
                al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 1);
            } 
            else if (!tela_cheia && fullscreen) {
                al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 0);
            }
    
    aplicar = 0;
        }
        if(quadro && al_is_event_queue_empty(fila)){
            switch(tela){
                case MENU:
                    desenha_menu(fundo_menu, font_base, X_SCREEN, Y_SCREEN);
                    quadro = 0;
                break;
                case CONFIG:
                    desenha_config(fundo_menu, font_base, X_SCREEN, Y_SCREEN);
                    quadro = 0;
                break;
                case VIDEO:
                    desenha_video(fundo_menu, check, font_base, X_SCREEN, Y_SCREEN, resolucao, tela_cheia);
                    quadro = 0;
                break;
                case AUDIO:
                    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_scaled_bitmap(sprite_sheet, 8, 8, 16, 24, 500, 500, 100, 100, 0);
                    al_flip_display();
                    quadro = 0;
                break;
                case CONTROLE:
                    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_flip_display();
                    quadro = 0;
                break;
                case JOGO:
                    al_draw_scaled_bitmap(fundo0, 0, 0, al_get_bitmap_width(fundo0), al_get_bitmap_height(fundo0), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_scaled_bitmap(fundo1, 0, 0, al_get_bitmap_width(fundo1), al_get_bitmap_height(fundo1), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_scaled_bitmap(fundo2, 0, 0, al_get_bitmap_width(fundo2), al_get_bitmap_height(fundo2), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_scaled_bitmap(fundo3, 0, 0, al_get_bitmap_width(fundo3), al_get_bitmap_height(fundo3), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    desenha_boneco(sprite_sheet ,personagem.x, personagem.y, sprite/5, personagem.direcao);
                    sprite++;
                    if(sprite >= 20)
                        sprite = 0;
                    quadro = 0;
                break;
                case LOADING:
                    double now_load = al_get_time();
                    if(now_load - start_load >= 1.5)
                        tela = JOGO;
                    al_draw_scaled_bitmap(fundo0, 0, 0, al_get_bitmap_width(fundo0), al_get_bitmap_height(fundo0), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Carregando...");
                    al_flip_display();
                    quadro = 0;
                break;
            }
            //al_clear_to_color(al_map_rgb(0, 0, 0));
            
        }
    }

    al_destroy_timer(timer);
    al_destroy_mouse_cursor(mouse);
    al_destroy_display(display);
    al_destroy_font(font_base);
    al_destroy_bitmap(fundo_menu);
    al_destroy_bitmap(check);
    al_destroy_bitmap(fundo0);
    al_destroy_bitmap(fundo1);
    al_destroy_bitmap(fundo2);
    al_destroy_bitmap(fundo3);
    al_destroy_bitmap(cursor);
    al_destroy_event_queue(fila);
    return 0;
}