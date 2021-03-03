
///////////////////////////////////////////////////////////////////////////////
// Headers.

#include <stdint.h>
#include "system.h"
#include <stdio.h>
#include <time.h>

#include "kola_rgb333.h"
#include "pozadina_rgb333.h"
#include "pozadina2_rgb333.h"
#include "novci_ograda_rgb333.h"
#include "pile_rgb333.h"
#include "brojevi_rgb333.h"



///////////////////////////////////////////////////////////////////////////////
// HW stuff.

#define WAIT_UNITL_0(x) while(x != 0){}
#define WAIT_UNITL_1(x) while(x != 1){}

#define SCREEN_IDX1_W 640
#define SCREEN_IDX1_H 480
#define SCREEN_IDX4_W 320
#define SCREEN_IDX4_H 240
#define SCREEN_RGB333_W 160
#define SCREEN_RGB333_H 120

#define SCREEN_IDX4_W8 (SCREEN_IDX4_W/8)

#define gpu_p32 ((volatile uint32_t*)LPRS2_GPU_BASE)
#define palette_p32 ((volatile uint32_t*)(LPRS2_GPU_BASE+0x1000))
#define unpack_idx1_p32 ((volatile uint32_t*)(LPRS2_GPU_BASE+0x400000))
#define pack_idx1_p32 ((volatile uint32_t*)(LPRS2_GPU_BASE+0x600000))
#define unpack_idx4_p32 ((volatile uint32_t*)(LPRS2_GPU_BASE+0x800000))
#define pack_idx4_p32 ((volatile uint32_t*)(LPRS2_GPU_BASE+0xa00000))
#define unpack_rgb333_p32 ((volatile uint32_t*)(LPRS2_GPU_BASE+0xc00000))
#define joypad_p32 ((volatile uint32_t*)LPRS2_JOYPAD_BASE)

typedef struct {
	unsigned a      : 1;
	unsigned b      : 1;
	unsigned z      : 1;
	unsigned start  : 1;
	unsigned up     : 1;
	unsigned down   : 1;
	unsigned left   : 1;
	unsigned right  : 1;
} bf_joypad;
#define joypad (*((volatile bf_joypad*)LPRS2_JOYPAD_BASE))

typedef struct {
	uint32_t m[SCREEN_IDX1_H][SCREEN_IDX1_W];
} bf_unpack_idx1;
#define unpack_idx1 (*((volatile bf_unpack_idx1*)unpack_idx1_p32))



///////////////////////////////////////////////////////////////////////////////
// Game config.
#define STEP 1
#define CHARACTER_STEP 8
#define CHARACTER_JUMP_DELAY 5
#define CAR_ANIM_DELAY 5
#define ACAB_DELAY 100
#define CAR_W 16
#define CAR_H 8



///////////////////////////////////////////////////////////////////////////////
// Game data structures.

typedef struct {
	int16_t x;
	int16_t y;
} point_t;

// Auto 1
typedef enum {
	CAR_LIGHTS_ON,
	CAR_LIGHTS_OFF
} car_anim_states_t;


typedef struct {
	car_anim_states_t state;
	uint8_t delay_cnt;
} car_anim_t;

typedef struct {
	point_t pos;
	car_anim_t anim;
} car_t;

// Character
typedef enum {
	IDE_DOLE,
	IDE_GORE,
	IDE_LEVO,
	IDE_DESNO
} char_anim_states_t;

typedef struct {
	char_anim_states_t state;
	uint8_t delay_cnt;
} char_anim_t;

typedef struct {
	point_t pos;
	char_anim_t anim;
} char_t;
////////////////
// Novcic
typedef enum {
	CRVEN,
	ZUT
} novcic_anim_states_t;

typedef struct {
	novcic_anim_states_t state;
	uint8_t delay_cnt;
} novcic_anim_t;

typedef struct {
	point_t pos;
	novcic_anim_t anim;
} novcic_t;




////////////////
typedef struct {
	car_t car1;
	car_t car2;
	car_t car3;
	car_t car4;
	novcic_t novcic;
	char_t character;
} game_state_t;

