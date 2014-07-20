#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include "include.h"

//#include <stdlib.h>


typedef struct _sprite2D{
  unsigned char x;
  unsigned char y;

  unsigned char sprite_number;
  unsigned char hide;

  u16* sprite_gfx_mem;
  u8* frame_gfx;

  unsigned char number_element;
} sprite2D;

extern sprite2D divide_main_screen[NUMBER_SPRITE_MAIN_SCREEN];
extern sprite2D divide_menu[NUMBER_BUTTONS_MENU];
extern sprite2D divide_sub_screen[3];

extern char init_play;
extern int current_position_list;

void init_graphic_engine();
void init_main_screen();
void init_sec_screen();
void init_2D_sprite(sprite2D* sprite, u8* gfx, unsigned char _x,unsigned char _y, unsigned char _sprite_number);
void change_sprite(sprite2D* sprite,unsigned char frame);
void display_elements_list();
void clear_elements();
void graphic_loop();
void display_buttons_play();
void init_menu();
void add_element(int a);
void clear_sub_screen();
void clear_direction();

#endif

