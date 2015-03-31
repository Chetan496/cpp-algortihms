#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

inline void print_error(char *msg) {
   printf("\n Error: %s \n", msg);
   abort();
}

inline void print_successMsg( char *msg ) {
   printf(" \n Success: %s \n" , msg) ;
}

typedef char GraphElementT ;

typedef struct Vertex_t {
   GraphElementT val;
   struct AdjacencyList_t* adjList;  // to store information of adjacent vertices in a list
   struct Vertex_t* next;     //to point to the next vertex (not the adjacent vertex) in the list of the vertices of the graph
   bool visited;
   SetElement_p set_ref ; //each vertex ref. will also me maintained in its own set
}Vertex_t, *Vertex_p ;  //typedef to Vertex and typedef to pointer of Vertex

/*Each node of adjacency list contains a pointer to the vertex and a pointer to the next node in adjacencey list */
typedef struct AdjacencyList_node_t {
   Vertex_p vertex_ref;
   struct AdjacencyList_node_t* next;
}AdjacencyList_node_t, *AdjacencyList_node_p;

//Each adjacency List can be represented by just a pointer to its head node
typedef struct AdjacencyList_t {
   AdjacencyList_node_p head;
}AdjacencyList_t, *AdjacencyList_p; 

typedef struct Edge_t {
   Vertex_p src;
   Vertex_p dest;
   int wt ;  //This is a weighted graph with positive weights
} Edge_t, *Edge_p ;

typedef struct Graph_t {
  Vertex_p headVertex; 
  Edge_p edge ;
  int edgeCount ;
}Graph_t, *Graph_p;

typedef struct MSTGraph_t {
   Edge_p edges;
   size_t edgeCount ;
} MSTGraph_t, *MSTGraph_p ;
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
   /*Make entries in the adjacency lists of both the src and dest in the graph to addn edge */
   /*we just add new entry in adjacency list at the head of that list */
   /*Takes O(1) time */
   if( src == NULL || dest == NULL) {
      print_error("Either the source vertex or dest vertex is not initialized");
   }
   AdjacencyList_p srcAdjList = src->adjList ;
   AdjacencyList_p destAdjList = dest->adjList ;

   AdjacencyList_node_p node_srcAdjList = (AdjacencyList_node_p) malloc(sizeof(AdjacencyList_node_t)) ;
   if (node_srcAdjList == NULL) {
      print_error("Could not allocate memory for creating a node in source Adjacency list ") ;
   }
   node_srcAdjList->vertex_ref = dest;
   node_srcAdjList->next = srcAdjList->head;
   srcAdjList->head = node_srcAdjList ;

   AdjacencyList_node_p node_destAdjList = (AdjacencyList_node_p) malloc(sizeof(AdjacencyList_node_t)) ;
   if (node_destAdjList == NULL) {
      print_error("Could not allocate memory for creating a node in destination Adjacency list ") ;
   }
   node_destAdjList->vertex_ref = src;
   node_destAdjList->next = destAdjList->head;
   destAdjList->head = node_destAdjList ;

   Edge_t edge ;
   edge.dest = dest;
   edge.src = src ;
   edge.wt = wt ;
   g->edgeCount = g->edgeCount + 1 ;
   g->edge = (Edge_p) realloc(g->edge, (g->edgeCount)*sizeof(Edge_t)) ;
   *(g->edge + g->edgeCount - 1) = edge ;  // add this edge to end of memory block

   print_successMsg("Added the edge") ;
}


