#pragma once

#include "ZIPNode.h"
#include "Voter.h"

class InvertedIndex{
    public:
    ZIPNode* PostalCodes = nullptr;
    int VotersCount=0;
    
    ZIPNode* Search(int ZIP);
    void Print(int ZIP);
    void PrintAllIndex();
    void Insert(Voter* voter);
    int Size();
    ~InvertedIndex();
};
