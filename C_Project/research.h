#ifndef C_PROJECT_RESEARCH_H
#define C_PROJECT_RESEARCH_H

//Link with the remainder of the program
#include "list.h"


//FUNCTIONS

//function searching a value at level 0
t_d_cell * search0(t_d_list, int);

//function searching a value using all levels
t_d_cell * general_search(t_d_list list, int value);

#endif //C_PROJECT_RESEARCH_H
