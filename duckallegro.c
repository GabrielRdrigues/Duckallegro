#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "arquivo.h"
#include "circulo.h"
#include "stack.h"



int main(){


//--------------- Inicialização addons ALLEGRO -------------------------------------
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(15);
// ------------------------------------------------------------------------------------


    
// ----------------------- Carregando recursos do ALLEGRO -----------------------------
    ALLEGRO_DISPLAY*      disp = al_create_display(1920, 1080);
    ALLEGRO_TIMER*       timer = al_create_timer(1.0/140.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT*         font = al_load_font("dragon.ttf", 10, 0);
    ALLEGRO_FONT*         font2 = al_load_font("dragon.ttf", 30, 0);
    ALLEGRO_BITMAP* image1 = al_load_bitmap("duckp2.png");
    ALLEGRO_BITMAP* image2 = al_load_bitmap("duckp3.png");
    ALLEGRO_BITMAP* image3 = al_load_bitmap("background.png");
    ALLEGRO_BITMAP* image4 = al_load_bitmap("gameover.png");
    ALLEGRO_SAMPLE* quack = al_load_sample("quack.wav");
    ALLEGRO_SAMPLE* fail = al_load_sample("fail.wav");
    ALLEGRO_EVENT event;
// ------------------------------------------------------------------------------------

    // Colocando o título do jogo
    al_set_window_title(disp,"Duckallegro - GOTY");


// -------------------- Registrando eventos --------------------------------------------
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
// ------------------------------------------------------------------------------------

// ------------------ Variaveís primitivas ----------------------------------------
    int highscore; // Highscore
    bool redraw = true; // Rdesenhar
    int x = 1;
    int y = 1;
    int seg = 0; // Timer
    int pontos = 0; // Quantidade de pontos
    int n = 3; // Quantidade de patos na tela
    int aux; // Variável auxiliar
    int por; // Variável auxiliar
    double tempo = 0; // Tempo da função al_get_time
    srand(time(NULL));

    circulo C1; // Mouse
    C1.raio = 10; // Hitbox do Mouse

    Stack poderes;
    init_stack(&poderes);

    circulo* Cr = malloc(100*sizeof(circulo)); // Vetor de circulos (hitbox do pato)
    circulo* duckalive = malloc(100*sizeof(circulo)); // Vetor de patos vivos, que são repŕesentados por círculos.
// ------------------------------------------------------------------------------------

    
    // Lendo do Arquivo highscore.txt o maior score do usuário
    Init_Highscore(&highscore);
    


    al_start_timer(timer);

/* -----------------------------------LOOP PRINCIPAL -------------------------------------- ------------------------
----------------------------------------------------------------------------------------------------------------*/
    while(x==1){
        while (y == 1){ // Espera antes de começar o jogo, aperte qualquer tecla para começar
            al_wait_for_event(queue, &event);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN){
                y=0;
            }
        }

        al_wait_for_event(queue, &event); // Esperando um evento

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            seg++; // Aumenta o timer
            al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 20, ALLEGRO_ALIGN_LEFT, "HIGHSCORE: %d", highscore); // Escreve o highscore
} else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) { // Verifica se houve clique do mouse
    C1.x = event.mouse.x;
    C1.y = event.mouse.y;
    for(int i = 0; i < n; i++){
                if(circulos_colidem(C1, Cr[i])){
                    if((aux==0 || aux==1 || aux ==2 ) && (al_get_time() - tempo <= 560)){
                        if(aux==0)
                            pontos+= 2000;
                        else if(aux==1)
                            pontos+= 5000;
                        else
                            pontos+=10000;
                    }else
                        pontos+=100;
                    
                    Cr[i].r = 0;
                    // Reseta a tela
                    al_draw_bitmap(image3, 0, 0, 0);
                    // Reescreve o highscore
                    al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 20, ALLEGRO_ALIGN_LEFT, "HIGHSCORE: %d", highscore);
                    // Reescreve o score atualizado
                    al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, ALLEGRO_ALIGN_LEFT, "SCORE: %d", pontos);
                    // Desenha o PNG do pato atingido
                    al_draw_bitmap(image2, Cr[i].x - 15, Cr[i].y - 15, 0);
                    // Toca o quack
                    al_play_sample(quack, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    duckalive[i].r = 0;
                    for (int j = 0; j < n; j++) {
                        if (duckalive[j].r != 0) {
                            al_draw_bitmap(image1, Cr[j].x - 14, Cr[j].y - 15, 0);
                        }
                    }
        }
    }
} else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
    if (!is_empty(&poderes)) {
        if (event.keyboard.keycode == ALLEGRO_KEY_1) {
            aux = top(&poderes);
            pop(&poderes);
            tempo = al_get_time();
        }
    }
} else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    break;
}

