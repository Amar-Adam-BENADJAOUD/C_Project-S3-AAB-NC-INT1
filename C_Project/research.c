#include "research.h"

t_d_cell * search0(t_d_list list, int value) {
    //checking if the list is empty
    if (list.head == NULL)
        return NULL;
    t_d_cell * tmp = list.head[0];

    //dicotomic research algorithm
    do {
        if (tmp->value == value)
            return tmp;
        if (tmp->value > value)
            break;
        else
            tmp = tmp->next[0];
    } while (tmp != NULL);

    return NULL;
}

t_d_cell *  general_search(t_d_list L, int val){
    //checking if the list is empty
    if (L.head == NULL)
        return NULL;

    //initialization
    int n = L.n_level-1;
    t_d_cell * tmp;

    //finding the highest non-NULL element
    do {
        n--;
        tmp = L.head[n];
    } while (tmp == NULL && n >= 0);

    if (tmp == NULL)
        return NULL;

    //dicotomic research
    do
    {
        if (tmp->value == val)
            return tmp;
        if (n > 0 && tmp->value > val)
            tmp = L.head[--n];
        else
            tmp = tmp->next[0];
    } while (tmp != NULL);

    return NULL;
}
