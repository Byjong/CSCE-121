#include <stdexcept>
#include "linked_list.h"

int LinkedList::at(size_t index) const {

  int val = 0;

  if (index >= this->size()) {
    throw std::out_of_range("Index out of bounds.");
  }

  const Node* node = this->get_head();

  size_t idx = 0;

  while (idx < this->size()) {
    if (idx == index) {
      val = node->value;
    }
    node = node->next;
  }

  return val;
}

void LinkedList::insert(size_t index, int value) {

  if (index >= this->size()) {
    throw std::invalid_argument("Invalid index.");
  }

  Node* add_node = new Node(value);

  if (this->head == nullptr) {
    this->head = add_node;
    return;
  }

  Node* curr = this->head;
  size_t idx = 0;

  while (idx < this->size()) {
    if (idx == index) {
      add_node->next = curr;


      curr = curr->next;
      idx++;
    }
  }
}

void LinkedList::merge(const LinkedList& other) {

  if (other.get_head() == nullptr) {
    return;
  }

  size_t idx = 0;
  size_t count = 0;

  const Node* add_node = other.get_head();


  while (idx < this->size()) {
    if (idx % 2 == 1) {
      this->insert(idx, add_node->value);
      add_node = add_node->next;
      ++count;
    }
    ++idx;
  }

  if (count < other.size()) {
    while (count < other.size()) {
      this->insert((this->size() - 1), add_node->value);
      add_node = add_node->next;
    }
  }
}