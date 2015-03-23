typedef struct Node {
   int data;
   struct Node* next ;
}Node ;

typedef Node* NodePtr;

typedef struct LinkList {
  NodePtr firstNode; 
}LinkList ;
