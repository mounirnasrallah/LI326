#include <nds.h>
#include "../include/include.h"
#include "../include/alchemy_engine.h"
#include "../include/graphic_engine.h"
#include "../include/interface_engine.h"
#include "../include/list.h"
#include "../include/saving_engine.h"
#include "../include/sound_engine.h"
#include "../include/main.h"
#include "../include/3D_engine.h"

#define MENU 0
#define LOAD 1
#define PLAY 2
#define QUIT 3

unsigned char screen_select = MENU;

int nbr_select;
int combinaison[2];
sprite2D divide_sub_screen[3];
sprite2D divide_main_screen[NUMBER_SPRITE_MAIN_SCREEN];

int main(void){

  init_play = 0;
  init_sound_engine();

  touchPosition touch;

    while(1){

    if(screen_select==MENU){
      screen_select = menu();
    }
    
    if(screen_select==LOAD){
      load();
    }

    if(screen_select==PLAY){
      play();
    }
    
    if(screen_select==QUIT){ 
      return 0;
    }

    }

    return 0;
}




unsigned char menu(){

  touchPosition touch;

  init_menu();
  
 
  while(1){
    
    scanKeys();
    touchRead(&touch);
    
    int pressed = keysDown();
    int held = keysHeld();

    if(!(pressed & KEY_TOUCH)) continue;

    if(!(held & KEY_TOUCH) || (touch.rawx == 0) || (touch.rawy == 0)) continue;

    if(is_stylus_on_menu(24,233,44,74,touch)){
      screen_select = PLAY;
      return PLAY;
    }

    if(is_stylus_on_menu(24,233,84,114,touch)){
      screen_select = LOAD;
      return LOAD;
    }

    if(is_stylus_on_menu(24,233,124,154,touch)){
      screen_select = QUIT;
      return QUIT;
    }
  }

}

void load(){

  init_saving_engine();

  touchPosition touch;

  list_load_file();

  while(1){}
}

void play(){

  touchPosition touch;
  int i;
  unsigned char tmp;

  current_position_list = 0;

  init_graphic_engine();
  
  if (init_play == 0){
    init_play = 1;
  }


  while(1){ 

    clear_direction();

    if(current_position_list > 0){
      divide_main_screen[LEFT].hide = false;
    }
    
    if( current_position_list <= (list_elm->size - ELEMENT1 ) ){
      divide_main_screen[RIGHT].hide = false;
    }
    
    graphic_loop();
    graphic_loop_sprite_main();

    scanKeys();
    touchRead(&touch);
    
    int pressed = keysDown();
    int held = keysHeld();

    if(!(pressed & KEY_TOUCH)) continue;
    
    if(!(held & KEY_TOUCH) || (touch.rawx == 0) || (touch.rawy == 0)) continue;
    
    if(is_stylus_on_sprite(&divide_main_screen[LEFT],touch)){
      prev_element_list();
    }

    if(is_stylus_on_sprite(&divide_main_screen[RIGHT],touch)){
      next_element_list();
    }

    if(is_stylus_on_sprite(&divide_main_screen[TRASH],touch)){
      play_sound_trash();
      delete_combinaison();
      divide_sub_screen[0].hide = true;
      divide_sub_screen[1].hide = true;
      divide_sub_screen[2].hide = true;
      nbr_select = 0;
    }

    if(is_stylus_on_sprite(&divide_main_screen[HOME],touch)){
      current_position_list=0;
      screen_select=MENU;
      return;
    }

    if(is_stylus_on_sprite(&divide_main_screen[CORRECT],touch)){
    }
  
    if(is_stylus_on_sprite(&divide_main_screen[ADD],touch)){

      if(nbr_select==2){
	tmp = combine(combinaison[0],combinaison[1]);
	if(tmp != 0){
	  add_element(tmp);

	  // Supression de la combinaison
	  used_combinaison(combinaison[0],combinaison[1]);

	  play_sound_success();
	  nbr_select = 0;
	  combinaison[0] = -1;
	  combinaison[1] = -1;
	  clear_sub_screen();

	  gestion_3D(tmp);

	  init_graphic_engine();
	}
	else{
	  nbr_select = 0;
	  clear_sub_screen();
	}
      }
      else{
	
      }
    }

    for(i = ELEMENT1;i<NUMBER_SPRITE_MAIN_SCREEN;i++){
      if(is_stylus_on_sprite(&divide_main_screen[i],touch)){
	if(nbr_select<2){
	  divide_sub_screen[nbr_select+1].hide = false;
	  play_sound_select();	
	  combinaison[nbr_select]=(divide_main_screen[i].sprite_number) - ELEMENT1;
	  nbr_select++;
	  display_elements_sec();
          graphic_loop_sprite_main();
	}
	else{
	}
      }
    }
  }
  

}

