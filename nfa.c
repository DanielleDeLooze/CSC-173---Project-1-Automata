
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

struct NFA {
  IntSet** transitions_subsets;
  int states;
  int* accepting;
  char* description;
};

NFA NFA_new(int nstates){
  NFA nfa = (NFA)malloc(sizeof(NFA));
  nfa->states = nstates;
  nfa->transitions_subsets = (IntSet**)calloc(nstates, sizeof(IntSet*));
  nfa->accepting = (int*)calloc(nstates, sizeof(int));
  for(int i =0; i < nstates; i++){
    nfa->transitions_subsets[i] = (IntSet*)calloc(123, sizeof(IntSet));
    for(int j = 0; j < 123; j++){
      nfa->transitions_subsets[i][j] = IntSet_new();
    }
    printf("\n");
  }

  return nfa;
}

void NFA_free(NFA nfa){
  for(int i = 0; i < nfa->states; i++){
    for(int j = 0; j<123; j++){
      free(nfa->transitions_subsets[i][j]);
    }
    free(nfa->transitions_subsets[i]);
  }
  free(nfa->accepting);
  free(nfa->description);
  free(nfa);
}

int NFA_get_size(NFA nfa){
  return nfa->states;
}

IntSet NFA_get_transitions(NFA nfa, int state, char sym){
  int x = sym;
  return nfa->transitions_subsets[state][x];
}

void NFA_add_transition(NFA nfa,int src, char sym, int dst){
  int x = sym;
  IntSet_add(nfa->transitions_subsets[src][x], dst);
}

void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
  for(char* pointer = str; *pointer != '\0'; pointer++){
    int x = *pointer;
    IntSet_add(nfa->transitions_subsets[src][x], dst);
  }
}

void NFA_add_transition_all(NFA nfa, int src, int dst){
  for(int i = 0; i < 123; i++){
    IntSet_add(nfa->transitions_subsets[src][i], dst);
  }
}

void NFA_set_accepting(NFA nfa, int state, bool value){
  nfa->accepting[state] = value;
}

bool NFA_get_accepting(NFA nfa, int state){
  return nfa->accepting[state];
}

/*
bool NFA_execute(NFA nfa, char *input){
  int current = 0;
  while(*input != '\0'){
    NFA_get_transition(nfa, current, *input);
  }
}*/

void NFA_print(NFA nfa){
  for(int i = 0; i < nfa->states; i++){
    printf("State %d ", i);
    for(int j = 0; j < 123; j++){
      IntSet_print(nfa->transitions_subsets[i][j]);
    }
    printf("\n");
  }
}
