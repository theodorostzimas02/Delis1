#include "Node.h"

Node::Node(Voter* voter, Node* next) {
    this->voter = voter;
    this->next = next;
}
