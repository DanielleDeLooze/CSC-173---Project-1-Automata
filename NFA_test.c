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


void Automaton_tester(NFA nfa){
  printf("NFA Automaton Description: %s \n", NFA_get_description(nfa));
  char control = 'Y';

  while(control != 'N'){
    printf("Please enter the string you'd like to test: ");
    char input[50];
    scanf("%s", input);
    bool result = NFA_execute(nfa, input);
    printf("The string '%s' %s", input, result? "passes this automaton\n" : "fails this automation\n");
    printf("Enter 'N' to stop, 'Y' to continue: ");
    scanf(" %c", &control);
    printf("\n");
  }
}


int main(int argc, char **argv){

  NFA man = NFA_new(4);
  NFA_set_description(man, "This automaton will return true for any string ending with 'man'");

  IntSet zero = IntSet_new();
  IntSet_add(zero, 0);

  IntSet one = IntSet_new();
  IntSet_add(one, 1);

  IntSet two = IntSet_new();
  IntSet_add(two, 2);

  IntSet three = IntSet_new();
  IntSet_add(three, 3);

  IntSet zero_one = IntSet_new();
  IntSet_add(zero_one, 0);
  IntSet_add(zero_one, 1);

  //IntSet nothing = IntSet_new();

  NFA_add_transition_all(man, 3, zero); //initializing the intset array
  NFA_add_transition_all(man, 2, zero);
  NFA_add_transition_all(man, 1, zero);
  NFA_add_transition_all(man, 0, zero);

  NFA_add_transition(man, 0, 'm', zero_one); //m always goes to state 1
  NFA_add_transition(man, 1, 'a', two);
  NFA_add_transition(man, 2, 'n', three);

  NFA_set_accepting(man, 3);

  Automaton_tester(man);

  return 0;
}
