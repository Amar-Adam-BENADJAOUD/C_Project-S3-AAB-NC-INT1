#ifndef C_PROJECT_FILE_H
#define C_PROJECT_FILE_H

//Needed libraries
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include <time.h>


//Needed structures

//Structure of the cell
typedef struct s_d_cell {
    int value; //stored value
    int n_level; //number of levels in the cell
    struct s_d_cell ** next; //list of pointers on the levels of the next cell
} t_d_cell;

//Structure of the list
typedef struct s_d_list {
    t_d_cell ** head; //list of pointers on the levels of the first cell
    int n_level; //number of the maximum levels in the cell of the list
} t_d_list;


//FUNCTIONS

//creation functions
t_d_cell * create_cell(int, int);
t_d_list create_empty_list(int);
t_d_list create_s_list(int);

//insertion functions
void init_head(t_d_list *, t_d_cell *);
void insert_cell(t_d_list *, int, int);

//display functions
void display_cell(t_d_cell *, int);
void display_level(t_d_list, int);
void display_all_levels(t_d_list);


#endif //C_PROJECT_FILE_H
