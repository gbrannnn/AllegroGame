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
int binary_result[4];
const int countCheck = 0;

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

    WALL walls[48] = {
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
        {"WALL", 64 * 15, 64 * 11, 32, 48},
        {"WALL", 64 * 15, 64 * 12, 32, 48},
        {"WALL", 64 * 15, 64 * 13, 32, 48},
        {"WALL", 64 * 15, 64 * 14, 32, 48},
        {"WALL", 64 * 15, 64 * 15, 32, 48},

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
        {"WALL", 0, 64 * 11, 32, 48},
        {"WALL", 0, 64 * 12, 32, 48},
        {"WALL", 0, 64 * 13, 32, 48},
        {"WALL", 0, 64 * 14, 32, 48},
        {"WALL", 0, 64 * 15, 32, 48},
    };
   
    WALL bottomWals[15] = {
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
        { "WALL", 64 * 14, 64 * 11, 32, 48 }
    };
    BUTTON numbersButtons[4] = {
        {"BUTTON", 500, 400, 35, 35, 0, -1},
        {"BUTTON", 500 * 1.1, 400, 35, 35, 0, -1},
        {"BUTTON", 500 * 1.2, 400, 35, 35, 0, -1},
        {"BUTTON", 500 * 1.3, 400, 35, 35, 0, -1}
    };
    BUTTON checkButtons[1] = {
        {"BUTTON", 500 * 1.15, 400 * 1.25, 35, 35, 0}
    };
    NPC npc_collisions[1] = {
        { "NPC", 200, 400, 16, 16, "Ola eu sou um NPC \n Esse e um teste de quebra de linhas", false }
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
        // RENDERING
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
            checkCollisionWithButton(&player, &numbersButtons[i], &binary_result[i]);
        }

        //Dwaing check buttons
        for (int i = 0; i < 1; i++) {
            al_draw_bitmap(
                button_confirm,
                checkButtons[i].POSX,
                checkButtons[i].POSY,
                0
            ); checkCollisionWithButton2(&player, &checkButtons[i], &binary_result, &binary_result, &countCheck, checkButtonResult);
        }
        

        if (countCheck == 1) {
            al_draw_text(font, al_map_rgb(255, 255, 255), 200, 200, 0, "ACERTO MISERAVEL!!");
        }

        // Drawing left/top/rigth wall
        for (int i = 0; i < 48; i++) {
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
        for (int i = 0; i < 15  ; i++) {
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
            checkCollisionWithNpc(&player, &npc_collisions[i], textBox, font, drawTextBox);
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