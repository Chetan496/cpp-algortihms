#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define CREATE_NEW(type) (type*)malloc(sizeof(type))  //wrapper for creating ptr objects by allocating memory from heap
#define APPEND_TO_LINKLIST(firstNode, newNode, tempNode) \
   if( firstNode == NULL ) { \
      firstNode = newNode ; \
   } \
   else {      \
      tempNode = firstNode; \
      while (tempNode->next != NULL) { \
         tempNode = tempNode->next; \
      } \
      tempNode->next = newNode; \
   }  
/*
 *Note: This implementation of the graph data structure here is based on the description of Graph using Adjacency linklist
 found at this url: https://www.cs.bu.edu/teaching/c/graph/linked/

 This implementation is for a directed graph
 */
typedef char graphElementT;
/*
 *For each vertex, we need to store an element, its visited flag, its list of edges and a link to the next vertex
 */
typedef struct vertexTag {
   graphElementT element;
   bool visited;
   struct edgeTag* edges;
   struct vertexTag* next;
} vertexT;
/* For each edge, we need a link to the vertex it connects to and a link to the next edge w.r.t source vertex*/
typedef struct edgeTag {
   vertexT* connectsTo;
   struct edgeTag* next;
} edgeT;

typedef struct graphCDT {
  vertexT* vertices; 
} graphCDT;

typedef struct graphCDT* graphADT;

/*
 *Graph Operations:
 1. GraphAddVertex()
 2. GraphAddEdge()
 3. GraphIsReachable()
 */

graphADT GraphCreate(){
   /* Creates an empty graph, with no vertices. Allocate memory from the heap */
   graphADT emptyGraph = CREATE_NEW(graphCDT) ;
   emptyGraph->vertices = NULL;
   return emptyGraph;
}

vertexT* getVertex(graphADT graph, graphElementT elem){
   /*search for a vertex in graph having the input elem.
    * Return it
    * Return NULL if not found*/
   vertexT* temp = graph->vertices;
   while(temp != NULL && temp->element != elem) {
      temp = temp->next;
   }
   return temp;
}

void GraphAddEdge(vertexT* from, vertexT* to){
/*This function adds a edge in our graph from the vertex "from" to the vertex "to" */
   if(from == NULL || to == NULL){
      fprintf(stdout, "\n Either of the vertices do not exist \n") ;
      return;
   }
   edgeT* newEdge = CREATE_NEW(edgeT) ;
   newEdge->connectsTo = to;
   newEdge->next = NULL;
   edgeT* tempEdge=NULL;
   APPEND_TO_LINKLIST(from->edges, newEdge, tempEdge);
   fprintf(stdout, "\n Added the edge from %c to %c \n", from->element, to->element) ;
}

void GraphAddVertex(graphADT graph , graphElementT elem){
   /* given a char to insert as a new vertex, this function will create a new vertex with that char*/
   if ( getVertex (graph, elem) != NULL ) {
      fprintf(stderr, "\n Error! The vertex already exists in the graph \n");
   }else{
      vertexT* newVertex = CREATE_NEW(vertexT) ;
      newVertex->next = NULL;
      newVertex->visited = false;
      newVertex->element = elem;
      newVertex->edges = NULL;
      /*insert this new vertex at the end of the vertex list of the graph */
      vertexT* tempNode = NULL;
      APPEND_TO_LINKLIST(graph->vertices, newVertex, tempNode) ;
      fprintf(stdout, "\n Added the vertex in the graph \n") ;
   }
}


void markAllVerticesNotVisited(graphADT graph){
   /* iterate through all the vertices. Set visited = false*/
   /* This method is required so that GraphIsReachable runs successfully for all all function calls */
   vertexT* temp = graph->vertices;
   while(temp!=NULL) {
      temp->visited = false;
      temp = temp->next;
   }
}

bool GraphIsReachable(graphADT graph, vertexT* src, vertexT* dest) {
   /*This method returns if a vertex called dest is reachable from the vertex called source */
   /* first set visited = false for all vertices */
   if (src == dest) {
      return true;
   }else if(src->visited == true){
      return false;
   }else{
      //visit all edges of vertexT* src
      src->visited = true;
      edgeT* tempe = src->edges;  //the first edge outgoing from this vertex
      while(tempe != NULL){
         if (GraphIsReachable(graph, tempe->connectsTo , dest) == false ) {
            tempe = tempe->next;
         }else{
            return true;
         }
      }
   }
   return false;
}

bool isDestReachable(graphADT graph, graphElementT from, graphElementT to) {
   if(graph == NULL){
      return false;
   }else{
      vertexT* src = getVertex(graph,from);
      vertexT* dest = getVertex(graph,to);
      if(src == NULL || dest == NULL) {
         return false;
      }else{
         /*The graph is not null. The vertices do exist in the graph. Get to work! find if dest is rechable from src */
         /*first set visited = false for all vertices */
         markAllVerticesNotVisited(graph);
         return GraphIsReachable(graph, src, dest);
      }
   }
}

int main(){
   graphADT graph = GraphCreate() ;
   GraphAddVertex(graph, 'A') ;
   GraphAddVertex(graph, 'B') ;
   GraphAddVertex(graph, 'C') ;
   GraphAddVertex(graph, 'D') ;
   GraphAddVertex(graph, 'E') ;
   
   GraphAddEdge( getVertex(graph, 'A'), getVertex(graph, 'C') ) ;
   GraphAddEdge( getVertex(graph, 'C'), getVertex(graph, 'D') ) ;
   GraphAddEdge( getVertex(graph, 'D'), getVertex(graph, 'E') ) ;
   GraphAddEdge( getVertex(graph, 'B'), getVertex(graph, 'E') ) ;

   printf("\n Is vertex E reachable from A? : %s \n ",   isDestReachable(graph, 'A', 'E')==true?"True":"False" ) ;
   printf("\n Is vertex E reachable from B? : %s\n ",    isDestReachable(graph, 'B', 'E')==true?"True":"False" ) ;
   printf("\n Is vertex D reachable from A? : %s \n ",   isDestReachable(graph, 'A', 'D')==true?"True":"False" ) ;
   printf("\n Is vertex E reachable from D? : %s \n ",   isDestReachable(graph, 'D', 'E')==true?"True":"False" ) ;
   printf("\n Is vertex B reachable from A? : %s \n ",   isDestReachable(graph, 'A', 'B')==true?"True":"False" ) ;
   printf("\n Is vertex D reachable from C? : %s \n ",   isDestReachable(graph, 'C', 'D')==true?"True":"False" ) ;
   return 0;
}
