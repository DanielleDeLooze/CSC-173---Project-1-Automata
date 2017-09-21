#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"
#include "nfa.h"
#include "IntSet.h"
#include "LinkedList.h"
#include "translate.h"


int main(int argc, char** argv){
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

  NFA_add_transition_all(man, 3, zero); //initializing the intset array
  NFA_add_transition_all(man, 2, zero);
  NFA_add_transition_all(man, 1, zero);
  NFA_add_transition_all(man, 0, zero);

  NFA_add_transition(man, 0, 'm', zero_one); //m always goes to state 1
  NFA_add_transition(man, 1, 'a', two);
  NFA_add_transition(man, 2, 'n', three);

  NFA_set_accepting(man, 3);

  DFA dfa = translate(man);
  Automaton_Tester(dfa);

  return 0;
}
