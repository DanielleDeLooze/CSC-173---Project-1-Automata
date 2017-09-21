/*
Author: Danielle DeLooze
Date: 9/20/2017
Purpose: CSC 173 Project 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"
#include "nfa.h"
#include "IntSet.h"
#include "LinkedList.h"
#include "translate.h"

int main(int argc, char const *argv[]) {
  //DFA examples and testing
  DFA ab = DFA_new(3);
  for(int i = 0; i < 3; i++){ //if an incorrect input is entered that causes the automaton to fail, this will catch it
    DFA_set_transition_all(ab, i, -1);
  }
  DFA_set_transition(ab, 0, 'a', 1);
  DFA_set_transition(ab, 1, 'b', 2);
  DFA_set_accepting(ab, 2, true);
  DFA_set_description(ab, "This automaton recognizes the string 'ab'");
  Automaton_Tester(ab);

  free(ab);

  //Automaton that recognizes any string starting with 'ab'
  DFA start_ab = DFA_new(3);
  for(int i = 0; i < 3; i++){
    DFA_set_transition_all(start_ab, i, -1);
  }
  DFA_set_transition(start_ab, 0, 'a', 1);
  DFA_set_transition(start_ab, 1, 'b', 2);
  DFA_set_accepting(start_ab, 2, true);
  DFA_set_transition_all(start_ab, 2, 2);
  DFA_set_description(start_ab, "This automaton recognizes any string starting with 'ab'");
  Automaton_Tester(start_ab);
  free(start_ab);

  //Automaton that recognizes binary input with even number of 1's
  DFA even_ones = DFA_new(2);
  for(int i =0; i<2; i++){ //since 0 is accepting, we default everything but 1 and 0 to a false state
    DFA_set_transition_all(even_ones, i, -1);
  }
  DFA_set_transition(even_ones, 0, '1', 1);
  DFA_set_transition(even_ones, 1, '1', 0);
  DFA_set_transition(even_ones, 1, '0', 1);
  DFA_set_transition(even_ones, 0, '0', 0);
  DFA_set_accepting(even_ones, 0, true);
  DFA_set_description(even_ones, "This automaton recognizes a binary input with an even number of ones");
  Automaton_Tester(even_ones);
  free(even_ones);

  //Automaton that recognizes binary input with even number of 0's and 1's
  DFA even = DFA_new(4);
  for(int i = 0; i < 4; i++){
    DFA_set_transition_all(even, i, -1);
  }
  DFA_set_transition(even, 0, '1', 1);
  DFA_set_transition(even, 1, '1', 0);
  DFA_set_transition(even, 1, '0', 3);
  DFA_set_transition(even, 3, '0', 1);
  DFA_set_transition(even, 3, '1', 2);
  DFA_set_transition(even, 2, '1', 3);
  DFA_set_transition(even, 2, '0', 0);
  DFA_set_transition(even, 0, '0', 2);
  DFA_set_accepting(even, 0, true);
  DFA_set_description(even, "This automaton recognizes a binary input with an even number of 1's and 0's");
  Automaton_Tester(even);
  free(even);

  //Automaton that regcognizes binary input that starts and ends with 1
  DFA ones = DFA_new(3);
  for(int i = 0; i < 3; i++){
    DFA_set_transition_all(ones, i, -1);
  }
  DFA_set_transition(ones, 0, '1', 1);
  DFA_set_transition(ones, 1, '0', 1);
  DFA_set_transition(ones, 1, '1', 2);
  DFA_set_transition(ones, 2, '0', 1);
  DFA_set_transition(ones, 2, '1', 2);
  DFA_set_accepting(ones, 2, true);
  DFA_set_description(ones, "This automaton recognizes a binary input that starts and ends with a 1");
  Automaton_Tester(ones);
  free(ones);


  //NFA example and testing
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

  Automaton_tester(man);


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

 //using the translate function
 DFA man_dfa = translate(man);
 Automaton_Tester(man_dfa);

  return 0;
}
