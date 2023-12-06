#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>



// Move Player
void movePlayer(PLAYER* player, ALLEGRO_EVENT event) {
	// MOVING RIGHT
	if (event.keyboard.keycode == ALLEGRO_KEY_D) { 
		player->PLAYERDIR = 3;
		player->POSX+=player->VELOCITY; 

	}
	
	// MOVING LEFT 
	if (event.keyboard.keycode == ALLEGRO_KEY_A) {
		player->PLAYERDIR = 2;
		player->POSX -= player->VELOCITY;

	}
	
	// MOVING UP
	if (event.keyboard.keycode == ALLEGRO_KEY_W) {
		player->PLAYERDIR = 1;
		player->POSY -= player->VELOCITY;

	}
	
	// MOVING DOWN
	if (event.keyboard.keycode == ALLEGRO_KEY_S) {
		player->PLAYERDIR = 0;
		player->POSY += player->VELOCITY;

	}
}

// Colission with Walls
void checkCollisionWithWalls(PLAYER* player, WALL* wall) {
	int pushBack = 5;

	int playerBottomRightX = player->POSX + 48;
	int playerBottomRightY = player->POSY + 48;

	int wallBottomDownX = wall->POSX + wall->WIDTH;
	int wallBottomDowny = wall->POSY + wall->HEIGH;

	float playerVel = player->VELOCITY;

	if (wall->POSX <= playerBottomRightX &&
		wallBottomDownX >= player->POSX &&
		wall->POSY <= playerBottomRightY &&
		wallBottomDowny >= player->POSY
		) {
		
		// Push player to the oppsite direction to not get stuck
		if (player->PLAYERDIR == 0) player->POSY -= pushBack;
		if (player->PLAYERDIR == 1) player->POSY += pushBack;
		if (player->PLAYERDIR == 2) player->POSX += pushBack;
		if (player->PLAYERDIR == 3) player->POSX -= pushBack; 

		return true;

	}
	return false;

}

// Colission with NPC 
void checkCollisionWithNpc(PLAYER* player, NPC* npc, ALLEGRO_BITMAP* sprite, ALLEGRO_FONT* font, void (*callBack)()) {
	int pushBack = 5;

	int playerBottomRightX = player->POSX + 48;
	int playerBottomRightY = player->POSY + 48;

	int npcBottomDownX = npc->POSX + npc->WIDTH;
	int npcBottomDowny = npc->POSY + npc->HEIGH;

	float playerVel = player->VELOCITY;

	if (npc->POSX <= playerBottomRightX &&
		npcBottomDownX >= player->POSX &&
		npc->POSY <= playerBottomRightY &&
		npcBottomDowny >= player->POSY
		) {

		
		callBack(sprite, font, npc);
		

		return true;

	}
	return false;
	 
}

// Colission with Buttons
void checkCollisionWithButton(PLAYER* player, BUTTON* button) {
	int pushBack = 20;

	int playerBottomRightX = player->POSX + 48;
	int playerBottomRightY = player->POSY + 48;

	int buttonX = button->POSX - 10;
	int buttony = button->POSY - 10; 

	float playerVel = player->VELOCITY;

	if (button->POSX <= playerBottomRightX &&
		buttonX >= player->POSX &&
		button->POSY <= playerBottomRightY &&
		buttony >= player->POSY
		) {

		button->ISCOLLIDING = button->ISCOLLIDING * (-1);
		 
		if (button->ISCOLLIDING > 0) {
			button->VALUE = 1;
		}
		else {
			button->VALUE = 0;
		}

		// Push player to the oppsite direction to not get stuck
		if (player->PLAYERDIR == 0) player->POSY -= pushBack;
		if (player->PLAYERDIR == 1) player->POSY += pushBack;
		if (player->PLAYERDIR == 2) player->POSX += pushBack;
		if (player->PLAYERDIR == 3) player->POSX -= pushBack;

		return true;

	}
	
	return false;
}

void checkButtonResult(int binary_quest[], int binary_result[], int countCheck) {
	for (int i = 0; i < 4; i++) {
		if (binary_result[i] != binary_quest[i]) {
			return 0;
		}
		else {
			return countCheck += 1;
		}
	}
}

//Draw text Box
void drawTextBoxNpc(ALLEGRO_BITMAP* sprite, ALLEGRO_FONT* font, NPC* npc) {
	al_draw_scaled_bitmap(sprite, 0, 0, 144, 64, npc->POSX, npc->POSY - 144, 144 * 4, 64 * 2, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), npc->POSX + 20, npc->POSY - 130, 0, npc->lines);
	al_draw_text(font, al_map_rgb(255, 255, 255), npc->POSX + 20, npc->POSY - 100, 0, "Escreva com esses botoes 3 na base binaria");
	al_draw_text(font, al_map_rgb(255, 255, 255), npc->POSX + 20, npc->POSY - 70, 0, "Duvido que vai conseguir!!!");
};

void drawTextBox(ALLEGRO_BITMAP* sprite, ALLEGRO_FONT* font, NPC* npc, char text) {
	al_draw_scaled_bitmap(sprite, 0, 0, 144, 64, npc->POSX, npc->POSY - 144, 144 * 5, 64 * 2, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), npc->POSX + 15, npc->POSY - 130, 0, text);
};