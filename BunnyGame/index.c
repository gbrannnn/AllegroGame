// Must to stuff
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

// Types
#include "player.h";
#include "wall.h";
#include "npc.h";
#include "button.h";

// Functions
#include "playerFunctions.h";


const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int binary_quest[] = {0,0,1,1};
int countCheck = 0;

char correct[200] = "PARABENS ACERTOU!!! Voce sabe que 3 em binario e 0011, para";
char correct_2[200] = "chegar nesse resultado e necessario saber que dividir o 3 por 2,";
char correct_3[200] = " e ir guardando os valores que sobram e junta los formara 0011";

char incorrect[200] = "Resposta errada, tente novamente";

int main() {
    // ======================================================
    // ALLEGRO INIT
    // ======================================================
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();


    // ======================================================
    // EVENTS
    // ======================================================
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    // ======================================================
    // SPRITES
    // ======================================================
    ALLEGRO_BITMAP* playerSprite = al_load_bitmap("..\\assets\\player.png");
    ALLEGRO_BITMAP* npc_one_sprite = al_load_bitmap("..\\assets\\npc_one_sprite.png");
    ALLEGRO_BITMAP* wallSprite = al_load_bitmap("..\\assets\\tree.png");
    ALLEGRO_BITMAP* textBox = al_load_bitmap("..\\assets\\boxT.png");
    ALLEGRO_BITMAP* button_0 = al_load_bitmap("..\\assets\\button_0_rs.png");
    ALLEGRO_BITMAP* button_1 = al_load_bitmap("..\\assets\\button_1_rs.png");
    ALLEGRO_BITMAP* button_confirm = al_load_bitmap("..\\assets\\button_confirm_rs.png");
    ALLEGRO_BITMAP* button_return = al_load_bitmap("..\\assets\\button_return_rs.png");


    // ======================================================
    // GENERAL ASSETS
    // ======================================================
    ALLEGRO_FONT* font = al_load_font("..\\font.ttf", 20, 0);

    

    // ======================================================
    // REGISTRING EVENTS
    // ======================================================
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    

    // ======================================================
    // INITIALIZING OBJECTS
    // ======================================================
    //                X    Y     DIR VEL  ISCOLI  CANMOVE   INSIGNAAS
    PLAYER player = { 200, 200,  0,  7.0, false,  true,     {0}};

    WALL walls[38] = {
        // TOP 16 WALLS
        {"WALL", 64 * 0,   0, 32, 48},
        {"WALL", 64 * 1,   0, 32, 48},
        {"WALL", 64 * 2,   0, 32, 48},
        {"WALL", 64 * 3,   0, 32, 48},
        {"WALL", 64 * 4,   0, 32, 48},
        {"WALL", 64 * 5,   0, 32, 48},
        {"WALL", 64 * 6,   0, 32, 48},
        {"WALL", 64 * 7,   0, 32, 48},
        {"WALL", 64 * 8,   0, 32, 48},
        {"WALL", 64 * 9,   0, 32, 48},
        {"WALL", 64 * 10,  0, 32, 48},
        {"WALL", 64 * 11,  0, 32, 48},
        {"WALL", 64 * 12,  0, 32, 48},
        {"WALL", 64 * 13,  0, 32, 48},
        {"WALL", 64 * 14,  0, 32, 48},
        {"WALL", 64 * 15,  0, 32, 48},
        
        // TOP RIGHT
        {"WALL", 64 * 15, 64 * 0, 32, 48},
        {"WALL", 64 * 15, 64 * 1, 32, 48},
        {"WALL", 64 * 15, 64 * 2, 32, 48},
        {"WALL", 64 * 15, 64 * 3, 32, 48},
        {"WALL", 64 * 15, 64 * 4, 32, 48},
        {"WALL", 64 * 15, 64 * 5, 32, 48},
        {"WALL", 64 * 15, 64 * 6, 32, 48},
        {"WALL", 64 * 15, 64 * 7, 32, 48},
        {"WALL", 64 * 15, 64 * 8, 32, 48},
        {"WALL", 64 * 15, 64 * 9, 32, 48},
        {"WALL", 64 * 15, 64 * 10, 32, 48},

        // TOP LEFT
        {"WALL", 0, 64 * 0, 32, 48},
        {"WALL", 0, 64 * 1, 32, 48},
        {"WALL", 0, 64 * 2, 32, 48},
        {"WALL", 0, 64 * 3, 32, 48},
        {"WALL", 0, 64 * 4, 32, 48},
        {"WALL", 0, 64 * 5, 32, 48},
        {"WALL", 0, 64 * 6, 32, 48},
        {"WALL", 0, 64 * 7, 32, 48},
        {"WALL", 0, 64 * 8, 32, 48},
        {"WALL", 0, 64 * 9, 32, 48},
        {"WALL", 0, 64 * 10, 32, 48},
        
    };
   
    WALL bottomWals[16] = {
        { "WALL", 64 *0,  64 * 11, 32,48 },
        { "WALL", 64 * 1,  64 * 11, 32, 48 },
        { "WALL", 64 * 2,  64 * 11, 32, 48 },
        { "WALL", 64 * 3,  64 * 11, 32, 48 },
        { "WALL", 64 * 4,  64 * 11, 32, 48 },
        { "WALL", 64 * 5,  64 * 11, 32, 48 },
        { "WALL", 64 * 6,  64 * 11, 32, 48 },
        { "WALL", 64 * 7,  64 * 11, 32, 48 },
        { "WALL", 64 * 8,  64 * 11, 32, 48 },
        { "WALL", 64 * 9,  64 * 11, 32, 48 },
        { "WALL", 64 * 10, 64 * 11, 32, 48 },
        { "WALL", 64 * 11, 64 * 11, 32, 48 },
        { "WALL", 64 * 12, 64 * 11, 32, 48 },
        { "WALL", 64 * 13, 64 * 11, 32, 48 },
        { "WALL", 64 * 14, 64 * 11, 32, 48 },
        { "WALL", 64 * 15, 64 * 11, 32, 48 },

    };
    BUTTON numbersButtons[4] = {
        {"BUTTON", 500, 400, 35, 35, 0, -1},
        {"BUTTON", 500 * 1.1, 400, 35, 35, 0, -1},
        {"BUTTON", 500 * 1.2, 400, 35, 35, 0, -1},
        {"BUTTON", 500 * 1.3, 400, 35, 35, 0, -1}
    };
    BUTTON checkButtons[1] = {
        {"BUTTON", 500 * 1.15, 400 * 1.25, 35, 35, 0, -1}
    };
    NPC npc_collisions[1] = {
        { "NPC", 200, 400, 16, 16, "Ola mero mortal, tenho um desafio para voce!!", false }
    };


    // ======================================================
    // MAIN LOOP
    // ======================================================
    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break;
        }



        // ======================================================
        // PLAYER INPUTS
        // ======================================================
        movePlayer(&player, event);




        
        // ======================================================
        // RENDERIN
        // ======================================================

        al_clear_to_color(al_map_rgb(87, 152, 105, 255));


        // Drawing numbers buttons
        for (int i = 0; i < 4; i++) {
            if (numbersButtons[i].VALUE < 0) {
                al_draw_bitmap(
                    button_0,
                    numbersButtons[i].POSX,
                    numbersButtons[i].POSY,
                    0
                );
            }
            else if (numbersButtons[i].VALUE > 0) {
                al_draw_bitmap(
                    button_1,
                    numbersButtons[i].POSX,
                    numbersButtons[i].POSY,
                    0
                );
            }
            else {
                al_draw_bitmap( 
                    button_0,
                    numbersButtons[i].POSX,
                    numbersButtons[i].POSY,
                    0
                );
            }
            checkCollisionWithButton(&player, &numbersButtons[i]);
            if (numbersButtons[i].VALUE != binary_quest[i]) {
                countCheck = 0;
            }
            else {
                countCheck += 1;
            }
        }


        //Dwaing check buttons
        for (int i = 0; i < 1; i++) {
            al_draw_bitmap(
                button_confirm,
                checkButtons[i].POSX,
                checkButtons[i].POSY,
                0
            ); checkCollisionWithButton(&player, &checkButtons[i]);
        }

        if (checkButtons[0].VALUE > 0) {
            if (countCheck >= 4) {
                al_draw_scaled_bitmap(textBox, 0, 0, 144, 64, npc_collisions[0].POSX, npc_collisions[0].POSY - 144, 144 * 5, 64 * 2, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), npc_collisions[0].POSX + 25, npc_collisions[0].POSY - 130, 0, correct);
                al_draw_text(font, al_map_rgb(255, 255, 255), npc_collisions[0].POSX + 25, npc_collisions[0].POSY - 100, 0, correct_2);
                al_draw_text(font, al_map_rgb(255, 255, 255), npc_collisions[0].POSX + 25, npc_collisions[0].POSY - 70, 0, correct_3);
            }
            else {
                al_draw_scaled_bitmap(textBox, 0, 0, 144, 64, npc_collisions[0].POSX, npc_collisions[0].POSY - 144, 144 * 3, 64 * 2, 0);
                al_draw_text(font, al_map_rgb(255, 255, 255), npc_collisions[0].POSX + 15, npc_collisions[0].POSY - 130, 0, incorrect);
            }
        }
         
        // Drawing left/top/rigth wall
        for (int i = 0; i < 38; i++) {
            al_draw_scaled_bitmap(
                wallSprite,
                0,
                0,
                32,
                48,
                walls[i].POSX,
                walls[i].POSY,
                walls[i].WIDTH * 2,
                walls[i].HEIGH * 2,
                0
            );
            checkCollisionWithWalls(&player, &walls[i]);
        }

        // Sprites
        al_draw_scaled_bitmap(playerSprite, 0, 48 * player.PLAYERDIR, 48, 48, player.POSX, player.POSY, 48 * 2, 48 * 2, 0);
        al_draw_scaled_bitmap(npc_one_sprite, 0, 0, 16, 16, 200, 400, 16 * 2, 16 * 2, 0);

        
        // Drawing bottom walls
        for (int i = 0; i < 16 ; i++) {
            al_draw_scaled_bitmap(
                wallSprite, 
                0, 
                0, 
                32, 
                48, 
                bottomWals[i].POSX, 
                bottomWals[i].POSY, 
                bottomWals[i].WIDTH * 2,
                bottomWals[i].HEIGH * 2,
                0
            );
            checkCollisionWithWalls(&player, &bottomWals[i]);
        }

        for (int i = 0; i < 1; i++) {
            checkCollisionWithNpc(&player, &npc_collisions[i], textBox, font, drawTextBoxNpc);
        }



        al_flip_display();
    }

    
    // ======================================================
    // DESTROYING OBJECTS
    // ======================================================
    
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    
    al_destroy_bitmap(wallSprite);
    al_destroy_bitmap(playerSprite);
    al_destroy_bitmap(button_0);
    al_destroy_bitmap(button_1);
    al_destroy_bitmap(button_return);
    al_destroy_bitmap(button_confirm);

    return 0;
}