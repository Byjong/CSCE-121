#include <string>
#include "Node.h"

using namespace std;

// Default constructor
Node::Node(): data(TemperatureData()), next(nullptr) {} // remember to initialize next to nullptr

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature): data(TemperatureData(id, year, month, temperature)), next(nullptr) {}
// remember to initialize next to nullptr

Node::Node(const Node& node) : data(TemperatureData()), next(node.next) {}

Node& Node::operator=(const Node& node) {
	delete this->next;
	this->next = node.next;
	this->data = node.data;
	return *this;
}

bool Node::operator<(const Node& b) {
	return this->data < b.data;
}