#ifndef  LIST_REAL_H_
#define  LIST_REAL_H_

#include<stdio.h>

typedef int list_elem_t;

enum error_types {

    OKEY                = 0,
    ERROR               = 1,
    ZERO_POINTER        = 2,
    LIST_OVERFLOW       = 3,

};

struct list
{
    list_elem_t * list_data;
    list_elem_t * list_next;
    list_elem_t * list_prev;

    size_t list_max_size = 64; // TODO: const?
    size_t list_size = 1;

    list_elem_t last_pop_element = -1;

    size_t n_dumps = 0;

};

error_types List_construct(list * my_list);

error_types List_destruct(list * my_list); 

int Find_anchor_position(list * my_list, int elem_num); 

error_types List_push_front(list * my_list, list_elem_t elem);

error_types List_pop_back(list * my_list);

error_types List_insert(list * my_list, size_t elem_num, list_elem_t elem);

error_types List_delete(list * my_list, size_t elem_num);

error_types List_Swap(list * my_list, size_t elem_num_1, size_t elem_num_2);

#endif