#include "Bucket.h"
#include "Voter.h"

extern int bucketentries;

class HashTable{
public:
    float loadFactor;
    int bucketSize=bucketentries;    
    int orBuckets = 2; //original number of buckets
    int curBuckets = orBuckets; //current number of buckets
    int round = 0;
    Bucket** hashTable;
    Bucket* p;

    void Insert(Voter* voter);
    void Split();
    Voter* Search(int PIN);
    float GetLoadFactor();
    int FindpIndex();
    int TotalKeys();
    int overFlowKeys();
    void PrintTable();
    int HashFunction(int PIN, int i, int m);
    HashTable();
    ~HashTable();
};