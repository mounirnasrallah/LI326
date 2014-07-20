#include <nds.h>
#include <../include/3D_engine.h>
#include <../include/ocean_bin.h>


void gestion_3D(int a){

  switch(a){
  
  case 0:
    break;
  
  case 1:
    break;
  
  case 2:
    break;
    
  case 3:
    break;
    
  case 4:
    break;
    
  case 5:
    break;
   
  case 6:
    ocean();
    break;
    
  case 7:
    break;
  }       

}

void ocean(void){

  float rotateX = 0.0;
  float rotateY = 0.0;
  int i;

  videoSetMode(MODE_0_3D);

  u8* ocean;

  glInit();

  glEnable(GL_ANTIALIAS);

  glClearColor(255,255,255,31);
  glClearPolyID(63);
  glClearDepth(0x7FFF);

  glViewport(0,0,255,191);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 256.0 / 192.0, 0.1, 10);

  gluLookAt(
            -2,0,1.0,
	    2.13176,-10.71837,-2.0,
	    0.0, -0.4, 1.0);

  glMaterialf(GL_AMBIENT, RGB15(136,203,255));
  glMaterialf(GL_DIFFUSE, RGB15(235,245,255));
  glMaterialf(GL_SPECULAR, RGB15(255,255,255));
  glMaterialf(GL_EMISSION, RGB15(0,0,0));

  glLight(0, RGB15(31,31,31) , 0, floattov10(-1.0),0);


  glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0);

   for(i=0;i<145;i++){
   glRotateXi(rotateX++);
   glRotateYi(rotateY++);
  }


  for(i=0;i<80;i++){
  
    glTranslatef32(floattof32(0.05),0,0);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glCallList((u32*)ocean_bin);

    glPopMatrix(1);

    glFlush(0);

    swiWaitForVBlank();

  }

}




