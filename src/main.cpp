
#include <stdio.h>

#include "../include/list_realize.h"
#include "../include/utilities.h"

int main(int argc, char const *argv[])
{
    list my_list = {};

    List_construct(&my_list);

    List_push_front(&my_list, 10);
    List_push_front(&my_list, 20);
    List_push_front(&my_list, 30);
    Dump(&my_list, 3);
    List_insert(&my_list, 2, 50);

    Dump(&my_list, 4);

    List_push_front(&my_list, 60);
    List_push_front(&my_list, 70);

    Dump(&my_list, 6);

    List_push_front(&my_list, 80);
    List_delete(&my_list, 2);

    Dump(&my_list, 6);

    List_push_front(&my_list, 90);
    
    Dump(&my_list, 7);    
    
    List_destruct(&my_list);

    Html_dump(my_list.n_dumps);

    printf("OK\n");

    return 0;
}
