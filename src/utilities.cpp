
#include<stdlib.h>

#include "../include/list_realize.h"
#include "../include/utilities.h"

#define  ERR(err) Dump(my_list, 1); return err;

error_types Verifier(list * my_list) {

    if (my_list->list_next == NULL && my_list->list_data == NULL && my_list->list_prev == NULL && my_list->list_size == 1) {
        return OKEY;
    }
    
    else if (my_list->list_data == NULL || my_list->list_next == NULL || my_list->list_prev == NULL) {

        ERR(ZERO_POINTER);

    }
    else if (my_list->list_size > my_list->list_max_size) {

        ERR(LIST_OVERFLOW);

    } 

    return OKEY;   
}


void Dump_vertices(list * my_list, FILE * file_f, int anchor_position) {

    for (int id = 0; id < my_list->list_max_size; id++) {

        if (id == 0) {

            fprintf(file_f, "node%d[shape = Mrecord; style = filled; fillcolor = \"#07f5c6\"; color = \"#6d0dd4\"; fontcolor = \"#000055\"; ", id);
            fprintf(file_f, "label = \" {id: %d} | {value: %d} | {next: %d} | {prev: %d}\"]; ", id, my_list->list_data[id], 
                                                                                                    my_list->list_next[id], 
                                                                                                    my_list->list_prev[id]);
            fprintf(file_f, "\n");

            fprintf(file_f, "node01[shape = box3d; style = filled; fillcolor = \"#000055\"; color = \"#07f5c6\"; fontcolor = \"#07f5c6\"; ");
            fprintf(file_f, "label = \" Head/Tail elem\"]; ");
            fprintf(file_f, "\n");

        } 
        else if (id == anchor_position) {

            fprintf(file_f, "node%d[shape = Mrecord; style = filled; fillcolor = \"#eacd3b\"; color = \"#6d0dd4\"; fontcolor = \"#000055\"; ", id);
            fprintf(file_f, "label = \" {id: %d} | {value: %d} | {next: %d} | {prev: %d}\"]; ", id, my_list->list_data[id], 
                                                                                        my_list->list_next[id], 
                                                                                        my_list->list_prev[id]);
            fprintf(file_f, "\n");

            fprintf(file_f, "node00[shape = box3d; style = filled; fillcolor = \"#000055\"; color = \"#eacd3b\"; fontcolor = \"#eacd3b\"; ");
            fprintf(file_f, "label = \" Anchor elem\"]; ");
            fprintf(file_f, "\n");

        } else {

            if(my_list->list_data[id] == -1) {
            continue;
        }

        fprintf(file_f, "node%d[shape = Mrecord; style = bold; fillcolor = \"#0000aa\"; color = \"#55ffff\"; fontcolor = \"#55ffff\"; ", id);
        fprintf(file_f, "label = \" {id: %d} | {value: %d} | {next: %d} | {prev: %d}\"]; ", id, my_list->list_data[id], 
                                                                                                my_list->list_next[id], 
                                                                                                my_list->list_prev[id]);
        fprintf(file_f, "\n");

        }

    }

    fprintf(file_f, "\n");

}

void Dump_big_ribs(list * my_list, FILE * file_f) {

    int id = 0;
    int position = 0;
    int position_next = 0;

    while( id < my_list->list_size - 1) {

        position_next++;
        
        while (my_list->list_data[position_next] == -1) {
            position_next++;
        }

        fprintf(file_f, "node%d -> node%d [color = \"#0000aa\"; weight = 1000;];\n", position, (position_next));

        position = position_next;
        id++;
    }

    fprintf(file_f, "\n");
}


void Dump_ribs_next(list * my_list, FILE * file_f) {

    int position = 0;

    for (int id = 0; id < my_list->list_size; id++) {

        fprintf(file_f, "node%d -> node%d [color = \"#18e41b\" ;style=\"bold\";  weight = 0;];\n", position, my_list->list_next[position]);

        position = my_list->list_next[position];
    }
    fprintf(file_f, "\n");
}

void Dump_ribs_prev(list * my_list, FILE * file_f) {

     int position = 0;

    for (int id = 0; id < my_list->list_size; id++) {
        
         fprintf(file_f, "node%d -> node%d [color = \"#ff5555\" ; style=\"bold\"; weight = 0; constraint = false;];\n", position, my_list->list_prev[position]);

         position = my_list->list_next[position];
    }   

    fprintf(file_f, "\n");
}

void Dump(list * my_list, int anchor_num) {

    int anchor_position = Find_anchor_position(my_list, anchor_num);

    char file_name[25] = ""; 
    
    snprintf(file_name, 25, "./debug/dots/graph%d.dot", my_list->n_dumps);

    FILE * file_f = fopen(file_name, "w");    //check if open 

    fprintf(file_f, "digraph List {\n");
    fprintf(file_f, "  graph [\n");
    fprintf(file_f, "  charset = \"UTF-8\";\n  label = \"like faaar list\"\n");
    fprintf(file_f, "    bgcolor   = \"#0000aa\", \nfontcolor = white, \nfontsize  = 18, \n style = \"rounded\",   \n");
    fprintf(file_f, "rankdir = LR, \nsplines = ortho  \nranksep = 1.0, \nnodesep = 0.9\n");
    fprintf(file_f, " ];\n");

    Dump_vertices(my_list, file_f, anchor_position);



    Dump_big_ribs(my_list, file_f);

    Dump_ribs_next(my_list, file_f);

    Dump_ribs_prev(my_list, file_f);

    fprintf(file_f, "node00 -> node%d [color = \"#eacd3b\" ; style=\"bold\"; weight = 0;];\n", anchor_position);
    fprintf(file_f, "node01 -> node0  [color = \"#07f5c6\" ; style=\"bold\"; weight = 0;];\n");

    fprintf(file_f, "}\n");

    fclose(file_f);

    char command[65] = "";

    snprintf(command, 65, "dot ./debug/dots/graph%d.dot -Tpng -o ./debug/img/graph%d.png\n", my_list->n_dumps, my_list->n_dumps);
    
    system((const char *)command);

    my_list->n_dumps++;

}

void Html_dump(int number_of_dumps) {

    FILE * file_f = fopen("log.html", "w");

    fprintf(file_f, "<!DOCTYPE html>\n"      
                    "<html lang=\"ru\">\n" 
                    "<head>\n"
                    "<meta charset=\"UTF-8\">\n"
                    "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\n"
                    "<title>List</title>\n"
                    "<link rel=\"stylesheet\" href=\"log.css\">\n"
                    "</head>\n"
                    "<body>\n"
                    //"<h1>DED CVADROBER</h1>\n"
                    "<div class=\"flex-container\">\n");


    for ( int i = 0; i < number_of_dumps; i++ ) {

        fprintf(file_f, "<div class = \"elem\">" 
                        "<img src = \"./debug/img/graph%d.png\" height = \"200\">\n", i);

        fprintf(file_f, "<div class = \"text\">" 
                        "dump number %d" 
                        "</div>\n"
                        "</div>\n\n", i);
        }

    fclose(file_f);

}
