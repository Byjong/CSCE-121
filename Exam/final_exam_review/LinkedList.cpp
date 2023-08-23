#include <iostream>
using namespace std;

class LinkedList {
public:
   LinkedList();
   ~LinkedList();
   void Prepend(int dataValue);
    
   LinkedListNode* head;
};

LinkedList::LinkedList() {
   cout << "In LinkedList constructor" << endl;
   head = nullptr;
}

LinkedList::~LinkedList() {
   cout << "In LinkedList destructor" << endl;
    
   // The destructor deletes each node in the linked list
   while (head) {
      LinkedListNode* next = head->next;
      delete head;
      head = next;
   }
}

void LinkedList::Prepend(int dataValue) {
   LinkedListNode* newNode = new LinkedListNode(dataValue);
   newNode->next = head;
   head = newNode;
}