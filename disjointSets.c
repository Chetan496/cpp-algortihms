#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


/*1. MAKE-SET(x) - creates a new set whose only member(and thus representative) is x.
 * Since the sets are disjoint, we require that x not already be in some other set.
 *
 *2. UNION(x,y) - unites the dynamic sets that contain x and y, say Sx and Sy, into a new set that is the union of these two sets.
 The two sets are assumed to be disjoint prior to the operation.
 The representative of the resulting set is any member of Sx or Sy. Since we require the sets in the collection to be disjoint, we destroy sets Sx and Sy, removing them from the collection.

 3. FIND-SET(x) - returns a pointer to the representative of the unique set containing x

 Let n - number of MAKE-SET operations, and  m - total number of MAKE-SET, UNION and FIND-SET operations.
 Since the sets are disjoint, each UNION operation reduces the number of sets by one. After n-1 UNION operations therefore, only one set remains. The number of UNION operations is thus at most n-1.
 Also since the MAKESET operations are included in total number of operations m, we have m>=n. We assume that the n MAKE-SET operations are the first n operations performed
 * */
/*
 *We are going to implement disjoint sets using disjoint forests.
 */

/* SetElement structure*/
typedef struct SetElement_t {
   struct SetElement_t* parent;  /*only parent pointers, no child pointers */
   int rank;
   void* val;   /*Our setElements are generic - we can store anything in it */
}SetElement;

/*the root node can represent the entire set a.k.a tree */
/* this function takes an int, creates a SetElement from it and returns it. This SetElement will represent a new Set */
SetElement* makeSet(void* x) {
   SetElement* S = (SetElement*) malloc(sizeof(SetElement));
   S->rank = 0;
   S->parent = S;
   S->val = x;
   return S;
}

/*Given a SetElement in a set, this function returns the root/representative of that set */
SetElement* findSet(SetElement* x) {
   /*We are using PAth-compression heuristic. Each node on the find path will point directly to the root node after this function finishes */
   /* This is a two-pass method: It makes one pass up the find path to find the root, and it makes a second pass back down the find path to update each node so that it points directly to the root*/
   if (x != x->parent){
      x->parent = findSet(x->parent)  ;
   }
   return x->parent ;
}

void link(SetElement* x, SetElement* y) {
   /* x and y are the roots of the two trees a.k.a the reprsenatatives of both the sets*/
/*Links the two sets|trees. The tree with a root of smaller rank will be attached to tree of root with greater rank */
   if(x->rank > y->rank) {
      y->parent = x;
   }else{
      x->parent = y;
      if(x->parent == y->parent) {
         y->rank = y->rank + 1;
      }
   }
}

void Union(SetElement* x, SetElement* y) {
   link( findSet(x), findSet(y) ) ;
}

int main(){
  int i1 = 2, i2 = 3, i3 = 5;
  SetElement* s1 = makeSet(&i1);
  SetElement* s2 = makeSet(&i2);
  SetElement* s3 = makeSet(&i3);
   
  assert( findSet(s1) != findSet(s2) ) ;
  Union(s1, s2) ;

  assert( findSet(s1) == findSet(s2)) ;
  Union(s2, s3);


  assert( findSet(s1) == findSet(s3)) ;

   return 0;
}
