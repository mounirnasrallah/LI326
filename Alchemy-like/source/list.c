
typedef struct _element_list{
  int element;
  struct _list_elements* next;
  struct _list_elements* prev;
} element_list;

typedef struct _list{
  int size;
  element_list* first;
  element_list* end;
} list;


void init_list(list* _list){
  _list->size = 0;
  _list->first = NULL;
  _list->end = NULL;
}


void add_element_list(list* _list,int element){
  
  element_list* last_element = _list->end;
  element_list* new_element = malloc(sizeof(element_list));
  new_element = element;

  last_element->next = new_element;
  new_element->prev = last_element;

  _list->end = new_element;

}