void draw_sprite_from_atlas(
	uint16_t src_x,
	uint16_t src_y,
	uint16_t w,
	uint16_t h,
	uint16_t dst_x,
	uint16_t dst_y,
	uint8_t izbor // 0 kola, 1 novcic,ograda, 2 karakter / 3 brojevi /
) {	
	if(!izbor){
		for(uint16_t y = 0; y < h; y++){
			for(uint16_t x = 0; x < w; x++){
				uint32_t src_idx = 
					(src_y+y)*kola__w +
					(src_x+x);
				uint32_t dst_idx = 
					(dst_y+y)*SCREEN_RGB333_W +
					(dst_x+x);
				uint16_t pixel = kola__p[src_idx];
				unpack_rgb333_p32[dst_idx] = pixel;
			}
		}
	}else if(izbor == 1){
		for(uint16_t y = 0; y < h; y++){
			for(uint16_t x = 0; x < w; x++){
				uint32_t src_idx = 
					(src_y+y)*novci_ograda__w +
					(src_x+x);
				uint32_t dst_idx = 
					(dst_y+y)*SCREEN_RGB333_W +
					(dst_x+x);
				uint16_t pixel = novci_ograda__p[src_idx];
				if(pixel == 0x000); // da mi ne zezne pozadinu, da ne printa crno okolo sprajta
				else unpack_rgb333_p32[dst_idx] = pixel;
			}
		}
	}else if(izbor == 2){
		for(uint16_t y = 0; y < h; y++){
			for(uint16_t x = 0; x < w; x++){
				uint32_t src_idx = 
					(src_y+y)*pile__w +
					(src_x+x);
				uint32_t dst_idx = 
					(dst_y+y)*SCREEN_RGB333_W +
					(dst_x+x);
				uint16_t pixel = pile__p[src_idx];
				if(pixel == 0x000);
				else unpack_rgb333_p32[dst_idx] = pixel;
			}
		}
	}else if(izbor == 3){
		for(uint16_t y = 0; y < h; y++){
			for(uint16_t x = 0; x < w; x++){
				uint32_t src_idx = 
					(src_y+y)*brojevi__w +
					(src_x+x);
				uint32_t dst_idx = 
					(dst_y+y)*SCREEN_RGB333_W +
					(dst_x+x);
				uint16_t pixel = brojevi__p[src_idx];
				if(pixel == 0x000);
				else unpack_rgb333_p32[dst_idx] = pixel;
			}
		}
	}
}
void draw_pozadina_from_atlas(
	uint16_t src_x,
	uint16_t src_y,
	uint16_t w,
	uint16_t h,
	uint16_t dst_x,
	uint16_t dst_y, 
	uint8_t acab
) {	
	if(!acab){ // biram koji pozadinu printam
		for(uint16_t y = 0; y < h; y++){
			for(uint16_t x = 0; x < w; x++){
				uint32_t src_idx = 
					(src_y+y)*pozadina__w +
					(src_x+x);
				uint32_t dst_idx = 
					(dst_y+y)*SCREEN_RGB333_W +
					(dst_x+x);
				uint16_t pixel = pozadina__p[src_idx];
				unpack_rgb333_p32[dst_idx] = pixel;
			}
		}
	}else{
		for(uint16_t y = 0; y < h; y++){
			for(uint16_t x = 0; x < w; x++){
				uint32_t src_idx = 
					(src_y+y)*pozadina2__w +
					(src_x+x);
				uint32_t dst_idx = 
					(dst_y+y)*SCREEN_RGB333_W +
					(dst_x+x);
				uint16_t pixel = pozadina2__p[src_idx];
				unpack_rgb333_p32[dst_idx] = pixel;
			}
		}
	}	
}
///
///////////////////////////////////////////////////////////////////////////////
// Game code.

