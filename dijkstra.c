#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define INFINITY 1000 /*assuming no input vertex has distance greater than 1000 */

inline void print_error(char *msg) {
   printf("\n Error: %s \n", msg);
   abort();
}

inline void print_successMsg( char *msg ) {
   printf(" \n Success: %s \n" , msg) ;
}
/*--------------------Begin Disjoint Set Data Structure------------------------- */
typedef struct SetElement_t {
   struct SetElement_t* parent;  /*only parent pointers, no child pointers */
   int rank;
   void* val;   /*Our setElements are generic - we can store anything in it */
}SetElement_t, *SetElement_p;

SetElement_p makeSet(void* x) {
   SetElement_p S = (SetElement_p) malloc(sizeof(SetElement_t));
   S->rank = 0;
   S->parent = S;
   S->val = x;
   return S;
}

/*Given a SetElement in a set, this function returns the root/representative of that set */
SetElement_p findSet(SetElement_p x) {
   /*We are using PAth-compression heuristic. Each node on the find path will point directly to the root node after this function finishes */
   if (x != x->parent){
      x->parent = findSet(x->parent)  ;
   }
   return x->parent ;
}

void link(SetElement_p x, SetElement_p y) {
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

void Union(SetElement_p x, SetElement_p y) {
   link( findSet(x), findSet(y) ) ;
}


/*------------------------------------Begin  Graph data structures and functions----------------------- */

typedef char GraphElementT ;

typedef struct Vertex_t {
   GraphElementT val;
   struct AdjacencyList_t* adjList;  // to store information of adjacent vertices in a list
   struct Vertex_t* next;     //to point to the next vertex (not the adjacent vertex) in the list of the vertices of the graph
   bool visited;
   SetElement_p set_ref ; //each vertex ref. will also me maintained in its own set
   struct Vertex_t* predecessor;
   int d;
}Vertex_t, *Vertex_p ;  //typedef to Vertex and typedef to pointer of Vertex

/*Each node of adjacency list contains a pointer to the vertex and a pointer to the next node in adjacencey list */
typedef struct AdjacencyList_node_t {
   Vertex_p vertex_ref;
   struct AdjacencyList_node_t* next;
   struct Edge_t *edgeRef ;
}AdjacencyList_node_t, *AdjacencyList_node_p;

//Each adjacency List can be represented by just a pointer to its head node
typedef struct AdjacencyList_t {
   AdjacencyList_node_p head;
}AdjacencyList_t, *AdjacencyList_p; 

typedef struct Edge_t {
   Vertex_p src;
   Vertex_p dest;
   struct Edge_t *next ;
   int wt ;  //This is a weighted graph with positive weights
} Edge_t, *Edge_p ;

typedef struct Graph_t {
  Vertex_p headVertex; 
  Edge_p edge ;
  int edgeCount ;
}Graph_t, *Graph_p;

/*returns a empty undirected graph */
Graph_p createGraph(){
   Graph_p graph= (Graph_p) malloc(sizeof(Graph_t)) ;
   graph->headVertex = NULL;   //empty graph
   graph->edge = NULL ;
   graph->edgeCount = 0;
   return graph;
}

Vertex_p createVertex(GraphElementT val) {
   /*Creates a new Vertex with given  value*/
   /*Takes O(1)  time to create vertex in the graph*/
   Vertex_p newVertex = (Vertex_p) malloc(sizeof(Vertex_t)) ;
   if (newVertex == NULL) {
      print_error("Could not allocate a new Vertex from heap memory. Exiting") ;
   }
   newVertex->val = val;
   newVertex->next = NULL;
   newVertex->visited = false;
   newVertex->adjList = (AdjacencyList_p) malloc(sizeof(AdjacencyList_t)) ;
   if (newVertex->adjList == NULL) {
      print_error("Could not allocate memory for creating adjacency List of the vertex");
   }
   newVertex->adjList->head = NULL ; //the adjacency List is empty when vertex is initialzed

   newVertex->set_ref = NULL ;
   newVertex->predecessor = NULL ;
   newVertex->d = INFINITY;
   return newVertex;
}

void addVertex(Graph_p graph, Vertex_p vertex){
   /*adds the given vertex into the graph */
   /*Takes O(1) time. The new vertex is added at the head of the list of the vertices of the graph */
   /*TODO: check if this vertex already exists in the graph. If it already exists then do not add it to graph */
   if (graph == NULL || vertex == NULL)   {
      print_error("Either the graph or the vertex to add is not initialized") ;
   }
   vertex->next = graph->headVertex ;
   graph->headVertex = vertex ;
   print_successMsg("Added the vertex to the graph") ;
}


/*This function returns a vertex whose value is elem.
 * Takes O(|V|) time*/
inline Vertex_p getVertex(Graph_p graph_p, GraphElementT elem) {
   Vertex_p vp = graph_p->headVertex ;
   while(vp != NULL){
      if (vp->val == elem){
         return vp;
      }
      vp = vp->next;
   }
   return NULL;
}

void addEdge(Graph_p g, Vertex_p src, Vertex_p dest, size_t wt) {
   /*Make entries in the adjacency lists of src vertex only since Dijsktras algo. works on directed graph */
   /*we just add new entry in adjacency list at the head of that list */
   /*Takes O(1) time */
   if( src == NULL || dest == NULL) {
      print_error("Either the source vertex or dest vertex is not initialized");
   }
   if ( g == NULL)   {
   
      print_error("The graph is not intialized") ;
   }
   //add a new edge in to the edge list of the graph at the beginning
   Edge_p edge = (Edge_p) malloc(sizeof(Edge_t)) ;
   edge->dest = dest;
   edge->src = src ;
   edge->wt = wt ;
   edge->next = g->edge ;
   g->edge = edge ;
   g->edgeCount = g->edgeCount + 1 ;
   
   //update the adjacency list, since this is a directed graph only update the src adj. list
   AdjacencyList_p srcAdjList = src->adjList ;

   AdjacencyList_node_p node_srcAdjList = (AdjacencyList_node_p) malloc(sizeof(AdjacencyList_node_t)) ;
   if (node_srcAdjList == NULL) {
      print_error("Could not allocate memory for creating a node in source Adjacency list ") ;
   }

   node_srcAdjList->vertex_ref = dest;
   node_srcAdjList->next = srcAdjList->head;
   node_srcAdjList->edgeRef = edge ;
   srcAdjList->head = node_srcAdjList ;

   print_successMsg("Added the edge") ;
}



/*-------------------------------Priority Queue Implementation ---------------------------------*/
#define PARENT(i) (i & 0x01) ? ( i >> 1) : ( (i-1) >> 1 )    /* C arrays start with 0. Hence the subtelity to get Parent */
#define LEFT(i) ( (i << 1) | 1 )
#define RIGHT(i) ( LEFT(i) + 1)
#define MID_HEAP_INDEX(heapSize) ( (heapSize >> 1 ) - 1 )


typedef struct Heap_t {
   Vertex_p *vp_refs;
   int arrlength;
   int heapSize;
} Heap_t, *Heap_p;


inline void swap( void *num1, void *num2) { void *t; t = num1 ;   num1 = num2;   num2 = t;}

void heapify(Heap_p H, int i) {
   int l = LEFT(i)   ;
   int r = RIGHT(i) ;
   int least = (l <= H->heapSize-1 && ( H->vp_refs)[l]->d < (H->vp_refs)[i]->d ) ? l : i ;

   least = ( r<= H->heapSize-1 &&  (H->vp_refs)[r]->d < (H->vp_refs)[least]->d  ) ? r : least ;

   if( least != i )  {
      swap (  &(H->vp_refs)[i] , &(H->vp_refs)[least] ) ;
      if( least <=  MID_HEAP_INDEX(H->heapSize)  ){
        heapify(H, least) ;
      }
   }
}

/* This function inserts a new element with key into the heap.
 * It maintains the min-heap property while inserting*/
void heap_insert(Heap_p H, Vertex_p v) {
   //expand the heap, add a new node to heap memory
   H->vp_refs = (Vertex_p *) realloc(H->vp_refs, (H->heapSize + 1)*sizeof(Vertex_p) ) ;
   if (H->vp_refs == NULL) {
      print_error("Could not allocate memory for new element ");
   }
   H->heapSize = H->heapSize + 1 ;
   int i = H->heapSize - 1 ; //last index of heap is always one less than heapSize
   // i is pointing to last index in the heap. That location currently has garbage val      
   
   while( i>0 &&  ( (H->vp_refs)[PARENT(i)]->d ) > v->d ) {

      (H->vp_refs)[i] = ( H->vp_refs)[PARENT(i)] ;
      i = PARENT(i);
   }

   (H->vp_refs)[i] = v;
}

/*This function takes in a Heap ptr. as input and returns the element having the least value of its key k*/
/*It maintains the heap property by calling Heapify */
Vertex_p heap_extract_min(Heap_p H){
   if(H == NULL) {
      print_error("The heap is not initialized ");
   }
   if(H->heapSize < 1) {
      print_error("Heap Underflow!");
   }
  
   Vertex_p min = (H->vp_refs)[0] ;
   (H->vp_refs)[0] = (H->vp_refs)[H->heapSize - 1] ;
   H->heapSize = H->heapSize - 1;
   heapify(H, 0);
   return min;
}

/*Creates an empty heap and returns it */
Heap_p createHeap() {
   Heap_p H = (Heap_p) malloc(sizeof(Heap_t)) ;
   H->heapSize = 0;  
   H->vp_refs = NULL;
   H->arrlength = 0 ;
   return H;
}


/*----------------------------Specific functions to Dijkstras algo--------------------------- */

void initializeSingleSource(Graph_p g, Vertex_p s) {
   Vertex_p v = g->headVertex ;
   while(v != NULL) {
      v->d = INFINITY ;
      v->predecessor = NULL ;
      v = v->next ;
   }
   s->d = 0;
}


inline void relax(Vertex_p u, Vertex_p v, int wt) {
   if (v->d > (u->d + wt ) ) {
      v->d = u->d + wt ;
      v->predecessor = u ;
   }
}

void dijkstra(Graph_p g, Vertex_p s) {
   initializeSingleSource(g, s) ;
   Heap_p q = createHeap() ;
   Vertex_p v = g->headVertex ;
   /*Insert all the vertices in the heap */
   while(v != NULL) {
      heap_insert(q, v) ;
      v = v->next ;
   }

   Vertex_p u; 
   AdjacencyList_p adjList ;
   AdjacencyList_node_p node ;
   while(q->heapSize != 0) {
      u = heap_extract_min(q) ;
      adjList = u->adjList ;
      node = adjList->head ;
      while(node != NULL) {
         relax(u, node->vertex_ref, node->edgeRef->wt ) ;
         node = node->next ;
      }
   }
}
/*--------------------Main driver function-------------------------------*/
int main(){
   Graph_p g = createGraph() ;
   Vertex_p v_A = createVertex('A') ;
   Vertex_p v_B = createVertex('B') ;
   Vertex_p v_C = createVertex('C') ;
   Vertex_p v_D = createVertex('D') ;
   Vertex_p v_E = createVertex('E') ;
   
   addVertex(g, v_A);
   addVertex(g, v_B);
   addVertex(g, v_C);
   addVertex(g, v_D);
   addVertex(g, v_E);

   addEdge(g, v_A, v_B, 10) ;
   addEdge(g, v_B, v_C, 1) ;
   addEdge(g, v_A, v_D, 5) ;
   addEdge(g, v_D, v_E, 2) ;
   addEdge(g, v_B, v_D, 2) ;
   addEdge(g, v_D, v_B, 3) ;
   addEdge(g, v_C, v_E, 4) ;
   addEdge(g, v_E, v_C, 6) ;
   addEdge(g, v_D, v_C, 9) ;
   addEdge(g, v_E, v_A, 7) ;

   dijkstra(g, v_A) ;
   
  return 0;
}