bool isReachable(Vertex_p src, Vertex_p dest) {
  /*Traverses the Graph from src to dest in depth first search manner.
   * Returns id the dest is reachable from src*/
   if (src == NULL || dest == NULL){
      print_error("Either of src or dest vertices is null") ;
   }
   if (src == dest) {
      return true;   // trivial case - if both the src and dest are the same vertex
   }
   if (src->visited == true) {
      return false; /* backtrack - we have visited this src vertex before */
   }
   src->visited = true;
   /*go through the adjacency list of src vertex in depth search manner */
   AdjacencyList_node_p tempNode =  src->adjList->head ;
   while(tempNode != NULL) {
     if ( !isReachable(tempNode->vertex_ref, dest )  ) {
         tempNode = tempNode->next ;   //check if dest is rechable from next node in list
     }else{
         return true ;
     }
   }
   return false;
}
/*This function goes through each vertex of the graph and resets its visited flag */
void markAllVerticesAsNotVisited(Graph_p graph_p) {
   if (graph_p == NULL) {
      print_error("Graph is not intialized.") ;
   }
   Vertex_p vp = graph_p->headVertex ;
   while(vp != NULL) {
      vp->visited = false;
      vp = vp->next;
   }
}

bool isDestReachable( Graph_p graph_p,  Vertex_p src, Vertex_p dest) {
   markAllVerticesAsNotVisited(graph_p);
   return isReachable( src,  dest ) ;
}


/*----------------------------Specific functions to MST--------------------------- */
int compareEdgeWeights (const void *edge1, const void *edge2) { 
   Edge_p e1  = (Edge_p) edge1 ;
   Edge_p e2 = (Edge_p) edge2 ;
   if ( e1->wt > e2->wt) {
      return 1;
   }else if (e1->wt == e2->wt) {
      return 0;
   }else{
      return -1;
   }
}


MSTGraph_p mst_Kruskal(Graph_p g) {
/*sort the edges of E by weight */
   if ( g == NULL || g->edgeCount == 0){
      print_error("Either graph is not intialized or there are no edges added") ;
   }
   qsort(g->edge, g->edgeCount, sizeof(Edge_t), compareEdgeWeights) ;
   Vertex_p temp = g->headVertex ;
   while(temp != NULL) {
      temp->set_ref = makeSet(temp);
      temp = temp->next ;
   }
   int i = 0 ;
   Vertex_p u, v ;
   MSTGraph_p mst = (MSTGraph_p) malloc(sizeof(MSTGraph_t));
   mst->edgeCount = 0;
   mst->edges = NULL ;
   Edge_t tempEdge ;
   Edge_t currEdge ;
   for ( i = 0; i < (g->edgeCount) ; i++) {
      currEdge = *(g->edge + i)  ;
      u = currEdge.src ;
      v = currEdge.dest ;
      
      if (findSet(u->set_ref) != findSet(v->set_ref)) {
         mst->edgeCount = mst->edgeCount  + 1;
         //this is a safe edge to add to our  mst graph
         //add it to the resulting graph
         //mke a copy of the edge and its vertices, we dont want to mess the original graph
         tempEdge.wt = currEdge.wt ;
         tempEdge.dest = createVertex( (currEdge.dest)->val  ) ;
         tempEdge.src = createVertex( (currEdge.src)->val  ) ;

         mst->edges = (Edge_p) realloc(mst->edges, (mst->edgeCount) * sizeof(Edge_t) ) ;
         *(mst->edges + (mst->edgeCount) - 1) = tempEdge ;
         Union(u->set_ref, v->set_ref) ;
      }

   }
   
   return mst ;
}

size_t getMSTWeight(Graph_p g) {

   MSTGraph_p mst =  mst_Kruskal(g) ;
   int mstWt = 0;
   size_t i = 0;

   for(i = 0; i < (mst->edgeCount); i++) {
      mstWt = mstWt + ((mst->edges + i)->wt    )    ;
   }

   return mstWt ;
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

   addEdge(g, v_A, v_B, 12) ;
   addEdge(g, v_A, v_C, 4) ;
   addEdge(g, v_C, v_D, 9) ;
   addEdge(g, v_D, v_E, 8) ;
   addEdge(g, v_B, v_D, 7) ;
   addEdge(g, v_B, v_E, 10) ;
   
   MSTGraph_p mst =  mst_Kruskal(g) ;
   printf("\n The weight of the MST is : %ld \n", getMSTWeight(g)) ;
   printf("\n The weight of the MST is : %ld \n", getMSTWeight(g)) ;
   return 0;
}
