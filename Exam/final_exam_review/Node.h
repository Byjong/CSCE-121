#ifndef NODE_H
#define NODE_H

struct Node {

    int num;
    Node* next;
    Node* prev;

    Node();
    Node(int val);
    ~Node();
    Node(const Node& node);
    Node& operator=(const Node& rhs);
};

#endif