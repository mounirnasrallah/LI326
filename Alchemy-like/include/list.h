#ifndef LIST_STRUCT
#define LIST_STRUCT

#include <stdlib.h>

typedef struct _element_list{
  int element;
  struct _element_list* next;
  struct _element_list* prev;
} element_list;

typedef struct _list{
  int size;
  element_list* first;
  element_list* end;
} list;

extern list* list_elm;

list* create_list();
void add_element_list(list* _list,int _element);
void init_list(list* _list);
element_list* access(list* _list,int a);
#endif