if(redraw && al_is_event_queue_empty(queue)){
            if ((seg)%280 == 0 || seg == 4){
                al_draw_bitmap(image3, 0, 0, 0);
                for (int i=0; i<n; i++){
                    if (seg > 140){
                        if (Cr[i].r != 0){
                            al_draw_bitmap(image4, 0, 0, 0);
                            al_play_sample(fail, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            x = 0;
                            break;
                        }
                    }
                }
                if (seg == 560){
                        por = rand()%3; // O poder é obtido de forma aleatório
                        push(&poderes, por); // Dando push do poder na pilha
                        if(por==0)
                            al_draw_textf(font2, al_map_rgb(255, 0, 0), 1, 50, ALLEGRO_ALIGN_LEFT,"2X + PONTOS"); // Avisando ao usuário do poder
                        if(por==1)
                            al_draw_textf(font2, al_map_rgb(255, 0, 0), 1, 50, ALLEGRO_ALIGN_LEFT,"5X + PONTOS"); // Avisando ao usuário do poder
                        if(por==2)
                            al_draw_textf(font2, al_map_rgb(255, 0,0), 1, 50, ALLEGRO_ALIGN_LEFT,"10X + PONTOS"); // Avisando ao usuário do poder
                        n=4; // Aumentando o número de patos na tela
                }
                if (seg == 1120){
                        por = rand()%3; // O poder é obtido de forma aleatória
                        push(&poderes, por); // Dando push do poder na pilha
                        if(por==0)
                            al_draw_textf(font2, al_map_rgb(255, 0, 0), 1, 50, ALLEGRO_ALIGN_LEFT,"2X + PONTOS"); // Avisando ao usuário do poder
                        if(por==1)
                            al_draw_textf(font2, al_map_rgb(255, 0, 0), 1, 50, ALLEGRO_ALIGN_LEFT,"5X + PONTOS"); // Avisando ao usuário do poder
                        if(por==2)
                            al_draw_textf(font2, al_map_rgb(255, 0,0), 1, 50, ALLEGRO_ALIGN_LEFT,"10X + PONTOS"); // Avisando ao usuário do poder
                        n=5; // Aumentando o número de patos na tela
                }
                for (int i=0; i<n; i++){
                    if (x==0){
                        break;
                    }
                    Cr[i].x = rand()%500 + 50;
                    Cr[i].y = rand()%300 + 50;
                    Cr[i].raio = 20;
                    Cr[i].r = 255;
                    Cr[i].g = 255;
                    Cr[i].b = 255;
                    al_draw_filled_circle(Cr[i].x, Cr[i].y, Cr[i].raio, al_map_rgba_f(0, 0, 0, 0));
                    al_draw_bitmap(image1, Cr[i].x-14, Cr[i].y-15, 0);
                    al_draw_textf(font , al_map_rgb(255 , 255 , 0) , 1 , 1 , ALLEGRO_ALIGN_LEFT , "SCORE: %d" , pontos);
                    duckalive[i] = Cr[i];
                }
            }
            al_flip_display();
            redraw = false;
        }
    }
/* ------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------FIM DO LOOP PRINCIPAL-------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------*/

    // Verificando se o score da partida atual é maior que seu highscore armazenado no arquivo, se for, será seu novo highscore.
    LerHighscore(pontos); 

    free(Cr); // Liberando a memória alocada.
    free(duckalive); // Liberando a memória alocada.

    sleep(5);

    // Destruindo componentes do Allegro
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(image1);
    al_destroy_bitmap(image2);
    al_destroy_bitmap(image3);
    al_destroy_bitmap(image4);
    al_destroy_sample(quack);
    al_destroy_sample(fail);
    al_destroy_font(font);

}
