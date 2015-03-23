/* A simple implementation of a hash table in C */
/* Based on the description of Hash Tables in Introduction to Algorithms by Thomas Cormen */
/*This implemenation is Hashing uses Chaining */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_BUCKETS 23
#define CREATE_NEW(type) (type*)malloc(sizeof(type))
/*TODO: 1. key and data should be char*
 * 2. Use a docubly Link List. So that deletion of an entry from the hash table takes a constant time*/
struct entry {
   char key;
   int data;  /* this is satellite data*/
   struct entry* next;  /*Link to next entry which hashes to the same slot */
   struct entry* prev;
} ;

typedef struct entry* entry_ptr;

typedef struct hashTable {
   int m;  /*Max num of slots in our Hash Table. A good value of m should be a prime not close to exact powers of 2
   powers of 10 should be avoided if the app. deals with decimal keys, since then the hash function does not
   depend on all decimal digits of the key*/
   entry_ptr* bucket; /* store the pointer to the first bucket*/
} HashTable;   /*Our hashTable has slots from index 0 to m-1 */

/* computes the index for key k and returns it*/
int hashFunction(HashTable* T, char k) {
   if (T == NULL) {
      printf("\n Error: The HashTable was not initialized \n") ;
      abort();
   }else{
      return k%(T->m);
   }
}

void chained_hash_insert(HashTable* T, entry_ptr newEntry) {
   if (T == NULL) {
      printf("\n Error: The HashTable was not initialized \n") ;
      abort();
   }else{
     /* find the bucket where newEntry hashes to. Add it there in the hash table*/
     int h = hashFunction(T, newEntry->key);
     if( *( T->bucket + h )  != NULL)  {
      /*collision - add at the beginning of the linklist in this bucket*/
      /*save the previous head of linklist. Add new head at beginning. Adjust links */
        entry_ptr oldhead = *(T->bucket + h) ;
        newEntry->next = oldhead;
        newEntry->prev = NULL;
        oldhead->prev = newEntry;
     }

     *(T->bucket + h) = newEntry;
     printf("\n Added to the hash table in bucket %d \n", h) ;
   }
}


entry_ptr chained_hash_search(HashTable* T, char k) {
   /*search for an entry having key k in hash table and return it. */
   if (T == NULL) {
      printf("\n Error: The HashTable was not initialized \n") ;
      abort();
   }else{
      /*find the bucket where k hashes to. Search in the linklist of that bucket for k. Return the entry. */     
      int h = hashFunction(T, k) ;
      if ( *(T->bucket + h) == NULL ) {
       /*bucket is empty. The key k is nt present in this hash table. */
         printf("\n Error: This key is not present in the hash table \n");
         return NULL;
      }else{
         /* traverse the linklist*/ 
         entry_ptr temp = *(T->bucket + h) ;
         while( (temp->key != k) && temp!=NULL) {
            temp = temp->next;
         }
         return temp;
      }
   }
 }

bool chained_hash_delete(HashTable* T, entry_ptr ep) {
   /*deletes the given entry from the hash table */
   /*returns if the deletion was successful */
   /*deletion performance can be improved if we use doubly link list with just O(1) complexity.
    * FOr singly link list it requires O(n) time*/
   int h = hashFunction(T, ep->key) ;
   /*find the previous element of ep in bucket h. Then adjust the links */
      if(ep->next != NULL){
         ep->next->prev = ep->prev;
      }
      if( ep->prev != NULL){
         ep->prev->next = ep->next;
      }else{
       /*the entry being deleted is the first entry in the bucket */
         *(T->bucket + h) = ep->next;
      }
      free(ep);
      return true;
  }


/*Allocates memory, Initializes and returns a new HashTable. */
HashTable* allocate_hashTable(int m) {
   HashTable* T= CREATE_NEW(HashTable) ;
   if(T == NULL){
      printf("\n Error: Could not allocate memory for the HashTable \n");
      abort();
   }else{
      T->m = m ;
   /* use calloc for allocating a block containing pointers to m entries. Zero them out initially*/
      T->bucket = (entry_ptr*) calloc(sizeof(entry_ptr), m);
      if(T->bucket == NULL){
         printf("\n Error: Could not allocate memory for the buckets of the hash table \n") ;
         abort();
      }
   }
   return T;
}

entry_ptr create_newEntry(char key, int val) {
   entry_ptr e = CREATE_NEW(struct entry) ;
   if (e == NULL){
      printf("\n Error: Could not allocate memory to key-value pair \n");
      abort();
   }else{
      e->key = key;
      e->data = val;
      e->next = NULL;
      e->prev = NULL;
   }
   return e;
}

int main(){
   HashTable* T = allocate_hashTable(MAX_BUCKETS);
   chained_hash_insert(T, create_newEntry('A', 65)) ;
   chained_hash_insert(T, create_newEntry('B', 66)) ;
   chained_hash_insert(T, create_newEntry('B', 98)) ;
   entry_ptr e = chained_hash_search(T, 'A') ;
   printf("\n After searching, found %d \n ", e->data) ;
   chained_hash_delete(T, e) ;
   entry_ptr ef =   chained_hash_search(T, 'A') ;
   if (ef == NULL){
      printf("\n Search was not successful \n");
   }
   return 0;
}
