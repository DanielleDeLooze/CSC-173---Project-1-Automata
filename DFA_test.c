#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"

void Automaton_Tester(DFA dfa){
  printf("Automaton Description: %s \n", DFA_get_description(dfa));
  char control = 'Y';

  while (control != 'N' ){
    printf("Please enter the string you'd like to test: ");
    char input[50];
    scanf("%s", input);
    bool result = DFA_execute(dfa, input);
    printf("The string '%s'  %s", input, result? "passes this automaton\n" : "fails this automaton\n");
    printf("Enter 'N' to stop, 'Y' to continue: ");
    scanf(" %c", &control);
    printf("\n");
  }


}


int main(int argc, char **argv){

  //Automaton that recognizes the string 'ab'
  DFA ab = DFA_new(3);
  for(int i = 0; i < 3; i++){ //if an incorrect input is entered that causes the automaton to fail, this will catch it
    DFA_set_transition_all(ab, i, -1);
  }
  DFA_set_transition(ab, 0, 'a', 1);
  DFA_set_transition(ab, 1, 'b', 2);
  DFA_set_accepting(ab, 2, true);
  DFA_set_description(ab, "This automaton recognizes the string 'ab'");
  Automaton_Tester(ab);

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
  return 0;

}
