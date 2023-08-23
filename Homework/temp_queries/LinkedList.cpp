#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

LinkedList::~LinkedList() {
	clear();
}

LinkedList::LinkedList(const LinkedList& source) : head(nullptr), tail(nullptr) {
    Node* src_node = source.getHead();

    if(!src_node){
        return;
    }

    TemperatureData data = src_node->data;
    this->head = new Node(data.id, data.year, data.month, data.temperature);
    Node* curr_node = this->head;

    while(src_node->next != nullptr){
        src_node = src_node->next;
        curr_node->next = new Node(src_node->data.id, src_node->data.year, src_node->data.month, src_node->data.temperature);
        curr_node = curr_node->next;
    }
    this->tail = curr_node;
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	Node* src_node = source.getHead();

    TemperatureData data = src_node->data;
    this->head = new Node(data.id, data.year, data.month, data.temperature);
    Node* curr_node = this->head;

    while(src_node->next != nullptr){
        src_node = src_node->next;
        curr_node->next = new Node(src_node->data.id, src_node->data.year, src_node->data.month, src_node->data.temperature);
        curr_node = curr_node->next;
    }
    this->tail = curr_node;
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	if(temperature == -99.99){
		return;
	}

	Node* add_node = new Node(location, year, month, temperature);

	if (this->head == nullptr) {
		this->head = add_node;
		this->tail = add_node;
		return;
	}

	if(*add_node < *this->head){
		add_node->next = this->head;
		this->head = add_node;
		return;
	}

	if(*this->tail < *add_node){
		this->tail->next = add_node;
		this->tail = add_node;
		return;
	}
	
	Node* curr = this->head;
	while (*curr < *add_node) {
		add_node->next = curr;
		curr = curr->next;
	}

	add_node->next->next = add_node;
	add_node->next = curr;
}

void LinkedList::clear() {
	if(this->head == nullptr){
		return;
	}

	Node* curr = this->head;
	Node* next;
	while (curr != nullptr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
	this->head = nullptr;
	this->tail = nullptr;
}

Node* LinkedList::getHead() const {
	return this->head;
}

string LinkedList::print() const {
	string outputString = string();
	Node* node = this->head;
	while (node != nullptr) {
		string temp = to_string(node->data.temperature);
		temp.erase(temp.find_last_not_of('0') + 1, string::npos);

		if(temp.at(temp.length()-1) == '.'){
			temp.erase(temp.length() - 1 , string::npos);
		}

		outputString += node->data.id
			+ " " + to_string(node->data.year)
			+ " " + to_string(node->data.month)
			+ " " + temp
			+ "\n";
		node = node->next;
	}
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
