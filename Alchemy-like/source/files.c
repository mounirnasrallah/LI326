#include <nds.h>

#include <filesystem.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h> 

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include <limits.h>

#include <fcntl.h>


/* On récupere la taille de l'index  */
int size_index(int fd){
  
  int size;
  off_t current_position = lseek(fd,0,SEEK_CUR);
  lseek(fd,0,SEEK_SET);
  read(fd,&size_index,sizeof(int));
  lseek(fd,current_position,SEEK_SET);

  return size;
}

/**
 * Ouvre un fichier indexe.
 * Fichier cree ou ecrase => ecrire la taille de l'index en debut de fichier
 * Sinon => lire la taille de l'index en debut de fichier
 * path   nom du fichier a ouvrir
 * flags  mode d'ouverture du fichier
 * ind    taille de la structure index (ne sert que si le fichier est cree ou ecrase)
 * mode   droits d'acces au fichier
 * Renvoie le descripteur du fichier ouvert, -1 en cas de pb.
 */
int indopen(const char *path, int flags, int ind, mode_t mode){

  int fd;
  struct stat st;
  char action = 0; // 1 ecriture | 0 lecture

  // On essaye de récupérer les données du fichier
  int stat_file = stat(path,&st);

  // Si le fichier n'existe pas ou si l'on veut le vider alors on ecrit.
  if( ((stat_file >= 0) && (flags == O_TRUNC)) || (stat_file < 0)){
    action = 1;
  }

  if( (fd = open(path, flags, mode)) < 0)
    return -1;

  // Si le fichier est ouvert en mode ajout, on met la tête de lecture au début du fichier
  // puis on lit la taille de l'index
  if(flags == O_APPEND){
    lseek(fd,0,SEEK_SET);
    action = 0;
  }

  if(action){
    write(fd,&ind,sizeof(int)); // On ecrit la taille de l'index en début de fichier 
  }
  else{
    read(fd,NULL,sizeof(int)); // On lit la taille de l'index en début de fichier 
  }

  return fd;  // On retourne le descripteur de fichier

}



/**
 * Ferme un fichier indexe.
 * fd  le descripteur du fichier a fermer
 * Renvoie -1 en cas de pb, 0 sinon.
 */
int indclose(int fd){
  return close(fd);
}

/**
 * Lit des donnees dans un fichier indexe.
 *fd      descripteur du fichier lu
 *buf     ptr vers les donnees lues
 *nbytes  nb d'octets a lire 
 *(nbytes doit etre >= a la taille d'index)
 * Renvoie le nb d'octets lus, 0 si fin de fichier, -1 en cas de pb.
 */
ssize_t indread(int fd, void *buf, size_t nbytes){

  int size = size_index(fd);

  if((int)nbytes < size){
    return -1;
  }

  return read(fd, buf,nbytes);

}

/**
 * Ecrit des donnees dans un fichier indexe.
 *fddescripteur du fichier modifie
 *buf     ptr vers les donnees la ecrire
 *nbytes  nb d'octets a ecrire 
 *(nbytes doit etre >= a la taille d'index)
 * Renvoie le nb d'octets ecrits, -1 en cas de pb.
 */
ssize_t indwrite(int fd, const void *buf, size_t nbytes){
  
  int size = size_index(fd);

  if((int)nbytes < size){
    return -1;
  }

  return write(fd,buf,nbytes);

}

/**
 * Deplace le curseur dans un fichier indexe.
 *fddescripteur du fichier
 *offset  deplacement a effectuer (en nb de structures index)
 *whence  positionnement initial du curseur 
 * Renvoie le deplacement effectif du curseur (en nb d'octets), -1 en cas de pb.
 */
off_t indlseek(int fd, off_t offset, int whence){
  
  int position;
  int size_element = size_index(fd);

  switch(whence){
  case SEEK_SET: // Début de fichier
    position = (offset *  size_element) + sizeof(int);
    break;
  case SEEK_CUR:
    position = (offset * size_element);
    break;
  case SEEK_END:
    position = (offset * size_element);
    break; 
  }  
  
  return lseek(fd,position,whence); 
}
