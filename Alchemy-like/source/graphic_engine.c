#include <stdio.h>
#include <nds.h>
#include <sprites.h>
#include <bg_menu_sub.h>
#include <bg_menu_main.h>
#include "../include/graphic_engine.h" 
#include "../include/list.h"
#include "../include/include.h"
#include <bg_play.h>
#include <bg_play2.h>
#include "../include/main.h"
#include "../include/sound_engine.h"

int current_position_list;
char init_play; 

list* list_elm;
sprite2D divide_sub_screen[3];
sprite2D divide_menu[NUMBER_BUTTONS_MENU];
sprite2D divide_main_screen[NUMBER_SPRITE_MAIN_SCREEN];

void add_element(int a){
  add_element_list(list_elm,a);  
}

void init_graphic_engine(){

  //Configuration de l'ecran du dessous 
  videoSetModeSub(MODE_5_2D);
  init_main_screen();

  //Configuration de l'ecran de dessus 
  videoSetMode(MODE_5_2D);
  init_sec_screen();

}

void init_menu(){

  videoSetModeSub(MODE_5_2D);  
  vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

  videoSetMode(MODE_5_2D);
  vramSetBankC(VRAM_C_SUB_BG);

  int bg = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);
  dmaCopy(bg_menu_mainBitmap, bgGetGfxPtr(bg), 256*256);
  dmaCopy(bg_menu_mainPal, BG_PALETTE, 512);

  int bgSub = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);  
  dmaCopy(bg_menu_subBitmap, bgGetGfxPtr(bgSub), 256*256);  
  dmaCopy(bg_menu_subPal, BG_PALETTE_SUB, 512);  

}

//  Division de l'ecran principal ( retour au menu, corbeille, selection des objets, etc... )
void init_main_screen(){

  int bg_play;

  vramSetBankD(VRAM_D_MAIN_BG_0x06000000);
  bg_play = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256,0,0);
  dmaCopy(bg_play2Bitmap, bgGetGfxPtr(bg_play), 256*256);
  dmaCopy(bg_play2Pal,BG_PALETTE_SUB, 512);

  vramSetBankD(VRAM_D_SUB_SPRITE);
  oamInit(&oamSub, SpriteMapping_Bmp_1D_256,false);

  if(init_play == 0){
    
    init_2D_sprite(&divide_main_screen[LEFT],(u8*)spritesTiles,0,0,0);
    init_2D_sprite(&divide_main_screen[ELEMENT1],(u8*)spritesTiles,64,0,0);
    init_2D_sprite(&divide_main_screen[ELEMENT2],(u8*)spritesTiles,128,0,0);
    init_2D_sprite(&divide_main_screen[ELEMENT3],(u8*)spritesTiles,192,0,0);
    
    init_2D_sprite(&divide_main_screen[ELEMENT4],(u8*)spritesTiles,0,64,0);
    init_2D_sprite(&divide_main_screen[ELEMENT5],(u8*)spritesTiles,64,64,0);
    init_2D_sprite(&divide_main_screen[ELEMENT6],(u8*)spritesTiles,128,64,0);
    init_2D_sprite(&divide_main_screen[RIGHT],(u8*)spritesTiles,192,64,0);
    
    init_2D_sprite(&divide_main_screen[ADD],(u8*)spritesTiles,0,128,0);
    init_2D_sprite(&divide_main_screen[HOME],(u8*)spritesTiles,64,128,0);
    init_2D_sprite(&divide_main_screen[CORRECT],(u8*)spritesTiles,128,128,0);
    init_2D_sprite(&divide_main_screen[TRASH],(u8*)spritesTiles,192,128,0);
    
    dmaCopy(spritesPal, SPRITE_PALETTE_SUB, 512);
    
    list_elm = create_list();
    init_list(list_elm);
    
  }
  
  display_elements_list();
  display_buttons_play();
  
}

void init_sec_screen(){
  
  int bg_play;

  vramSetBankB(VRAM_B_MAIN_BG_0x06000000);
  bg_play = bgInit(2, BgType_Bmp8, BgSize_B8_256x256,0,0);
  dmaCopy(bg_playBitmap, bgGetGfxPtr(bg_play), 256*256);
  dmaCopy(bg_playPal, BG_PALETTE, 512);
  
  vramSetBankB(VRAM_B_MAIN_SPRITE);
  oamInit(&oamMain, SpriteMapping_Bmp_1D_256,false);
  
  if(init_play == 0){
    init_2D_sprite_main(&divide_sub_screen[0],(u8*)spritesTiles,128,30,0);
    init_2D_sprite_main(&divide_sub_screen[1],(u8*)spritesTiles,64,100,0);
    init_2D_sprite_main(&divide_sub_screen[2],(u8*)spritesTiles,128,100,0);
    dmaCopy(spritesPal, SPRITE_PALETTE, 512);
    combinaison[0] = -1;
    combinaison[1] = -1;      
  }
  
  display_elements_sec();
  
}

