#pragma once
#include "Node.h"

class ZIPNode{
    public:
    int ZIP;
    Node* head;
    Node* tail; 
    ZIPNode* next;
    int ZIPCount=0;
    ZIPNode();
};
