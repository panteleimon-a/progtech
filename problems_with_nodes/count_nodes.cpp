// THEMA 19 SEP 2019

#include <iostream>
//vertical define info as node
struct LinkedList {
    int info;
    LinkedList* next;
};

//header

struct Node {
    LinkedList* next_list;
    int data;
    Node* next_node;
    
};

typedef struct Node *list;
// A

int SumOfNodes(list l){
  if(!l){
    return;
  }
  // for each root
  return l->data +SumOfNodes(l->next_node);
};

// for each linkedlist

int ListSumIterator(list l){
while(l->next_list->info) {
  if (!l) {return;}
  return SumOfNodes(l)+ListSumIterator(l->next_list->next);
  };
};
 



// B
int numOfOdds(list l){
  if(!l) return;
  return (l->data % 2==1+numOfOdds(l->next_node));
};
// for each linked list count odds
int ListOddsIterator(list l){
while(l->next_list->info){
  return numOfOdds(l)+ListOddsIterator(l->next_list->next);
  };
};



