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
  char* description;
};


DFA DFA_new(int nstates){
  DFA dfa = (DFA)malloc(sizeof(struct DFA));
  dfa->states = nstates;
  dfa->transitions = (int**)calloc(nstates, sizeof(int*));
  dfa->accepting_states = (bool*)calloc(nstates, sizeof(bool));
  for(int i = 0; i <nstates; i++){
    dfa->transitions[i] = (int*)calloc(128, sizeof(int));
  }
  return dfa;
}

void DFA_free(DFA dfa){
  for(int i = 0; i < dfa->states; i++){
      free(dfa->transitions[i]);
    }
  free(dfa->accepting_states);
  free(dfa->description);
  free(dfa);
}

int DFA_get_size(DFA dfa){
  return dfa->states;
}

int DFA_get_transition(DFA dfa, int src, char sym){
  int x = sym;
  return dfa->transitions[src][x];
}

void DFA_set_transition(DFA dfa, int src, char sym, int dst){
  int x = sym;
  dfa->transitions[src][x] = dst;
}

void DFA_set_transition_str(DFA dfa, int src, char* str, int dst){
  for(char* pointer = str; *pointer !='\0'; pointer++){
    int x = *pointer;
    dfa->transitions[src][x]=dst;
  }
}

void DFA_set_transition_all(DFA dfa, int src, int dst){
  for(int i =0; i<128; i++){
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
  while(*input != '\0' && current != -1){
    current = DFA_get_transition(dfa, current, *input);
    input++;
  }

  if(current == -1){
    return false;
  }
  else if(DFA_get_accepting(dfa, current)){
    return true;
  }
  else{
    return false;
  }
}

void DFA_print(DFA dfa){
  printf("\n");
  for(int i = 0; i < dfa->states; i++){
    printf("State %d: ", i);
    for(int j = 0; j<128; j++){
      printf("%d ", dfa->transitions[i][j]);
    }
    printf("\n");
  }
}

char* DFA_get_description(DFA dfa){
  return dfa->description;
}

void DFA_set_description(DFA dfa, char* description){
  dfa->description = description;
}

void Automaton_Tester(DFA dfa){
  printf("DFA Automaton Description: %s \n", DFA_get_description(dfa));
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
