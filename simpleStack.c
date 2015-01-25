#include<stdio.h>
#include<stdlib.h>
#include "lib/customHeader.h"

struct stackObj {
  int *arrptr;
  int top;
  int maxSize;
};

typedef struct stackObj Stack;
typedef Stack* StackPtr;

StackPtr createStack(int stackSize){
  StackPtr stack = (StackPtr) malloc( sizeof(Stack) ) ;
  stack->top = -1;
  stack->arrptr = (int *)calloc(stackSize, sizeof(int)) ;
  stack->maxSize = stackSize;
  return stack;
}

int isStackEmpty(StackPtr stack) { return (stack->top == -1) ;  }

void push(StackPtr stack, int item) {
  
  if (stack->top == stack->maxSize - 1) { printf("\n Stack Overflow! \n"); return; } 

  (stack->arrptr) [++stack->top] = item;
}

int pop(StackPtr stack) {
  return isStackEmpty(stack) == TRUE ? ERROR_CODE : (stack->arrptr)[stack->top--] ;
}
int main(){
   
   StackPtr stack = createStack(5)   ;   //our stack is finite sized of 5 elems.
   push(stack, 3)       ;
   push(stack, 4)       ;
   push(stack, 1)       ;
   push(stack, -9)       ;
   push(stack, 3)       ;
   push(stack, 20)       ;
   printf("\n Popped: %d \n",  pop(stack) )  ;
   printf("\n Popped: %d \n",  pop(stack) )  ;
   printf("\n Popped: %d \n",  pop(stack) )  ;
   printf("\n Popped: %d \n",  pop(stack) )  ;
   printf("\n Popped: %d \n",  pop(stack) )  ;
   printf("\n Popped: %d \n",  pop(stack) )  ;
   return 0 ;
}
