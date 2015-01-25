/*
 *This is an implementation of circular doubly linked list.
 It uses a sentinel as the first("head") node of  the linked list.
 Each node of the doubly linked list has the next and the previous pointers.
 The next pointer of the last node in the link list points back to the sentinel node.
 Since we are using the sentinel node, there is no concept of head or tail for our doubly linked list
 */
#include<stdio.h>
#include<stdlib.h>
#include "lib/customHeader.h"

typedef struct NodeObj {
   int item;
   struct NodeObj* nextNode;
   struct NodeObj* prevNode;
}Node;

typedef Node* NodePtr;
/*we are reprsenting our doubly linked list by just a pointer to the first node. This node in turen has a pointer which 
 *points to the remaining list. In a way, if we remove the first node from our list, the remaining thing is still a list
 * */
typedef struct DoublyLinkedList{
  NodePtr nilNode ;
}DoublyLinkedList;

typedef DoublyLinkedList* DoublyLinkedListPtr;

DoublyLinkedListPtr createDoublyLinkedList(){
   DoublyLinkedListPtr list = (DoublyLinkedListPtr) malloc(sizeof(DoublyLinkedList)) ;
   NodePtr nilNode = (NodePtr) malloc(sizeof(Node)) ;
   nilNode->item = -1 ;
   nilNode->nextNode = nilNode;
   nilNode->prevNode = nilNode ;
   list->nilNode = nilNode ;
   return list ;
}

void list_traverse(DoublyLinkedListPtr L){
  printf("Traversing the list: ")   ;
  /*start from the nilNode. Keep on displaying node->nextNode. Stop if node->nextNode = nilNode  */
  NodePtr n = L->nilNode ;
  while( n->nextNode != L->nilNode ) {
     fprintf(stdout, "\n %d \n", n->nextNode->item) ;
     n = n->nextNode ;
  }
}

NodePtr list_search(DoublyLinkedListPtr L, int item) {
  NodePtr node = L->nilNode->nextNode ;
  while( node != L->nilNode && node->item != item ) {
      node = node->nextNode ;
  }
  return node ;

}

void list_insert(DoublyLinkedListPtr L, int item){
   /*1. Create a new node with the item given by the caller. 2. Insert it immediately after the nilNode.
    * 3. Set the Pointers of the nodes correctly  */
   NodePtr newNode = (NodePtr) malloc(sizeof(Node)) ;
   newNode->item = item ;

   newNode->nextNode = L->nilNode->nextNode ;
   L->nilNode->nextNode->prevNode = newNode;
   L->nilNode->nextNode = newNode;
   newNode->prevNode = L->nilNode ;
}

void list_delete( NodePtr node) {
   node->prevNode->nextNode = node->nextNode ;
   node->nextNode->prevNode = node->prevNode ;
   free(node) ;
}
int main(){
   DoublyLinkedListPtr list = createDoublyLinkedList() ;
   NodePtr searchedNode ;
   list_insert(list, 10)    ;
   list_insert(list, 5)    ;
   list_insert(list, 7)    ;
   list_traverse(list) ;
   
   searchedNode = list_search(list, 5) ;
   if(searchedNode->item == -1) {
      fprintf(stderr, "\n %s \n", "No item with the key was found " ) ;
   }else{
      fprintf(stdout, "\n %s \n", "The item was found")  ;
      printf("\n Deleting the searched node ...  \n ") ;
      list_delete(searchedNode) ;
      printf("\n After deleting the node, linklist is : \n ") ;
      list_traverse(list) ;
   }
   return 0;
}
