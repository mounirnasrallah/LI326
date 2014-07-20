#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/include.h"

list* create_list(){
  list* _list = (list*)malloc(sizeof(list));
  _list->size = 0;
  _list->first = NULL;
  _list->end = NULL;
  return _list;
}


void add_element_list(list* _list,int _element){
  
  element_list* last_element = _list->end;
  element_list* new_element = (element_list*)malloc(sizeof(element_list));
  new_element->element = _element;

  last_element->next = new_element;
  new_element->prev = last_element;

  _list->end = new_element;
 
  _list->size++;

}


void init_list(list* _list){
  int i;
  for(i=1;i<=NUMBER_SPRITE_START;i++){
    add_element_list(_list,i);
  }
}

element_list* access(list* _list,int a){
 
  int i;
  element_list* elm = _list->first;
  
  for(i=0;( (i < a) && (i < _list->size));i++){
    elm = elm->next;
  }
  
  return elm;
}
