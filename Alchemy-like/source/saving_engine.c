
#include <nds.h>
#include <fat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/saving_engine.h"


void list_directory() {

  consoleDemoInit();
  if (fatInitDefault()) {

    DIR *pdir;
    struct dirent *pent;

    pdir=opendir("/");

    if (pdir){
      while ((pent=readdir(pdir))!=NULL) {
	if(strcmp(".", pent->d_name) == 0 || strcmp("..", pent->d_name) == 0)
	  continue;
	if(pent->d_type == DT_DIR)
	  iprintf("[%s]\n", pent->d_name);
	else
	  iprintf("%s\n", pent->d_name);
      }
      closedir(pdir);
    } else {
      iprintf ("opendir() failure; terminating\n");
    }

  } else {
    iprintf("fatInitDefault failure: terminating\n");
  }

  while(1) {
    swiWaitForVBlank();
  }

}


unsigned char init_saving_engine(){
  list_directory();
  
}

void list_load_file(char* path){
}

unsigned char save_file(){
  return 3;
}
