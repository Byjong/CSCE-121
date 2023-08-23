#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList {

    size_t size;
    Node* head;
    Node* tail;

public:
    LinkedList();
    LinkedList(const LinkedList& ll);
    LinkedList& operator=(const LinkedList& rhs);
    Node* getHead() const noexcept;
    Node* getTail() const noexcept; 
    const Node& at(size_t pos) const;
};

#endif 