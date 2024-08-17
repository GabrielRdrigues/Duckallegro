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
    ALLEGRO_DISPLAY*      disp = al_create_display(600, 400);
    ALLEGRO_TIMER*       timer = al_create_timer(1.0/140.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT*         font = al_load_font("dragon.ttf", 10, 0);
    ALLEGRO_BITMAP* image1 = al_load_bitmap("duckp2.png");
    ALLEGRO_BITMAP* image2 = al_load_bitmap("duckp3.png");
    ALLEGRO_BITMAP* image3 = al_load_bitmap("background.png");
    ALLEGRO_BITMAP* image4 = al_load_bitmap("gameover.png");
    ALLEGRO_SAMPLE* quack = al_load_sample("quack.wav");
    ALLEGRO_SAMPLE* fail = al_load_sample("fail.wav");
    ALLEGRO_EVENT event;
// ------------------------------------------------------------------------------------


    al_set_window_title(disp,"Aimllegro - GOTY");


// -------------------- Registrando eventos --------------------------------------------
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
// ------------------------------------------------------------------------------------

// ------------------ Variaveís primitivas ----------------------------------------
    int highscore;
    bool redraw = true;
    int x = 1;
    int y = 1;
    int seg = 0;
    int pontos = 0;
    int n = 3;
    srand(time(NULL));

    circulo C1;
    C1.raio = 10;

    circulo* Cr = malloc(100*sizeof(circulo));
    circulo* duckalive = malloc(100*sizeof(circulo));
// ------------------------------------------------------------------------------------



    Init_Highscore(&highscore);



    al_start_timer(timer);

/* -----------------------------------LOOP PRINCIPAL -------------------------------------- ------------------------
----------------------------------------------------------------------------------------------------------------*/
    while(x==1){
        while (y == 1){
            al_wait_for_event(queue, &event);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN){
                y=0;
            }
        }

        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
            seg++;
            al_draw_textf(font , al_map_rgb(255 , 255 , 0) , 1 , 20 , ALLEGRO_ALIGN_LEFT , "HIGHSCORE: %d" , highscore);

        }else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            C1.x = event.mouse.x;
            C1.y = event.mouse.y;
            for(int i = 0; i < n; i++){
                if(circulos_colidem(C1, Cr[i])){
                    pontos = pontos +100;
                    Cr[i].r = 0;

                    //reseta a tela
                    al_draw_bitmap(image3, 0, 0, 0);

                    //reescreve o highscore
                    al_draw_textf(font , al_map_rgb(255 , 255 , 0) , 1 , 20 , ALLEGRO_ALIGN_LEFT , "HIGHSCORE: %d" , highscore);

                    //reescreve o score atualizado
                    al_draw_textf(font , al_map_rgb(255 , 255 , 0) , 1 , 1 , ALLEGRO_ALIGN_LEFT , "SCORE: %d" , pontos);

                    //desenha o png do pato atingido
                    al_draw_bitmap(image2, Cr[i].x-15, Cr[i].y-15, 0);

                    //toca o quack
                    al_play_sample(quack, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                    duckalive[i].r = 0;

                    for (int j=0; j<n; j++){
                        if (duckalive[j].r != 0)
                            al_draw_bitmap(image1, Cr[j].x-14, Cr[j].y-15, 0);
                    }

                }
            }

        }else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if(redraw && al_is_event_queue_empty(queue)){

            printf("%d ", seg);

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

                if (seg == 1400){
                    n=4;
                }
                if (seg == 2800){
                    n=5;
                }
                printf("(%d)", n);

                for (int i=0; i<n; i++){
                    if (x==0){
                        break;
                    }
                    Cr[i].x = rand()%600;
                    Cr[i].y = rand()%400;
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

    LerHighscore(pontos);

    free(Cr);
    free(duckalive);

    sleep(5);

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
