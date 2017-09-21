
/*
Author: Danielle DeLooze
Date: 9/17/2017
Purpose: CSC 173 Project 1 Part 2. Implementation of NFA
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "IntSet.h"
#include "nfa.h"

struct NFA{
  IntSet** transitions;
  int states;
  IntSet accepting;
  char* description;
};

NFA NFA_new(int nstates){
  NFA nfa = (NFA)malloc(sizeof(struct NFA));
  nfa->accepting = IntSet_new();
  nfa->states = nstates;
  nfa->transitions= (IntSet**)calloc(nstates, sizeof(IntSet*));
  for(int i =0; i < nstates; i++){
    nfa->transitions[i] = (IntSet*)calloc(128, sizeof(IntSet));
    }

  return nfa;
}

void NFA_free(NFA nfa){
  for(int i = 0; i < nfa->states; i++){
    for(int j = 0; j<128; j++){
      free(nfa->transitions[i][j]);
    }
    free(nfa->transitions[i]);
  }
  free(nfa->accepting);
  free(nfa);
}

int NFA_get_size(NFA nfa){
  return nfa->states;
}

IntSet NFA_get_transitions(NFA nfa, int state, char sym){
  int x = sym;
  return nfa->transitions[state][x];
}

void NFA_add_transition(NFA nfa,int src, char sym, IntSet dst){
  int x = sym;
  nfa->transitions[src][x] = dst;
}

void NFA_add_transition_str(NFA nfa, int src, char *str, IntSet dst){
  for(char* pointer = str; *pointer != '\0'; pointer++){
    int x = *pointer;
    nfa->transitions[src][x] = dst;
  }
}

void NFA_add_transition_all(NFA nfa, int src, IntSet dst){
  for(int i = 0; i < 128; i++){
    nfa->transitions[src][i] = dst;
  }
}

void NFA_set_accepting(NFA nfa, int state){
  IntSet_add(nfa->accepting, state);
}

IntSet NFA_get_accepting(NFA nfa){
  return nfa->accepting;
}


bool NFA_execute(NFA nfa, char* input){
  IntSet current = IntSet_new();
  IntSet_add(current, 0);

  while(*input != '\0'){
    int x = *input;
    IntSetIterator iterator = IntSet_iterator(current);
    IntSet temp = IntSet_new();
    while(IntSetIterator_has_next(iterator)){
      IntSet_union(temp, NFA_get_transitions(nfa, IntSetIterator_next(iterator), x));
    }
    current = temp;
    input++;
  }

  IntSetIterator accepting = IntSet_iterator(nfa->accepting);
  while(IntSetIterator_has_next(accepting)){
    if(IntSet_contains(current, IntSetIterator_next(accepting))){
      return true;
    }
  }
  return false;
}

void NFA_print(NFA nfa){
  for(int i = 0; i < nfa->states; i++){
    printf("State %d: ", i);
    for(int j = 0; j < 128; j++){
      IntSet_print(nfa->transitions[i][j]);
    }
    printf("\n");
  }
}

void NFA_set_description(NFA nfa, char* desc){
  nfa->description = desc;
}

char* NFA_get_description(NFA nfa){
  return nfa->description;
}

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
