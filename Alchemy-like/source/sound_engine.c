#include "../include/sound_engine.h"
#include "../include/soundbank.h"
#include "../include/soundbank_bin.h"  
#include <maxmod9.h>
#include <nds.h>

mm_sound_effect sfx_hit = {
  {SFX_HIT},
  1024,
  0,
  255,
  255
};

mm_sound_effect sfx_yahooo = {
  {SFX_YAAHOOO},
  1024,
  0,
  255,
  255
};

void init_sound_engine(){
  mmInitDefaultMem((mm_addr)soundbank_bin);
  mmLoad(MOD_FLATOUTLIES);
  //  mmStart(MOD_FLATOULIES, MM_PLAY_LOOP); 

  mmLoadEffect(SFX_HIT);
  mmLoadEffect(SFX_YAAHOOO);
}

void play_sound_success(){
  mmEffectEx(&sfx_yahooo);
}

void play_sound_select(){
  mmEffectEx(&sfx_hit);
}

void play_sound_trash(){
  mmEffectEx(&sfx_hit);
}

void play_sound_move_list(){
  mmEffectEx(&sfx_hit);
}
