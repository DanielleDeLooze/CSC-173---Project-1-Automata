/*
Author: Danielle DeLooze
Date: 9/16/2017
Purpose: Implementation of a DFA
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfa.h"

struct DFA {
  int** transitions;
  int states;
  bool* accepting_states;
};


DFA DFA_new(int nstates){
  DFA dfa = (DFA)malloc(sizeof(struct DFA));
  dfa->states = nstates;
  dfa->transitions = (int**)calloc(nstates+1, sizeof(int*));
  dfa->transitions[nstates+1] =NULL;
  dfa->accepting_states = (bool*)calloc(nstates, sizeof(bool));
  for(int i = 0; i <nstates; i++){
    dfa->transitions[i] = (int*)calloc(75, sizeof(int));
  }
  return dfa;
}

void DFA_free(DFA dfa){
  free(dfa->transitions);
  dfa->transitions = NULL;
  free(dfa);
  dfa = NULL;
}

int DFA_get_size(DFA dfa){
  return dfa->states;
}

int DFA_get_transition(DFA dfa, int src, char sym){
  int x = sym;
  return dfa->transitions[src][x-48];
}

void DFA_set_transition(DFA dfa, int src, char sym, int dst){
  int x = sym;
  dfa->transitions[src][x-48] = dst;
}

void DFA_set_transition_str(DFA dfa, int src, char* str, int dst){
  for(char* pointer = str; *pointer !='\0'; pointer++){
    int x = *pointer;
    dfa->transitions[src][x]=dst;
  }
}

void DFA_set_transition_all(DFA dfa, int src, int dst){
  for(int i =0; i<74; i++){
    dfa->transitions[src][i] = dst;
  }
}

void DFA_set_accepting(DFA dfa, int state, bool value){
  dfa->accepting_states[state] = value;
}

bool DFA_get_accepting(DFA dfa, int state){
  return dfa->accepting_states[state];
}

bool DFA_execute(DFA dfa, char* input){
  int current = 0;
  while(*input != '\0'){
    current = DFA_get_transition(dfa, current, *input);
    input++;
  }

  printf("%d \n", current);

  if(DFA_get_accepting(dfa, current)){
    return true;
  }
  else{
    return false;
  }
}

void DFA_print(DFA dfa){
  printf("\t ");
  for(int x= 0; x < 75; x++){
    printf("%c ", x+48);
  }
  printf("\n");
  for(int i = 0; i < dfa->states; i++){
    printf("State %d: ", i);
    for(int j = 0; j<75; j++){
      printf("%d ", dfa->transitions[i][j]);
    }
    printf("\n");
  }
}
