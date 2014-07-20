#include "../include/soundbank.h"
#include "../include/soundbank_bin.h"  


mm_sound_effect_sfx_hit = {
  {SFX_HIT},
  1024,
  0,
  255,
  255
};

mm_sound_effect_sfx_yahoo = {
  {SFX_YAHOO},
  1024,
  0,
  255,
  255
};


void init_sound_engine(){
  mmInitDefaultMem((mm_addr)soundbank_bin);
  mmLoad(MOD_FLATOUTLIES);
  // mmStart(MOD_FLATOULIES, MM_PLAY_LOOP); 

  mmLoadEffect(SFX_HIT);
  mmLoadEffect(SFX_YAHOO);
}

void play_sound(){
  mmEffectEx(&sfx_yahoo);
}
