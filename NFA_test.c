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
  //NFA that recognizes any string ending in 'man'
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

  IntSet nothing = IntSet_new();

  NFA_add_transition_all(man, 3, zero); //initializing the intset array
  NFA_add_transition_all(man, 2, zero);
  NFA_add_transition_all(man, 1, zero);
  NFA_add_transition_all(man, 0, zero);

  NFA_add_transition(man, 0, 'm', zero_one); //m always goes to state 1
  NFA_add_transition(man, 1, 'a', two);
  NFA_add_transition(man, 2, 'n', three);

  NFA_set_accepting(man, 3);

  NFA_print(man);

  //Automaton_tester(man);

  free(man);
  //NFA that recognizes any string with more w's,a's,s's,h's,i's,n's,t's, or o's than the string 'Washington'
  NFA washington = NFA_new(12);
  NFA_set_description(washington, "This automata recognizes any string with more w's,a's,s's,t's,h's,i's,n's, or 's than the String 'Washington'");
  NFA_set_accepting(washington, 11);

  IntSet four = IntSet_new();
  IntSet_add(four, 4);
  IntSet five = IntSet_new();
  IntSet_add(five, 5);
  IntSet six = IntSet_new();
  IntSet_add(six, 6);
  IntSet seven = IntSet_new();
  IntSet_add(seven, 7);
  IntSet eight = IntSet_new();
  IntSet_add(eight, 8);
  IntSet nine = IntSet_new();
  IntSet_add(nine, 9);
  IntSet ten = IntSet_new();
  IntSet_add(ten, 10);
  IntSet eleven = IntSet_new();
  IntSet_add(eleven, 11);


  IntSet zero_two = IntSet_new();
  IntSet_add(zero_two, 0);
  IntSet_add(zero_two, 2);
  IntSet zero_three = IntSet_new();
  IntSet_add(zero_three, 0);
  IntSet_add(zero_three, 3);
  IntSet zero_four = IntSet_new();
  IntSet_add(zero_four, 0);
  IntSet_add(zero_four, 4);
  IntSet zero_five = IntSet_new();
  IntSet_add(zero_five, 0);
  IntSet_add(zero_five, 5);
  IntSet zero_six = IntSet_new();
  IntSet_add(zero_six, 0);
  IntSet_add(zero_six, 6);
  IntSet zero_seven = IntSet_new();
  IntSet_add(zero_seven, 0);
  IntSet_add(zero_seven, 7);
  IntSet zero_eight = IntSet_new();
  IntSet_add(zero_eight, 0);
  IntSet_add(zero_eight, 8);
  IntSet zero_nine = IntSet_new();
  IntSet_add(zero_nine, 0);
  IntSet_add(zero_nine, 9);

  NFA_add_transition_all(washington, 0, zero);
  NFA_add_transition(washington, 0, 'a', zero_one);
  NFA_add_transition(washington, 0, 'g', zero_two);
  NFA_add_transition(washington, 0, 'h', zero_three);
  NFA_add_transition(washington, 0, 'i', zero_four);
  NFA_add_transition(washington, 0, 'o', zero_five);
  NFA_add_transition(washington, 0, 's', zero_six);
  NFA_add_transition(washington, 0, 't', zero_seven);
  NFA_add_transition(washington, 0, 'w', zero_eight);
  NFA_add_transition(washington, 0, 'n', zero_nine);

  NFA_add_transition_all(washington, 1, one);
  NFA_add_transition(washington, 1, 'a', eleven);

  NFA_add_transition_all(washington, 2, two);
  NFA_add_transition(washington, 2, 'g', eleven);

  NFA_add_transition_all(washington, 3, three);
  NFA_add_transition(washington, 3, 'h', eleven);

  NFA_add_transition_all(washington, 4, four);
  NFA_add_transition(washington, 4, 'i', eleven);

  NFA_add_transition_all(washington, 5, five);
  NFA_add_transition(washington, 5, 'o', eleven);

  NFA_add_transition_all(washington, 6, six);
  NFA_add_transition(washington, 6, 's', eleven);

  NFA_add_transition_all(washington, 7, seven);
  NFA_add_transition(washington, 7, 't', eleven);

  NFA_add_transition_all(washington, 8, eight);
  NFA_add_transition(washington, 8, 'w', eleven);

  NFA_add_transition_all(washington, 9, nine);
  NFA_add_transition(washington, 9, 'n', ten);

  NFA_add_transition_all(washington, 10, ten);
  NFA_add_transition(washington, 10, 'n', eleven);

  NFA_add_transition_all(washington, 11, eleven);

  Automaton_tester(washington);

  free(washington);

  //nfa that recognizes strings ending in .com,.edu, or .org. Meant to find valid webadresses

  NFA web = NFA_new(13);
  NFA_set_description(web, "This automaton recognizes strings that end in '.com','.org', or '.edu'. It finds strings ending in valid top-level-domains.");
  NFA_set_accepting(web, 4);
  NFA_set_accepting(web, 8);
  NFA_set_accepting(web, 12);

  IntSet zero_one_five_nine = IntSet_new();
  IntSet_add(zero_one_five_nine, 0);
  IntSet_add(zero_one_five_nine, 1);
  IntSet_add(zero_one_five_nine, 5);
  IntSet_add(zero_one_five_nine, 9);
  IntSet twelve = IntSet_new();
  IntSet_add(twelve, 12);



 NFA_add_transition_all(web, 0, zero);
 NFA_add_transition_all(web, 1, nothing);
 NFA_add_transition_all(web, 2, nothing);
 NFA_add_transition_all(web, 3, nothing);
 NFA_add_transition_all(web, 4, nothing);
 NFA_add_transition_all(web, 5, nothing);
 NFA_add_transition_all(web, 6, nothing);
 NFA_add_transition_all(web, 7, nothing);
 NFA_add_transition_all(web, 8, nothing);
 NFA_add_transition_all(web, 9, nothing);
 NFA_add_transition_all(web, 10, nothing);
 NFA_add_transition_all(web, 11, nothing);
 NFA_add_transition_all(web, 12, nothing);


 NFA_add_transition(web, 0, '.', zero_one_five_nine);
 NFA_add_transition(web, 1, 'c', two);
 NFA_add_transition(web, 2, 'o', three);
 NFA_add_transition(web, 3, 'm', four);
 NFA_add_transition(web, 5, 'e', six);
 NFA_add_transition(web, 6, 'd', seven);
 NFA_add_transition(web, 7, 'u', eight);
 NFA_add_transition(web, 9, 'o', ten);
 NFA_add_transition(web, 10, 'r', eleven);
 NFA_add_transition(web, 11, 'g', twelve);

 Automaton_tester(web);

 free(web);

  return 0;
}
