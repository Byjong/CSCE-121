#include "Node.h"
#include <iostream>

class Node {
public:
   LinkedListNode(int dataValue) {
      cout << "In LinkedListNode constructor (" << dataValue << ")" << endl;
      data = dataValue;
   }
    
   ~LinkedListNode() {
      cout << "In LinkedListNode destructor (";
      cout << data << ")" << endl;
   }
    
   int data;
    Node* next;
};
