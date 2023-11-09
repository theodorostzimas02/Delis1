#pragma once
#include "Node.h"

class Bucket{
public:
    Node* head = nullptr;
    Node* tail = nullptr;
    int NumOfKeys=0;
    int overflowed=0;
    
    int GetNumOfKeys();
    int GetOverflowed(); // Function to find the number of overflowed keys (> 2)
};
