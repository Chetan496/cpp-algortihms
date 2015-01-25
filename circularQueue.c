#include<stdio.h>
#include<stdlib.h>
#include "lib/customHeader.h"

/*
 *This circular queue is in accordance of 
 the description of circular queue in CLRS book.
 The queue is made from an array of n elements.
 However it can contain at the most only n-1 elements.
 */
struct Queue {
   int *arrptr;
   int head;
   int tail;
   int maxsize; /*maxsize is the maximum size of the array used by the queue */
};

typedef struct Queue QueueObj;
typedef QueueObj* QueuePtr;

QueuePtr createQueue(int maxsize){
   QueuePtr q = (QueuePtr) malloc( sizeof(QueueObj) ) ;
   q->head = 0;
   q->tail = 0;
   q->maxsize = maxsize;
   q->arrptr = (int *) calloc(maxsize, sizeof(int)) ;
   return q;
}

int isQueueFull(QueuePtr q){
   return (q->tail + 1) % q->maxsize == q->head ;
}

int isQueueEmpty(QueuePtr q){
   return q->head == q->tail ;
}

void enqueue(QueuePtr q, int item) {
   /* enqueues item at the location pointed to by the tail  */   
   /* before that checks if the queue is full */
   if ( isQueueFull(q) == TRUE) {
      fprintf(stderr, "\n %s \n", "Hey, The Queue is Full.");
      return;
   }
   (q->arrptr)[q->tail] = item;
   q->tail = (q->tail + 1) % q->maxsize  ;
}

int dequeue(QueuePtr q){
   /*removes the item currently at the head of the queue and returns it */
   /* we first need to check if the queue is empty */
   if ( isQueueEmpty(q) == TRUE ) {
      fprintf(stderr, "\n %s \n", " The Queue is already empty! Cannot Dequeue." );
      return ERROR_CODE ;
   }
   int headElem = (q->arrptr)[q->head] ;
   q->head = (q->head + 1) % q->maxsize ;
   return headElem ;
}

int main(){
   QueuePtr q = createQueue(5) ;
   enqueue(q, 5) ;
   enqueue(q, 4) ;
   enqueue(q, 9) ;
   enqueue(q, 10) ;
   enqueue(q, 91) ;
   fprintf(stdout, "\n %s: %d \n", "Dequeued Item is ", dequeue(q))  ;
   fprintf(stdout, "\n %s: %d \n", "Dequeued Item is ", dequeue(q))  ;
   fprintf(stdout, "\n %s: %d \n", "Dequeued Item is ", dequeue(q))  ;
   fprintf(stdout, "\n %s: %d \n", "Dequeued Item is ", dequeue(q))  ;
   fprintf(stdout, "\n %s: %d \n", "Dequeued Item is ", dequeue(q))  ;

   return 0;
}
