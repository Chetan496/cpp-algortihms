#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

/* A graph is just a collection of vertices and their adjacency lists*/
/*
 * Vertex    Adjacency List
 *A           B, C, D
  B            A, C
  C            A, B
  D            A
eg: in above undirected graph, vertices are A, B and C.  edges are AB, AC and BC and AD

 *
 */

typedef struct Graph_t {
  Vertex_p headVertex; 
}Graph_t, *Graph_p;


/*returns a empty undirected graph */
Graph_p createGraph(){
   Graph_p graph= (Graph_p) malloc(sizeof(Graph_t)) ;
   graph->headVertex = NULL;   //empty graph
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

void addEdge(Vertex_p src, Vertex_p dest) {
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

int main(){
   Graph_p graph = createGraph()  ;
   Vertex_p vp_A = createVertex('A');
   Vertex_p vp_B = createVertex('B');
   Vertex_p vp_C = createVertex('C');
   Vertex_p vp_D = createVertex('D');

   addVertex(graph, vp_A);
   addVertex(graph, vp_B);
   addVertex(graph, vp_C);
   addVertex(graph, vp_D);
   
   addEdge(vp_A, vp_B);
   addEdge(vp_A, vp_C);
//   addEdge(vp_A, vp_D);

   printf("\n Is there a path from %c to %c: %s \n", vp_A->val, vp_B->val, isDestReachable(graph, vp_A, vp_B)==true?"True":"False") ;
   printf("\n Is there a path from %c to %c: %s \n", vp_B->val, vp_C->val, isDestReachable(graph, vp_B, vp_C)==true?"True":"False") ;
   printf("\n Is there a path from %c to %c: %s \n", vp_A->val, vp_D->val, isDestReachable(graph, vp_A, vp_D)==true?"True":"False") ;
   return 0;
}
