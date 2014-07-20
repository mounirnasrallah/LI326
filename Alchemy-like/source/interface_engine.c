#ifndef INTERFACE_ENGINE
#define INTERFACE_ENGINE

#include <stdlib.h>
#include <nds.h>
#include "graphic_engine.h"

unsigned char is_stylus_on_sprite(sprite2D* sprite, touchPosition touch){
  if( (touch.px < sprite->x) || (touch.px > ((sprite->x)+64)) ){
    return 0;
  }
  if( (touch.py <sprite->y) ||(touch.py > ((sprite->y)+64)) ){
    return 0;
  }
  return 1;
}


unsigned char is_stylus_on_menu(unsigned char x1,unsigned char x2,unsigned char y1,unsigned char y2,touchPosition touch ){
  if( (touch.px < x2) && (touch.px > x1) && (touch.py > y1) && (touch.py < y2))
    return 1;
  return 0;
}



#endif
