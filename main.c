#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>


#define FPS 60.0

#define KEY_SEEN 1 //A tecla foi detectada pelo menos uma vez.
#define KEY_DOWN 2 //A tecla está mantida pressionada

#define MENU 0
#define CONFIG 1
#define JOGO 2


void init_all(bool flag, const char *string){
    if(!flag){
        printf("Não foi possível inicializar: %s\n", string);
        exit(1);
    }
}

bool mouse_no_botao(ALLEGRO_FONT *fonte, const char *texto, int x, int y, int mouse_x, int mouse_y){
    int altura = al_get_font_line_height(fonte);
    int largura = al_get_text_width(fonte, texto);
    return (mouse_x <= largura/2+x && mouse_x >= x-largura/2 
        && mouse_y <= y+altura/2 && mouse_y >= y - altura/2);
}

int main(){
    init_all(al_init(), "al_init"); //inicia as funções da biblioteca
    init_all(al_init_primitives_addon(), "primitives_addon");
    init_all(al_install_keyboard(), "teclado");
    init_all(al_install_mouse(), "mouse");
    init_all(al_init_image_addon(), "image_addon");
    init_all(al_init_font_addon(), "font addon");
    init_all(al_init_ttf_addon(), "ttf addon");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    init_all(timer, "timer");

    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
    init_all(fila, "fila");
    
    ALLEGRO_FONT *font = al_create_builtin_font();
    init_all(font, "fonte");

    ALLEGRO_FONT *font_base = al_load_ttf_font("Pixellari.ttf", 30, 0);
    init_all(font_base, "fonte minha");

    ALLEGRO_BITMAP *fundo_menu = al_load_bitmap("usaveis/orig.png");
    init_all(fundo_menu, "usaveis/orig.png");

    ALLEGRO_BITMAP *cursor = al_load_bitmap("usaveis/cursor.png");
    init_all(fundo_menu, "usaveis/cursor.png");

    ALLEGRO_MOUSE_CURSOR *mouse = al_create_mouse_cursor(cursor, 0, 0);
    init_all(mouse, "create_mouse_cursor");
    
    ALLEGRO_DISPLAY_MODE display_config;
    al_get_display_mode(0, &display_config);

    long X_SCREEN, Y_SCREEN;
    X_SCREEN = display_config.width;
    Y_SCREEN = display_config.height;
    ALLEGRO_DISPLAY *display = al_create_display(X_SCREEN, Y_SCREEN);
    init_all(display, "display");

    init_all(al_set_mouse_cursor(display, mouse), "set_mouse_cursor");

    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_mouse_event_source());
    al_register_event_source(fila, al_get_display_event_source(display));
    al_register_event_source(fila, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    unsigned char quadro, sair;
    unsigned int tela = MENU; //começa no menu
    unsigned char key[ALLEGRO_KEY_MAX]; //um indice do vetor para cada tecla, com máximo para todos as keys do Allegro
    memset(key, 0, sizeof(key)); //coloca 0 em todo o vetor
    while(1){
        al_wait_for_event(fila, &event);
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                /*if(key[ALLEGRO_KEY_W])
                if(key[ALLEGRO_KEY_S])
                if(key[ALLEGRO_KEY_A])
                if(key[ALLEGRO_KEY_D])
                if(key[ALLEGRO_KEY_ESCAPE])*/
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= ~KEY_SEEN; //&= faz a operação AND e ~faz um NOT, O resultado remove KEY_SEEN, mas mantém se KEY_DOWN.
                quadro = 1;
            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_DOWN; //faz operação OU bit a bit, então ambos estão ativos (vista e pressionada)
                switch(event.keyboard.keycode){
                    case ALLEGRO_KEY_ESCAPE:
                        switch(tela){
                            case MENU:
                                sair = 1;
                            break;
                            case CONFIG:
                                tela = MENU;
                            break;
                            case JOGO:
                                tela = CONFIG;
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
                        if(mouse_no_botao(font_base, "Iniciar", 450, Y_SCREEN/2, event.mouse.x, event.mouse.y))
                            tela = JOGO;
                        if(mouse_no_botao(font_base, "Configurações", ((450+830)/2)+8, Y_SCREEN/2, event.mouse.x, event.mouse.y))
                            tela = CONFIG;
                        if(mouse_no_botao(font_base, "Sair", 830, Y_SCREEN/2, event.mouse.x, event.mouse.y))
                            sair = 1;
                    break;
                    case CONFIG:
                        if(mouse_no_botao(font_base, "Voltar", X_SCREEN/2, 500, event.mouse.x, event.mouse.y))
                            tela = MENU;
                    break;
                break;
                }
                
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                sair = 1;
                break;
        }
        if(sair) break; //sai do loop se clicar para fechar ou apertar esq
        if(quadro && al_is_event_queue_empty(fila)){
            switch(tela){
                case MENU:
                    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_text(font_base, al_map_rgb(0, 0, 0), 450, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Iniciar");
                    al_draw_text(font_base, al_map_rgb(0, 0, 0), ((450+830)/2)+8, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Configurações");
                    al_draw_text(font_base, al_map_rgb(0, 0, 0), 830, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Sair");
                    al_flip_display();
                    quadro = 0;
                break;

                case CONFIG:
                    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, 500, ALLEGRO_ALIGN_CENTER, "VOLTAR");
                    al_flip_display();
                    quadro = 0;
                break;
                case JOGO:
                    al_clear_to_color(al_map_rgb(0, 0, 0));
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
    al_destroy_bitmap(cursor);
    al_destroy_event_queue(fila);
    return 0;
}