void delete_combinaison(){
  combinaison[0]= -1;
  combinaison[1] = -1;
  
}

void display_elements_sec(){
  
  if(combinaison[0]!=-1)
    change_sprite(&divide_sub_screen[1],combinaison[0]+ELEMENT1);
  
  if(combinaison[1]!=-1)
    change_sprite(&divide_sub_screen[2],combinaison[1]+ELEMENT1);
  
}


void init_2D_sprite_main(sprite2D* sprite, u8* gfx, unsigned char _x,unsigned char _y, unsigned char _sprite_number){
  sprite->x = _x;
  sprite->y = _y;
  sprite->sprite_number = _sprite_number;
  sprite->hide = true;
  sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
  sprite->frame_gfx = (u8*)gfx;

}

void init_2D_sprite(sprite2D* sprite, u8* gfx, unsigned char _x,unsigned char _y, unsigned char _sprite_number){

  sprite->x = _x;
  sprite->y = _y;
  sprite->sprite_number = _sprite_number;
  sprite->hide = false;
  sprite->sprite_gfx_mem = oamAllocateGfx(&oamSub, SpriteSize_64x64, SpriteColorFormat_256Color);
  sprite->frame_gfx = (u8*)gfx;

}

void change_sprite(sprite2D* sprite,unsigned char frame){
  u8* offset = sprite->frame_gfx + (frame * (64*64));
  dmaCopy(offset,sprite->sprite_gfx_mem,64*64);
  sprite->sprite_number = frame;
}

void display_elements_list(){
  int i;
  element_list* elm;
  
  elm = access(list_elm,current_position_list);
  
  for(i=0;i<=NUMBER_SPRITE_MAIN_SCREEN-ELEMENT1;i++){
    divide_main_screen[ELEMENT1+i].hide = false;
    change_sprite(&divide_main_screen[ELEMENT1+i],ELEMENT1 + elm->element);
    elm = elm->next;
  }
  
}


void clear_direction(){

  divide_main_screen[LEFT].hide = true;
  divide_main_screen[RIGHT].hide = true;
  
}

void display_buttons_play(){

  change_sprite(&divide_main_screen[LEFT],LEFT); 
  change_sprite(&divide_main_screen[RIGHT],RIGHT);   
  change_sprite(&divide_main_screen[TRASH],TRASH); 
  change_sprite(&divide_main_screen[ADD],ADD); 
  change_sprite(&divide_main_screen[HOME],HOME);
  change_sprite(&divide_main_screen[CORRECT],CORRECT);

}

void graphic_loop(){
  
  int i;
  for(i=0;i<NUMBER_SPRITE_MAIN_SCREEN;i++){  
    oamSet(&oamSub, 
	   i, 
	   divide_main_screen[i].x, 
	   divide_main_screen[i].y,
	   0,
	   0,
	   SpriteSize_64x64,
	   SpriteColorFormat_256Color,
	   divide_main_screen[i].sprite_gfx_mem,
	   -1,
	   false,
	   divide_main_screen[i].hide,
	   false,
	   false,
	   false);
  }

  swiWaitForVBlank();
  oamUpdate(&oamMain);

}

void graphic_loop_sprite_main(){
  oamSet(&oamMain,
	 0,
	 divide_sub_screen[0].x,
	 divide_sub_screen[0].y,
	 0,
	 0,
	 SpriteSize_64x64,
	 SpriteColorFormat_256Color,
	 divide_sub_screen[0].sprite_gfx_mem,
	 -1,
	 false,
	 divide_sub_screen[0].hide,
	 false,
	 false,
	 false);

      oamSet(&oamMain,
           1,
           divide_sub_screen[1].x,
           divide_sub_screen[1].y,
           0,
           0,
           SpriteSize_64x64,
           SpriteColorFormat_256Color,
           divide_sub_screen[1].sprite_gfx_mem,
           -1,
           false,
           divide_sub_screen[1].hide,
           false,
           false,
           false);
  
    oamSet(&oamMain,
           2,
           divide_sub_screen[2].x,
           divide_sub_screen[2].y,
           0,
           0,
           SpriteSize_64x64,
           SpriteColorFormat_256Color,
           divide_sub_screen[2].sprite_gfx_mem,
           -1,
           false,
           divide_sub_screen[2].hide,
           false,
           false,
           false);

  swiWaitForVBlank();
  oamUpdate(&oamSub);

}

void clear_sub_screen(){
  divide_sub_screen[0].hide = true;
  divide_sub_screen[1].hide = true;
  divide_sub_screen[2].hide = true;
}
  
void clear_elements(){
  
}

void next_element_list(){
  
  if( current_position_list <= (list_elm->size - ELEMENT1) ){
    current_position_list+=1;
    display_elements_list();
    play_sound_move_list();
  }
}


void prev_element_list(){
  
  if(current_position_list>0){
    current_position_list-=1;
    display_elements_list();
    play_sound_move_list();
  }

}
