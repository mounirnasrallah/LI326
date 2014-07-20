#include "../include/alchemy_engine.h"


/* alchemyMatrix contient les informations sur les combinaisons possibles
  char pour des soucis d'espace mémoire, et que l'on aura pas plus de 256 objets. */
char alchemyMatirx[10][10] ={
  0,0,0,0,0, 0,0,0,0,0,
  0,0,0,0,0, 6,0,0,0,0,
  0,0,0,0,0, 0,0,0,0,0,
  0,0,0,0,0, 0,7,8,0,0,
  0,0,0,0,0, 0,0,0,0,0,

  0,6,0,0,0, 0,0,0,0,0,
  0,0,0,7,0, 0,0,0,0,0,
  0,0,0,8,0, 0,0,0,0,0,
  0,0,0,0,0, 0,0,0,0,0,
  0,0,0,0,0, 0,0,0,0,0,
}; 

char combine(int a, int b){
  // Securité ?? bufferoverflow
  if(a<MAX_SIZE_COMBINAISONS && b<MAX_SIZE_COMBINAISONS && a>=0 && a>=0){
    return alchemyMatirx[a][b];
  }
  else{
    return 0;
  }
}

void used_combinaison(int a, int b){
  alchemyMatirx[a][b]=0; 
  alchemyMatirx[b][a]=0;
}



