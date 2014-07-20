#include <stdio.h>
#include <nds.h>
#include <alchemy0.h>
#include "../include/graphic_engine.h" 


#define SCREEN_TOP 0
#define SCREEN_BOTTOM 192
#define SCREEN_LEFT 0
#define SCREEN_RIGHT 256

#define TRASH 0
#define LEFT 1
#define RIGHT 2
#define ADD 3
#define HOME 4
#define CORRECT 5
#define ELEMENT1 6
#define ELEMENT2 7
#define ELEMENT3 8
#define ELEMENT4 9
#define ELEMENT5 10
#define ELEMENT6 11

#define NUMBER_SPRITE_MAIN_SCREEN 11

typedef struct _elements_list{
  int size;
  int element;
  struct _list_elements* next;
} elements_list;

typedef struct{
  unsigned char x;
  unsigned char y;

  unsigned char sprite_number;
  unsigned char hide;

  u16* sprite_gfx_mem;
  u8* frame_gfx;

} sprite2D;

sprite2D divide_main_screen[NUMBER_SPRITE_MAIN_SCREEN];

int current_position_list;

list_elements list;

void init_graphic_engine(){

  //Configuration de l'ecran du dessous 
  videoSetModeSub(MODE_0_2D);
  init_main_screen();

  //Configuration de l'ecran de dessus 
  videoSetMode(MODE_0_3D);
  init_sec_screen();

}

//  Division de l'ecran principal ( retour au menu, corbeille, selection des objets, etc... )
void init_main_screen(){
  vramSetBankD(VRAM_D_SUB_SPRITE);
  oamInit(&oamSub, SpriteMapping_Bmp_AD_256,false);

  init_2D_sprite(&divide_main_screen[LEFT],(u8*)alchemy0Tiles,0,0,0);
  init_2D_sprite(&divide_main_screen[ELEMENT1],(u8*)alchemy0Tiles,64,0,0);
  init_2D_sprite(&divide_main_screen[ELEMENT2],(u8*)alchemy0Tiles,128,0,0);
  init_2D_sprite(&divide_main_screen[ELEMENT3],(u8*)alchemy0Tiles,192,0,0);

  init_2D_sprite(&divide_main_screen[ELEMENT4],(u8*)alchemy0Tiles,0,64,0);
  init_2D_sprite(&divide_main_screen[ELEMENT5],(u8*)alchemy0Tiles,64,64,0);
  init_2D_sprite(&divide_main_screen[ELEMENT6],(u8*)alchemy0Tiles,128,64,0);
  init_2D_sprite(&divide_main_screen[RIGHT],(u8*)alchemy0Tiles,192,64,0);

  init_2D_sprite(&divide_main_screen[ADD],(u8*)alchemy0Tiles,0,128,0);
  init_2D_sprite(&divide_main_screen[HOME],(u8*)alchemy0Tiles,64,128,0);
  init_2D_sprite(&divide_main_screen[CORRECT],(u8*)alchemy0Tiles,128,128,0);
  init_2D_sprite(&divide_main_screen[TRASH],(u8*)alchemy0Tiles,192,128,0);

  dmaCopy(alchemy0Pal, SPRITE_PALETTE_SUB, 512);
}


void init_sec_screen(){
  
}


void init_2D_sprite(sprite2D sprite, u8* gfx, unsigned char _x,unsigned char _y, unsigned char _sprite_number){
  sprite->x = _x;
  sprite->y = _y;
  sprite->sprite_number = _sprite_number;
  sprite->hide = 0;
  sprite->sprite_gfx_mem = oamAllocateGfx(&oamSub, SpriteSize_64x64, SpriteColorFormat_256Color);
  sprite->frame_gfx = (u8*)gfx;
}

void change_sprite(sprite2D* sprite,unsigned char frame){
  u8* offset = sprite->frame_gfx + frame * 64*64;
  dmaCopy(offset,sprite->sprite_gfx_mem,64*64);
  sprite->sprite_number = frame;
}

void display_elements_list(){
  
  if(current_position_list==0)
    divide_main_screen[LEFT]->hide = true;
  else
    divide_main_screen[LEFT]->hide = false;
  
  if(current_position_list== (list->size - ELEMENT1))
    divide_main_screen[RIGHT]->hide = true;
  else
    divide_main_screen[LEFT]->hide = false;
  
  change_sprite(divide_main_screen[current_position_list],);
   
  for(i=0;i<=NUMBER_SPRITE_MAIN_SCREEN;i++)
    change_sprite(&divide_main_screen[ELEMENT1+i],6+current_position_list+i);
}

void clear_elements(){
  
}
