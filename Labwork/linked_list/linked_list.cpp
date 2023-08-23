#include "linked_list.h"
#include <iostream>
#include <string>

using std::cout, std::endl, std::string, std::ostream;

void MyList::add(const std::string& name, int score) {
    
    MyNode* new_node = new MyNode(name, score);
    
    if(this->_size == 0){
        this->_head = new_node;
        this->_tail = new_node;
    }
    else{
        new_node->prev = _tail;
        _tail->next = new_node;
        _tail = new_node;
    }
    _size++;
}

void MyList::clear() {
    if(_size > 1){
        for(size_t i = 0; i < this->_size; ++i){
            MyNode* curr_node = this->_tail;
            _tail = curr_node->prev;
            delete curr_node;
        }
    }
    else if(this->_size == 1){
        delete _head;
    }
    this->_size = 0;
}

bool MyList::remove(const std::string& name) {
    // TODO(student)
    return false;
}

bool MyList::insert(const std::string& name, int score, size_t index) {
    // TODO(student)
    return false;
}

MyList::MyList()
  : _size(0), _head(nullptr), _tail(nullptr) { }

MyList::~MyList() {
    clear();
}

size_t MyList::size() const {
    return _size;
}

bool MyList::empty() const {
    return _head == nullptr;
}

MyNode* MyList::head() const {
    return _head;
}

ostream& operator<<(ostream& os, const MyList& myList) {
    MyNode* _current = myList.head();
    if (_current == nullptr) {
        os << "<empty>" << endl;
        return os;
    }

    os << "[ " << _current->name << ", " << _current->score << " ]";
    _current = _current->next;
    while (_current != nullptr) {
        os << " --> [ " << _current->name << ", " << _current->score << " ]";
        _current = _current->next;
    }
    
    return os;
}

MyNode::MyNode(const std::string& name, int score)
    : name{name}, score{score}, next{nullptr}, prev{nullptr} {}
