#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																						//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																				    //Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																			//Biblioteca de figuras básicas
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "utils.c"
#include "menu.c"
#include "tiro.c"

#define FPS 60.0

#define KEY_SEEN 1 //A tecla foi detectada pelo menos uma vez.
#define KEY_DOWN 2 //A tecla está mantida pressionada

#define MAX_OBSTACULOS 24

#define LARGURA_PERSONAGEM 67
#define ALTURA_PERSONAGEM 88

#define MENU 0
#define CONFIG 1
#define JOGO 2
#define VIDEO 3
#define AUDIO 4
#define CONTROLE 5
#define PAUSE 6
#define LOADING 7
#define MORTE 8



int main(){
    srand(time(NULL));
    init_basico();
    
    int X_SCREEN, Y_SCREEN;
    struct tela t;
    struct fundo fundo1, fundo2, fundo3;
    ALLEGRO_DISPLAY *display = NULL;
    display = configura_display(display, 0, 0);
    t = dimensoes();
    X_SCREEN = t.X_SCREEN;
    Y_SCREEN = t.Y_SCREEN;

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    verifica_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
    verifica_init(fila, "fila");
    
    ALLEGRO_FONT *font_base = al_load_ttf_font("fontes/Pixellari.ttf", 30, 0);
    verifica_init(font_base, "fonte minha");

    ALLEGRO_BITMAP *fundo_menu = al_load_bitmap("usaveis/orig.png");
    verifica_init(fundo_menu, "usaveis/orig.png");

    ALLEGRO_BITMAP *check = al_load_bitmap("usaveis/check.png");
    verifica_init(check, "usaveis/check.png");

    ALLEGRO_BITMAP *fundo0 = al_load_bitmap("usaveis/1.png");
    verifica_init(fundo0, "usaveis/robo_bg.png");

    fundo1.bitmap = al_load_bitmap("usaveis/2.png");
    verifica_init(fundo1.bitmap, "usaveis/2.png");

    fundo2.bitmap = al_load_bitmap("usaveis/4.png");
    verifica_init(fundo2.bitmap, "usaveis/4.png");

    fundo3.bitmap = al_load_bitmap("usaveis/6.png");
    verifica_init(fundo3.bitmap, "usaveis/6.png");

    ALLEGRO_BITMAP *predio = al_load_bitmap("usaveis/predio.png");
    verifica_init(predio, "usaveis/predio.png");

    ALLEGRO_BITMAP *sprite_sheet = al_load_bitmap("usaveis/sprite3.png");
    verifica_init(sprite_sheet, "usaveis/sprite3.png");

    ALLEGRO_BITMAP *sprite_inimigo1 = al_load_bitmap("usaveis/inimigo1.png");
    verifica_init(sprite_sheet, "usaveis/inimigo1.png");

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
    memset(&personagem, 0, sizeof(personagem));
    personagem.x = X_SCREEN/2;
    personagem.y = Y_SCREEN/2;
    personagem.largura = LARGURA_PERSONAGEM;
    personagem.altura = ALTURA_PERSONAGEM;
    personagem.chao = 1;
    personagem.velocidade_y = 0;
    personagem.atirando = 0;
    personagem.vida = 3;
    int prox_x, prox_y;
    struct arma *gun;
    gun = inicia_arma();
    //struct bala *bullet_aux;

    struct obstacle estruturas[MAX_OBSTACULOS];
    estruturas[0].x1 = X_SCREEN/2 -100;
    estruturas[0].y1 = Y_SCREEN*0.7;
    estruturas[0].x2 = X_SCREEN/2 +100;
    estruturas[0].y2 = Y_SCREEN;
    estruturas[0].inimigo = 0;
    estruturas[0].enemy = NULL;
    gera_estruturas(estruturas, MAX_OBSTACULOS, Y_SCREEN);

    int scroll_X1, scroll_X2, scroll_X3, scroll_X4;
    scroll_X1 = scroll_X2 = scroll_X3 = scroll_X4 = 0;
    unsigned char quadro=0, sair=0;
    unsigned int tela = MENU; //começa no menu
    unsigned int resolucao = 1;
    unsigned int sprite = 1;
    int distancia_andada = 0;
    int pode_andar_x, pode_andar_y, altura_colide;
    int obs_tela1, obs_tela2;
    bool tela_cheia = 1, aplicar = 0;
    double start_load, delta=1, velocidade = 400, gravidade = 1800, pulo = 700, velocidade_geral;
    double start_delta = al_get_time();

    unsigned char key[ALLEGRO_KEY_MAX]; //um indice do vetor para cada tecla, com máximo para todos as keys do Allegro
    memset(key, 0, sizeof(key)); //coloca 0 em todo o vetor

    while(1){
        al_wait_for_event(fila, &event);
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                if(tela ==  JOGO){
                    personagem.abaixado = 0;
                    personagem.altura = ALTURA_PERSONAGEM;
                    personagem.direcao = 0;

                    if(key[ALLEGRO_KEY_W])
                            personagem.angulo = 270; //angulos invertidos da nossa visão tradicional
                    if(key[ALLEGRO_KEY_S])
                            personagem.angulo = 90;
                    if(key[ALLEGRO_KEY_A]){
                        personagem.direcao -= 1;
                        personagem.lado = personagem.direcao;
                        personagem.angulo = 180;
                        if(key[ALLEGRO_KEY_W])
                            personagem.angulo = 225;
                        if(key[ALLEGRO_KEY_S])
                            personagem.angulo = 135;
                    }
                    if(key[ALLEGRO_KEY_D]){
                        personagem.direcao += 1;
                        personagem.lado = personagem.direcao;
                        personagem.angulo = 0;
                        if(key[ALLEGRO_KEY_W])
                            personagem.angulo = 315;
                        if(key[ALLEGRO_KEY_S])
                            personagem.angulo = 45;
                    }
                    if(key[ALLEGRO_KEY_LCTRL]){
                        personagem.abaixado = 1;
                        personagem.altura = 70;
                    }
                    if(key[ALLEGRO_KEY_SPACE] && personagem.chao){
                        personagem.velocidade_y = -pulo;
                        personagem.chao = 0;
                    }


                    velocidade_geral = velocidade * delta;
                    if(personagem.abaixado) velocidade_geral =  velocidade_geral / 2.0;
                    prox_x = personagem.x + personagem.direcao * velocidade_geral;
                    prox_y =  personagem.y + personagem.velocidade_y * delta;
                    struct obstacle temp;
                    pode_andar_x = pode_andar_y = 1;
                    for(int i=0;i<MAX_OBSTACULOS;i++){
                        obs_tela1 = estruturas[i].x1 - distancia_andada; //valor convertido posição na tela
                        obs_tela2 = estruturas[i].x2 - distancia_andada;
                        if(obs_tela2 >= 0 && obs_tela1 <= X_SCREEN){
                            temp.x1 = obs_tela1;
                            temp.x2 = obs_tela2;
                            temp.y1 = estruturas[i].y1;
                            temp.y2 = estruturas[i].y2;
                            if(colide_x(prox_x, personagem.y, LARGURA_PERSONAGEM, ALTURA_PERSONAGEM, temp)){
                                pode_andar_x = 0;
                            }
                            if(colide_y(personagem.x, prox_y, LARGURA_PERSONAGEM, ALTURA_PERSONAGEM, temp)){
                                pode_andar_y = 0;
                                altura_colide = temp.y1;
                            }
                        }
                    }
                    if(pode_andar_x){
                        personagem.x = prox_x;
                        distancia_andada += personagem.direcao * velocidade_geral;
                        //printf("Distancia: %d\n", distancia_andada);
                        fundo3.scroll_x -= personagem.direcao * velocidade_geral*1.2;
                        fundo2.scroll_x -= personagem.direcao * velocidade_geral/2;
                        fundo1.scroll_x -= personagem.direcao * velocidade_geral/4;
                    }
                    if(!pode_andar_y){
                        if(personagem.velocidade_y > 0){
                            personagem.chao = 1;
                            personagem.velocidade_y = 0;
                            personagem.y = altura_colide;
                        }
                    }
                    else{
                        personagem.chao = 0;
                        personagem.y = prox_y;
                    }
                    
                    if(!personagem.chao) personagem.velocidade_y += gravidade * delta; //para competir com o pulo, vai acumulando gravidade
                    personagem.x = X_SCREEN/2-LARGURA_PERSONAGEM;
                    if(personagem.x <= 0)personagem.x = 0;
                    //personagem.y += personagem.velocidade_y * delta; 
                    if(personagem.y >= Y_SCREEN) personagem.vida = 0;
                    if(abs(scroll_X1) >= X_SCREEN) scroll_X1 = 0;
                }
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                        key[i] &= ~KEY_SEEN; //&= faz a operação AND e ~faz um NOT, O resultado remove KEY_SEEN, mas mantém se KEY_DOWN.
                    quadro = 1;
                    double now_delta = al_get_time();
                    delta = now_delta - start_delta; //tempo em segundos de um quadro a outro IRL, independe do FPS
                    start_delta = now_delta;
    //printf("FPS: %f\n", 1.0/delta);
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
                                tela = PAUSE;
                            break;
                            case PAUSE:
                                tela = JOGO;
                            break;
                            case LOADING:
                                tela = MENU;
                            break;
                            case MORTE:
                                tela = MENU;
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
                    case JOGO:
                        personagem.atirando = 1;
                    break;
                    case PAUSE:
                        if(mouse_no_botao(font_base, "Continuar", X_SCREEN*0.4, Y_SCREEN/2, event.mouse.x, event.mouse.y))
                            tela = JOGO;
                        if(mouse_no_botao(font_base, "Menu Principal", X_SCREEN*0.6, Y_SCREEN/2, event.mouse.x, event.mouse.y)){
                            personagem = reseta_game(personagem, estruturas, &distancia_andada, MAX_OBSTACULOS, X_SCREEN, Y_SCREEN);
                            tela = MENU;
                        }
                    break;
                }      
            break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if(tela == JOGO) personagem.atirando = 0;
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
            al_clear_to_color(al_map_rgb(0, 0, 0));
            switch(tela){
                case MENU:
                    desenha_menu(fundo_menu, font_base, X_SCREEN, Y_SCREEN);
                break;
                case CONFIG:
                    desenha_config(fundo_menu, font_base, X_SCREEN, Y_SCREEN);
                break;
                case VIDEO:
                    desenha_video(fundo_menu, check, font_base, X_SCREEN, Y_SCREEN, resolucao, tela_cheia);
                break;
                case AUDIO:
                    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
                break;
                case CONTROLE:
                    al_draw_scaled_bitmap(fundo_menu, 0, 0, al_get_bitmap_width(fundo_menu), al_get_bitmap_height(fundo_menu), 0, 0, X_SCREEN, Y_SCREEN, 0);
                break;
                case JOGO:
                    desenha_jogo(&personagem, gun, estruturas, fundo1, fundo2, fundo3, fundo0, sprite_sheet, sprite_inimigo1, sprite, 
                        distancia_andada, velocidade, delta, MAX_OBSTACULOS, X_SCREEN, Y_SCREEN); //passei por referência para decrementar a vida.
                    //al_draw_filled_rectangle(personagem.x, personagem.y, personagem.x+personagem.largura, personagem.y-personagem.altura, al_map_rgb(255, 0, 0)); //marca x, y do boneco
                    sprite++;
                    if(sprite >= 20) sprite = 0;
                    gun->cooldown -= delta;
                    if(personagem.atirando && gun->cooldown <= 0){
                        atirou(personagem.x+distancia_andada, personagem.y, personagem.angulo, 0.2, gun); //somo a distancia para a coordenanda da bala ficar certa
                    }
                    atualiza_lista(gun, estruturas, velocidade*delta*3, distancia_andada, MAX_OBSTACULOS, X_SCREEN, Y_SCREEN);
                    //printf("VIDA krl: %d\n", personagem.vida);
                    if(personagem.vida <= 0){
                        personagem = reseta_game(personagem, estruturas, &distancia_andada, MAX_OBSTACULOS, X_SCREEN, Y_SCREEN);
                        distancia_andada = 0;
                        tela = MORTE;
                    }
                break;
                case LOADING:
                    double now_load = al_get_time();
                    if(now_load - start_load >= 1.5)
                        tela = JOGO;
                    al_draw_scaled_bitmap(fundo0, 0, 0, al_get_bitmap_width(fundo0), al_get_bitmap_height(fundo0), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Carregando...");
                break;
                case PAUSE:
                    al_draw_scaled_bitmap(fundo0, 0, 0, al_get_bitmap_width(fundo0), al_get_bitmap_height(fundo0), 0, 0, X_SCREEN, Y_SCREEN, 0);
                    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN*0.4, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Continuar");
                    al_draw_text(font_base, al_map_rgb(0, 0, 0), X_SCREEN*0.6, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Menu Principal");
                break;
                case MORTE:
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_text(font_base, al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN*0.45, ALLEGRO_ALIGN_CENTER, "Skill Issue?");
                    al_draw_text(font_base, al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN*0.55, ALLEGRO_ALIGN_CENTER, "Pressione ESCAPE para voltar ao MENU");
                break;
            }
            al_flip_display();
            quadro = 0;
            //al_clear_to_color(al_map_rgb(0, 0, 0));
            
        }
    }

    destroi_arma(gun);
    al_destroy_timer(timer);
    al_destroy_mouse_cursor(mouse);
    al_destroy_display(display);
    al_destroy_font(font_base);
    al_destroy_bitmap(fundo_menu);
    al_destroy_bitmap(check);
    al_destroy_bitmap(sprite_sheet);
    al_destroy_bitmap(sprite_inimigo1);
    al_destroy_bitmap(fundo0);
    al_destroy_bitmap(fundo1.bitmap);
    al_destroy_bitmap(fundo2.bitmap);
    al_destroy_bitmap(fundo3.bitmap);
    al_destroy_bitmap(predio);
    al_destroy_bitmap(cursor);
    al_destroy_event_queue(fila);
    return 0;
}