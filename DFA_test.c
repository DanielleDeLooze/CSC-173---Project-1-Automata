#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"

int main(int argc, char **argv){
  DFA test = DFA_new(3);
  DFA_set_transition(test, 0, 'a', 1);
  DFA_set_transition(test, 1, 'b', 2);
  DFA_set_accepting(test, 2, true);


  printf("%d, %d \n", DFA_get_transition(test, 0, 'a'), DFA_get_transition(test,1,'b'));



  bool result = DFA_execute(test, "ab");
  bool result2 = DFA_execute(test, "abc");
  printf(DFA_get_accepting(test, 2)? "true" : "false");
  printf("\n");
  printf(result? "true \n" : "false \n");
  printf(result2? "true": "false");

  printf("\n");
  DFA_print(test);
  return 0;

}
