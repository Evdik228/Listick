
#include <stdio.h>
#include <stdlib.h>

#include "../include/list_realize.h"
#include "../include/utilities.h"


#define IS_ERR()  if (Verifier(my_list) != OKEY) { return ERROR; }

int Find_empty_position(list * my_list) {

    if (my_list->list_max_size == my_list->list_size) {
        return -1;
    }

    for (int i = 0; i <  my_list->list_max_size; i++) {
        if (my_list->list_data[i] == -1) {
            return i;
        }
    }
    return -1;
}

int Find_anchor_position(list * my_list, int elem_num) {
    int position = 0;

    for (int ip = 0; ip < my_list->list_size; ip++) {

        if (ip == elem_num) {

            return position;
        }

        position = my_list->list_next[position];

    }
    return -1;
}


error_types  List_clear(list * my_list) {

    IS_ERR();

    my_list->last_pop_element = -1;
    my_list->list_size = 1;

    for (int i = 1; i < my_list->list_max_size; i++) {

        *(my_list->list_data + i) = -1;
        *(my_list->list_next + i) = -1;
        *(my_list->list_prev + i) = -1;
    }

    *(my_list->list_data) = 0;
    *(my_list->list_next) = 0;
    *(my_list->list_prev) = 0;         
                                    
    IS_ERR();               

    return OKEY;
}

error_types List_construct(list * my_list) {

    IS_ERR();

    my_list->list_data = (list_elem_t *)calloc(my_list->list_max_size, sizeof(list_elem_t));
    my_list->list_next = (list_elem_t *)calloc(my_list->list_max_size, sizeof(list_elem_t));
    my_list->list_prev = (list_elem_t *)calloc(my_list->list_max_size, sizeof(list_elem_t));
    
    List_clear(my_list);

    IS_ERR();

    return OKEY;
    
}

error_types List_destruct(list * my_list) {

    IS_ERR();

    List_clear(my_list);

    free(my_list->list_data);
    free(my_list->list_next);
    free(my_list->list_prev);

    IS_ERR();

    return OKEY;
}

error_types List_push_front(list * my_list, list_elem_t elem) {

    IS_ERR(); // insert tail??

    if (my_list->list_size == my_list->list_max_size){
        printf("ERR: push unreal, list is full!");
    }

    my_list->list_size++;

    int position = Find_empty_position(my_list);
    
    my_list->list_data[position] = elem;

    my_list->list_prev[position] = my_list->list_prev[0]; 

    my_list->list_next[position] = 0;

    my_list->list_prev[0] = position;

    my_list->list_next[my_list->list_prev[position]] = position;

    IS_ERR();

    return OKEY;
}

error_types List_pop_back(list * my_list) {

    IS_ERR();

    if (my_list->list_size == 1){
        printf("ERR: pop unreal, list is empty!\n");
    }

    my_list->list_size--;

    int position = my_list->list_prev[0];
    my_list->last_pop_element = my_list->list_data[position];

    my_list->list_next[my_list->list_prev[position]] = 0;

    my_list->list_data[position] = -1;
    my_list->list_next[position] = -1;
    my_list->list_prev[position] = -1;

    IS_ERR();

    return OKEY;
}

error_types List_insert(list * my_list, size_t elem_num, list_elem_t elem) {

    IS_ERR();

    int anchor = Find_anchor_position(my_list, elem_num);
    int position = Find_empty_position(my_list);

    if (anchor == -1) {

        printf("ERR: position not detect!\n");
        return ERROR;
    }

    my_list->list_data[position] = elem;

    my_list->list_next[position] = my_list->list_next[anchor];
    my_list->list_prev[position] = anchor;

    my_list->list_prev[my_list->list_next[anchor]] = position;
    
    my_list->list_next[anchor] = position;

    my_list->list_size++;

    IS_ERR();

    return OKEY;
}

error_types List_delete(list * my_list, size_t position) {

    IS_ERR();

    my_list->last_pop_element = my_list->list_data[position];

    list_elem_t position_next = my_list->list_next[position];
    list_elem_t position_prev = my_list->list_prev[position];

    my_list->list_data[position] = -1;
    my_list->list_next[position] = -1;
    my_list->list_prev[position] = -1;

    my_list->list_next[position_prev] = position_next;
    my_list->list_prev[position_next] = position_prev;

    my_list->list_size--;

    IS_ERR();

    return OKEY;
}

error_types List_Swap(list * my_list, size_t elem_num_1, size_t elem_num_2) {

    IS_ERR();

    //poca ne gotova; 
    
    IS_ERR();

    return OKEY;
}