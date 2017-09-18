/*
Author: Danielle DeLooze
Date: 9/17/2017
Purpose: Test NFA implementation
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "IntSet.h"
#include "nfa.h"

int main(int argc, char **argv){

  NFA test = NFA_new(4);
  NFA_add_transition(test, 0, 'm', 0);

  NFA_print(test);




  return 0;
}
