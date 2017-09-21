/*
Author: Danielle DeLooze
Date: 9/20/2017
Purpose: Translate a NFA to a DFA
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"
#include "nfa.h"
#include "IntSet.h"
#include "LinkedList.h"


DFA translate(NFA nfa){
  LinkedList* list = LinkedList_new();

  IntSet zero = IntSet_new();
  IntSet_add(zero, 0);

  LinkedList_add_at_front(list, zero);
  int index = -1;
  int original_size = 1;


do{
  original_size = LinkedList_get_size(list);
  index++;
  IntSet subset = LinkedList_element_at(list, index);

  for(int i = 0; i <128; i++){
    IntSetIterator subset_iterator = IntSet_iterator(subset);
    IntSet temp = IntSet_new();
    while(IntSetIterator_has_next(subset_iterator)){
      IntSet_union(temp, NFA_get_transitions(nfa, IntSetIterator_next(subset_iterator), i));
    }
    if(!(LinkedList_contains(list, temp))){
      LinkedList_add_at_end(list, temp);
    }
  }

}while((LinkedList_get_size(list) != original_size) && ((index + 1) != LinkedList_get_size(list)));

DFA dfa = DFA_new(LinkedList_get_size(list));

LinkedListIterator* accepting_iterator = LinkedList_iterator(list);
int incr = 0;
while(LinkedListIterator_has_next(accepting_iterator)){
  IntSetIterator accepting_states = IntSet_iterator(NFA_get_accepting(nfa));
  IntSet temp = LinkedListIterator_next(accepting_iterator);
  while(IntSetIterator_has_next(accepting_states)){
    if(IntSet_contains(temp, IntSetIterator_next(accepting_states))){
      DFA_set_accepting(dfa, incr, true);
    }
  }
  incr++;
}

DFA_set_description(dfa, NFA_get_description(nfa));

for(int index = 0; index < DFA_get_size(dfa); index++){
  IntSet subset = LinkedList_element_at(list, index);
  for(int i = 0; i <128; i++){
    IntSetIterator subset_iterator = IntSet_iterator(subset);
    IntSet temp = IntSet_new();
    while(IntSetIterator_has_next(subset_iterator)){
      IntSet_union(temp, NFA_get_transitions(nfa, IntSetIterator_next(subset_iterator), i));
    }
    int current = 0;
    while(!IntSet_equals(temp, LinkedList_element_at(list, current))){
      current++;
    }
    char x = i;
    DFA_set_transition(dfa, index, x, current );
  }
}

return dfa;




/*
LinkedListIterator* iterator = LinkedList_iterator(list);
while(LinkedListIterator_has_next(iterator)){
  IntSet_print(LinkedListIterator_next(iterator));
}
*/
/*
free(iterator);
LinkedList_free(list, true);
*/
}
