#include "Voter.h"
#pragma once

class Node{
public:
    Voter* voter;
    Node* next;
    Node(Voter* voter, Node* next);
};