int main(void) {
	
	// Setup.
	srand(time(NULL));
	


	gpu_p32[0] = 3; // Color bar.
	gpu_p32[0x800] = 0x00ff00ff; // Magenta for HUD.


	// Game state.
	game_state_t gs;
	//kola1
	gs.car1.pos.x = 0;
	gs.car1.pos.y = 19;
	gs.car1.anim.state = CAR_LIGHTS_ON;
	gs.car1.anim.delay_cnt = 0;

	//kola2
	gs.car2.pos.x = SCREEN_RGB333_W-16;
	gs.car2.pos.y = 53;
	gs.car2.anim.state = CAR_LIGHTS_ON;
	gs.car2.anim.delay_cnt = 0;

	//kola3
	gs.car3.pos.x = SCREEN_RGB333_W-16;
	gs.car3.pos.y = 72;
	gs.car3.anim.state = CAR_LIGHTS_ON;
	gs.car3.anim.delay_cnt = 0;

	// kola4
	gs.car4.pos.x = 0;
	gs.car4.pos.y = 35;
	gs.car4.anim.state = CAR_LIGHTS_ON;
	gs.car4.anim.delay_cnt = 0;

	//novcic
	gs.novcic.pos.x = rand()%152;
	gs.novcic.pos.y = rand()%112;
	gs.novcic.anim.state = ZUT;
	gs.novcic.anim.delay_cnt = 0;

	gs.character.pos.x=80;
	gs.character.pos.y=112;

	gs.character.anim.state=IDE_GORE;
	int mov_x = 0;
	int mov_y = 0;
	int cnt = 0; // softversko diferenciranje skokova igraca
	int acab_cnt = 0; //koliko dugo je printan ACAB ekran
	/*
		Danger zone -- koolizija:
		oko objekta sa kojim treba da imam sudar (novcic, auto) racunam "danger zone"
		imam 5 objekata od interesa, za svaki racunam i onda pitam da li se pile nalazi unutar nje 

		dzX = (Xobjekta - sirinaKaraktera) U ( Xobjekta + sirinaObjekta)
		dzY = (Yobjekta - visinaKaraktera) U ( Yobjekta + visinaObjekta)
			
	*/
	int dz_x_pocetak1 = 0;
	int dz_x_kraj1 =0;
	int dz_y_pocetak1 = 0;
	int dz_y_kraj1 = 0;

	int dz_x_pocetak2 = 0;
	int dz_x_kraj2 =0;
	int dz_y_pocetak2 = 0;
	int dz_y_kraj2 = 0;

	int dz_x_pocetak3 = 0;
	int dz_x_kraj3 =0;
	int dz_y_pocetak3 = 0;
	int dz_y_kraj3 = 0;

	int dz_x_pocetak4 = 0;
	int dz_x_kraj4 =0;
	int dz_y_pocetak4 = 0;
	int dz_y_kraj4 = 0;
	
	int ACAB = 0;
	int poeni=0; // poeni od skakutanja
	int konacni_poeni = 0; // poeni + koliko je novcica nasao

	// za novcic
	int nasao = 0;
	int dz_x_pocetak5 = 0;
	int dz_x_kraj5 =0;
	int dz_y_pocetak5 = 0;
	int dz_y_kraj5 = 0;

	int poslednje_isao = 0; // 0 gore, 1 dole, 2 levo , 3 desno


	while(1){
		

		/////////////////////////////////////
		// Poll controls.
		if(cnt  < CHARACTER_JUMP_DELAY) cnt++; // DA NE BI LETEO PO EKRANU KAO LUD
		else{
			if(joypad.right){
				mov_x = 1;
				cnt = 0;
				poslednje_isao = 3;
			}else if(joypad.left){
				mov_x = -1;
				cnt = 0;
				poslednje_isao = 2;
			}
			if(joypad.up){
				mov_y = -1;
				cnt = 0;
				poslednje_isao = 0;
			}else if(joypad.down){
				mov_y = 1;
				cnt = 0;
				poslednje_isao = 1;
			}
		}
		// broj poena je ogranicen da ne moze da se smanjuje ukoliko ide nazad, ali da ne moze da se poveca ukoliko dva puta skoci na istu lokaciju
		// krecem od dole, znaci idem po Y osi od nazad, zato mnozim sa -1
		if((-1*(gs.character.pos.y/8-14))>poeni) poeni = -1*(gs.character.pos.y/8-14);
		konacni_poeni = poeni + nasao;

		if((gs.character.pos.x +mov_x*CHARACTER_STEP)>152) gs.character.pos.x=152; //ogranicenja
		else if((gs.character.pos.x +mov_x*CHARACTER_STEP)<0) gs.character.pos.x=0;
		else gs.character.pos.x += mov_x*CHARACTER_STEP;


		if((gs.character.pos.y +mov_y*CHARACTER_STEP)>112) gs.character.pos.y=112;
		else if((gs.character.pos.y +mov_y*CHARACTER_STEP)<0) gs.character.pos.y=0;
		else gs.character.pos.y += mov_y*CHARACTER_STEP;

		gs.car1.pos.x += STEP;
		if(gs.car1.pos.x > 160) gs.car1.pos.x =0;
		gs.car2.pos.x -=STEP;

		gs.car4.pos.x += STEP*2; // auto 2 i 4 idu brze
		if(gs.car4.pos.x > 160) gs.car4.pos.x =0;
		gs.car3.pos.x -=STEP*2;
		if(gs.car3.pos.x < 0 || gs.car3.pos.x > 160) gs.car3.pos.x = 160-16;	


		mov_x = 0;
		mov_y = 0;	
	
		// racunanje danger zone za svaki automobil/novcic
		dz_x_pocetak1 = gs.car1.pos.x - 8;
		dz_x_kraj1 = gs.car1.pos.x+16;
		dz_y_pocetak1 = gs.car1.pos.y - 8;
		dz_y_kraj1 = gs.car1.pos.y+8;

		dz_x_pocetak2 = gs.car2.pos.x - 8;
		dz_x_kraj2 = gs.car2.pos.x+16;
		dz_y_pocetak2 = gs.car2.pos.y - 8;
		dz_y_kraj2 = gs.car2.pos.y+8;

		dz_x_pocetak3 = gs.car3.pos.x - 8;
		dz_x_kraj3 = gs.car3.pos.x+16;
		dz_y_pocetak3 = gs.car3.pos.y - 8;
		dz_y_kraj3 = gs.car3.pos.y+8;

		dz_x_pocetak4 = gs.car4.pos.x - 8;
		dz_x_kraj4 = gs.car4.pos.x+16;
		dz_y_pocetak4 = gs.car4.pos.y - 8;
		dz_y_kraj4 = gs.car4.pos.y+8;

		
		dz_x_pocetak5 = gs.novcic.pos.x - 8;
		dz_x_kraj5 = gs.novcic.pos.x+8;
		dz_y_pocetak5 = gs.novcic.pos.y - 8;
		dz_y_kraj5 = gs.novcic.pos.y+8;
	

		// provera kolizije
		if ((((gs.character.pos.x >= dz_x_pocetak2) && (gs.character.pos.x <= dz_x_kraj2)) &&
			((gs.character.pos.y >= dz_y_pocetak2) && (gs.character.pos.y <= dz_y_kraj2)))
		 ){
		 	// MURIJSKA KOLA ACAB ACAB
			gs.character.pos.x=80;
			gs.character.pos.y=112;
			ACAB = 1;
			acab_cnt = ACAB_DELAY;
			poeni = 0;
			nasao = 0;
		}
		if ((((gs.character.pos.x >= dz_x_pocetak1) && (gs.character.pos.x <= dz_x_kraj1)) &&
			((gs.character.pos.y >= dz_y_pocetak1) && (gs.character.pos.y <= dz_y_kraj1)))
		 ){
			gs.character.pos.x=80;
			gs.character.pos.y=112;
			poeni = 0;	
			nasao = 0;
		}
		if ((((gs.character.pos.x >= dz_x_pocetak3) && (gs.character.pos.x <= dz_x_kraj3)) &&
			((gs.character.pos.y >= dz_y_pocetak3) && (gs.character.pos.y <= dz_y_kraj3)))
		 ){
			gs.character.pos.x=80;
			gs.character.pos.y=112;
			poeni = 0;
			nasao = 0;	
		}
		if ((((gs.character.pos.x >= dz_x_pocetak4) && (gs.character.pos.x <= dz_x_kraj4)) &&
			((gs.character.pos.y >= dz_y_pocetak4) && (gs.character.pos.y <= dz_y_kraj4)))
		 ){
		 	poeni = 0;
		 	nasao = 0;
			gs.character.pos.x=80;
			gs.character.pos.y=112;
		}
		
		if ((((gs.character.pos.x >= dz_x_pocetak5) && (gs.character.pos.x <= dz_x_kraj5)) &&
			((gs.character.pos.y >= dz_y_pocetak5) && (gs.character.pos.y <= dz_y_kraj5)))
		 ){
		 	// uzeo novce, respawnujem ga negde druge na ekran
		    nasao++;
		 	gs.novcic.pos.x = rand()%152;
			gs.novcic.pos.y = rand()%112;
		}
	



		
		/////////////////////////////////////
		// Animajice za auta

		switch(gs.car1.anim.state){
		case CAR_LIGHTS_ON:
			if(gs.car1.anim.delay_cnt != 0){
					gs.car1.anim.delay_cnt--;
			}else{
				gs.car1.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.car1.anim.state = CAR_LIGHTS_OFF;
			}
			break;
		case CAR_LIGHTS_OFF:
			if(gs.car1.anim.delay_cnt != 0){
					gs.car1.anim.delay_cnt--;
			}else{
				gs.car1.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.car1.anim.state = CAR_LIGHTS_ON;
			}
			break;
		}

		
		if(!gs.car2.pos.x) gs.car2.pos.x = SCREEN_RGB333_W-16;

		switch(gs.car2.anim.state){
			case CAR_LIGHTS_ON:
				if(gs.car2.anim.delay_cnt != 0){
					gs.car2.anim.delay_cnt--;
			}else{
				gs.car2.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.car2.anim.state = CAR_LIGHTS_OFF;
			}
			break;
			case CAR_LIGHTS_OFF:
				if(gs.car2.anim.delay_cnt != 0){
					gs.car2.anim.delay_cnt--;
			}else{
				gs.car2.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.car2.anim.state = CAR_LIGHTS_ON;
			}
			break;
		}

		switch(gs.car3.anim.state){
			case CAR_LIGHTS_ON:
				if(gs.car3.anim.delay_cnt != 0){
					gs.car3.anim.delay_cnt--;
			}else{
				gs.car3.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.car3.anim.state = CAR_LIGHTS_OFF;
			}
			break;
			case CAR_LIGHTS_OFF:
				if(gs.car3.anim.delay_cnt != 0){
					gs.car3.anim.delay_cnt--;
			}else{
				gs.car3.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.car3.anim.state = CAR_LIGHTS_ON;
			}
			break;
		}

		switch(gs.car4.anim.state){
			case CAR_LIGHTS_ON:
				if(gs.car4.anim.delay_cnt != 0){
					gs.car4.anim.delay_cnt--;
			}else{
				gs.car4.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.car4.anim.state = CAR_LIGHTS_OFF;
			}
			break;
			case CAR_LIGHTS_OFF:
				if(gs.car4.anim.delay_cnt != 0){
					gs.car4.anim.delay_cnt--;
			}else{
				gs.car4.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.car4.anim.state = CAR_LIGHTS_ON;
			}
			break;
		}
		switch(gs.novcic.anim.state){
			case ZUT:
				if(gs.novcic.anim.delay_cnt != 0){
					gs.novcic.anim.delay_cnt--;
			}else{
				gs.novcic.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.novcic.anim.state = CRVEN;
			}
			break;
			case CRVEN:
				if(gs.novcic.anim.delay_cnt != 0){
					gs.novcic.anim.delay_cnt--;
			}else{
				gs.novcic.anim.delay_cnt = CAR_ANIM_DELAY;
				gs.novcic.anim.state = ZUT;
			}
			break;
		}
		// za karaktera radim malo drugacije, pamtilo se gde je poslednje isao da bi pile na tu stranu
		switch(poslednje_isao){
			case 0:
				gs.character.anim.state = IDE_GORE;
				break;
			case 1:
				gs.character.anim.state = IDE_DOLE;
				break;
			case 2:
				gs.character.anim.state = IDE_LEVO;
				break;
			case 3:
				gs.character.anim.state = IDE_DESNO;
				break;
		}



		
		/////////////////////////////////////
		// Drawing.
		
		
		// Detecting rising edge of VSync.
		WAIT_UNITL_0(gpu_p32[2]);
		WAIT_UNITL_1(gpu_p32[2]);
		// Draw in buffer while it is in VSync.
		
		if(acab_cnt) acab_cnt--;
		else{
			ACAB = 0;
		}
		
		draw_pozadina_from_atlas(
		0, 0, 160, 120, 0, 0, ACAB
		);
		switch(gs.car1.anim.state){
		case CAR_LIGHTS_ON:
			draw_sprite_from_atlas(
				0, 8, 16, 8, gs.car1.pos.x, gs.car1.pos.y, 0//police svetla
			);
			break;
		case CAR_LIGHTS_OFF:
			draw_sprite_from_atlas(
				16, 8, 16, 8, gs.car1.pos.x, gs.car1.pos.y, 0
			);
			break;
		}
		switch(gs.car2.anim.state){
		case CAR_LIGHTS_ON:
			draw_sprite_from_atlas(
				0, 0, 16, 8, gs.car2.pos.x, gs.car2.pos.y, 0
			);
			break;
		case CAR_LIGHTS_OFF:
			draw_sprite_from_atlas(
				16, 0, 16, 8, gs.car2.pos.x, gs.car2.pos.y, 0
			);
			break;
		}
		switch(gs.car3.anim.state){
		case CAR_LIGHTS_ON:
			draw_sprite_from_atlas(
				0, 16, 16, 8, gs.car3.pos.x, gs.car3.pos.y, 0
			);
			break;
		case CAR_LIGHTS_OFF:
			draw_sprite_from_atlas(
				16, 16, 16, 8, gs.car3.pos.x, gs.car3.pos.y, 0
			);
			break;
		}
		switch(gs.car2.anim.state){
		case CAR_LIGHTS_ON:
			draw_sprite_from_atlas(
				0, 24, 16, 8, gs.car4.pos.x, gs.car4.pos.y, 0
			);
			break;
		case CAR_LIGHTS_OFF:
			draw_sprite_from_atlas(
				16, 24, 16, 8, gs.car4.pos.x, gs.car4.pos.y, 0
			);
			break;
		}
		// novcic
		switch(gs.novcic.anim.state){
		case ZUT:
			draw_sprite_from_atlas(
				0, 0, 7, 6, gs.novcic.pos.x, gs.novcic.pos.y, 1
			);
			break;
		case CRVEN:
			draw_sprite_from_atlas(
				7, 0, 7, 6, gs.novcic.pos.x, gs.novcic.pos.y, 1
			);
			break;
		}
	
		// crtanje karaktera
		switch(poslednje_isao){
		case 0:
			draw_sprite_from_atlas(
				7, 7, 7, 7, gs.character.pos.x, gs.character.pos.y, 2
			);
			break;
		case 1:
			draw_sprite_from_atlas(
				0, 0, 7, 7, gs.character.pos.x, gs.character.pos.y, 2
			);
			break;
		case 2:
			draw_sprite_from_atlas(
				7, 0, 7, 7, gs.character.pos.x, gs.character.pos.y, 2
			);
			break;
		case 3:
			draw_sprite_from_atlas(
				0, 7, 7, 7, gs.character.pos.x, gs.character.pos.y, 2
			);
			break;
		}
		// crtanje rezultata
		draw_sprite_from_atlas(
				(konacni_poeni % 10)*9,0 , 9, 10, 150, 0, 3
			);
		draw_sprite_from_atlas(
				(konacni_poeni / 10)*9, 0, 9, 10, 140, 0, 3
			);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
