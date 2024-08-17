#include "circulos.h"
#include <time.h>

// Estrutura Circulo


// Função para desenhar um círculo




void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}


int main()
{
    srand(time(NULL));
    int pontos=0;
    int N=10;
    Circulo C1 = {0, 0, 5, 100, 200, 200};
    Circulo C[20];
    int highscore;
    int seg=0;
    int x=1;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_install_mouse();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(15);


    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 144.0); // Tempo que redesenha a tela
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); // Criando a fila de eventos
    ALLEGRO_DISPLAY* disp = al_create_display(800,800); // Resolução da tela
    ALLEGRO_FONT* font = al_load_font("Fonte.ttf", 50, 0);
    ALLEGRO_SAMPLE* quack = al_load_sample("quack.wav");
    ALLEGRO_SAMPLE* fail = al_load_sample("fail.wav");
    ALLEGRO_BITMAP* image1 = al_load_bitmap("duck2.bmp");
    ALLEGRO_BITMAP* image2 = al_load_bitmap("duck3.bmp");


    al_register_event_source(queue, al_get_keyboard_event_source()); // Registrando o teclado como um evento
    al_register_event_source(queue, al_get_mouse_event_source()); // Registrando o mouse como um evento
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;

    FILE* f = fopen("highscore.txt","r");
    if(fscanf(f,"%d",&highscore)==0)
        highscore=0;
    fclose(f);

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    while(x==1){
        //al_hide_mouse_cursor(disp);
        al_wait_for_event(queue, &event); // Vai ficar parado aqui até acontecer algo

        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
            seg++;
            al_draw_textf(font , al_map_rgb(255 , 255 , 0) , 1 , 60 , ALLEGRO_ALIGN_LEFT , "HIGHSCORE: %d" , highscore);
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            C1.x = event.mouse.x;
            C1.y = event.mouse.y;
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                for(int i = 0; i < N; i++){ // Verificar se clicou e colidiu
                if(circulos_colidem(C1, C[i])){
                    C[i].r = 150;
                    C[i].g = 150;
                    C[i].b = 200;
                    desenha_circulo(C[i]);
                    al_draw_bitmap(image2, C[i].x-15, C[i].y-15, 0);
                    al_draw_filled_circle(C1.x, C1.y, C1.raio, al_map_rgba_f(0, 0, 0, 0));
                    al_play_sample(quack, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    pontos = pontos +1000;
                    al_draw_filled_rectangle(1,1, 425, 50, al_map_rgb(150, 150, 200));
                    al_draw_textf(font , al_map_rgb(255 , 255 , 0) , 1 , 1 , ALLEGRO_ALIGN_LEFT , "SCORE: %d" , pontos);
                }
            }
        }
        else if((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
            break;
            }

        if(redraw && al_is_event_queue_empty(queue))
        {

             if((seg)%280 == 0 ){
                    al_clear_to_color(al_map_rgb(150, 150, 200));
                    for (int i=0; i<3; i++){
                    if (seg > 280){
                        if (C[i].r != 150){
                            al_clear_to_color(al_map_rgb(150, 150, 200));
                            al_draw_text(font, al_map_rgb(255, 255, 255), 700,500, ALLEGRO_ALIGN_RIGHT, "VOCE PERDEU");
                            al_play_sample(fail, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            x=0;
                            break;
                        }
                    }
                    C[i].x = rand()%600;
                    C[i].y = rand()%400;
                    C[i].raio = 5;
                    C[i].r = 255;
                    C[i].g = 255;
                    C[i].b = 255;
                    al_draw_filled_circle(C[i].x, C[i].y, C[i].raio, al_map_rgba_f(0, 0, 0, 0));
                    al_draw_bitmap(image1, C[i].x-14, C[i].y-15, 0);
                    al_draw_textf(font , al_map_rgb(255 , 255 , 0) , 1 , 1 , ALLEGRO_ALIGN_LEFT , "SCORE: %d" , pontos);
                    }

             }

            al_flip_display();
            redraw = false;
        }
    }


    f = fopen("highscore.txt", "r");
    if (fscanf(f, "%d", &highscore) == 1){
        if (pontos > highscore){
            fclose(f);
            f = fopen("highscore.txt", "w");
            fprintf(f,"%d", pontos);
        }
    }else {
        fclose(f);
        f = fopen("highscore.txt", "w");
        fprintf(f,"%d", pontos);
    }
    fclose(f);

    delay(5);

    al_destroy_bitmap(image2);
    al_destroy_bitmap(image1);
    al_destroy_font(font);
    al_destroy_sample(quack);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
