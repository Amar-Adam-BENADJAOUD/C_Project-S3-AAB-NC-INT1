#include "list.h"

t_d_cell * create_cell(int x, int n){
    t_d_cell * c = (t_d_cell *) malloc(sizeof(t_d_cell)); //allocation of memory
    c->value = x; //initialization
    c->n_level = n; //definition of the number of level
    c->next = (t_d_cell **) malloc(sizeof(t_d_cell *) * c->n_level); //allocation of memory for the list of addresses
    for(int i = 0; i < c->n_level; ++i)
        c->next[i] = NULL; //initialization of the element of the list of addresses
    return c;
}

t_d_list create_empty_list(int n){
    t_d_list L;
    L.n_level = n; //definition of the number maximum of level in the cell of the list
    L.head = (t_d_cell **) malloc(sizeof(t_d_list *) * L.n_level); //allocation of memory for the list of heads
    for(int i = 0; i < L.n_level; ++i)
        L.head[i] = NULL; //initialization of the element of the list of heads
    return L;
}

t_d_list create_s_list(int n) {
    t_d_list L = create_empty_list(n); //initialization of the list
    int n_elements = (int) pow(2, n) - 1; //definition of the number of element in the list
    for( int i = n_elements; i>0; i--) {
        int cellLevel = 0;
        for( int j = 1; j<n; j++)
            if(i % (int)pow(2, j) == 0)
                cellLevel++;
        init_head(&L, create_cell(i, n)); //insertion at the head
    }
    return L;
}

void init_head(t_d_list * L, t_d_cell * c){
    if(c->n_level > L->n_level) //check if the number of levels are not absurd
        printf("Error size of cell"); //Error message
    else
        //insertion
        for(int i = 0; i < c->n_level; ++i) {
            c->next[i] = L->head[i];
            L->head[i] = c;
        }
    return;
}

void insert_cell(t_d_list * L, int x, int n) {
    if (n < 0)
        n = 0; //adjustment

    if (n >= L->n_level)
        n = L->n_level - 1; //adjustment

    t_d_cell * c = create_cell(x, n); //creation of the new cell
    t_d_cell * tmp = L->head[0]; //preparation of cursor
    t_d_cell *prev = NULL; //preparation of second cursor

    //empty list case
    init_head(L, c);
    if (tmp == NULL || tmp->value >= x) {
        init_head(L, c);
        return;
    }

    for ( int i = n; i >= 0; i--) {
        tmp = L->head[i]; //work on level i
        prev = NULL;

        //Finding the right place
        while (tmp != NULL && tmp->value < x) {
            prev = tmp;
            tmp = tmp->next[i];
        }

        //insertion
        if (prev == NULL) {
            c->next[i] = L->head[i];
            L->head[i] = c;
        } else {
            c->next[i] = prev->next[i];
            prev->next[i] = c;
        }
    }
}

void display_cell(t_d_cell * c, int n){
    while (c != NULL){
        printf("[%d]-->", c->value);
        c = c->next[n];
    }
    printf("[end]");
}

void display_level(t_d_list L, int n){
    printf("Level_%d { ", n);
    display_cell(L.head[n], n);
    printf(" }");
}

void display_all_levels(t_d_list L){
    for(int i=0; i < L.n_level; i++) {
        display_level(L, i);
        printf("\n");
    }
}
