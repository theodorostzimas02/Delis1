#include <iostream>
#include "HashTable.h"
using namespace std;

HashTable::HashTable(){
    hashTable = (Bucket**)malloc(bucketSize * sizeof(Bucket*));
    for (int j = 0; j < bucketSize; j++) {
        hashTable[j] = new Bucket();
    }
    p = hashTable[0];
}

int HashTable::HashFunction(int PIN, int i, int m) {   
    return PIN % ((1 << i) * m);            // << is shifting so it's 2^i
}

int HashTable::FindpIndex() {
    for (int j = 0; j < curBuckets; j++) {
        if (hashTable[j] == p) {
            return j; // Return the index of p
        }
    }
    return -1;
}

int HashTable::TotalKeys(){
    int sum=0;
    for (int j = 0; j < curBuckets; j++){
        sum += hashTable[j]->NumOfKeys;
    }
    return sum;
}

int HashTable::overFlowKeys() {
    int overflowedKeys = 0;
    for (int j = 0; j < curBuckets; j++) {
        overflowedKeys += hashTable[j]->overflowed;
    }
    return overflowedKeys;
}

void HashTable::PrintTable() {
    for (int j = 0; j < curBuckets; j++) {
        cout << j << ": |";
        Node* current = hashTable[j]->head;
        int count = 0 ;
        for (int k = 0; k <  hashTable[j]->NumOfKeys + hashTable[j]->overflowed ; k++) {
            if (current) {
                cout << "  " << current->voter->PIN;
                current = current->next;
                count++;
            } else {
                cout << ""        "";
            }
            cout << "|";
            if (count % 2 == 0 && current){
                    cout << " --> ";
                    count = 0;
                }
        }
        cout << endl;;
    }
    cout <<"Round:" << round << endl;
    cout << "Keys:" << TotalKeys() << endl;
    cout <<"Overflow Keys:" << overFlowKeys() << endl;
    cout << endl;
}

float HashTable::GetLoadFactor(){
    float lamda = float(TotalKeys()+overFlowKeys()) / float((bucketSize * curBuckets));
    return lamda;
}

Voter* HashTable::Search(int PIN) {
    int hash = HashFunction(PIN, round, bucketentries);
    if (hash < FindpIndex()) {
        hash = HashFunction(PIN, round + 1, bucketentries);
    }

    Node* current = hashTable[hash]->head;
    while (current) {
        if (current->voter->PIN == PIN) {
            return current->voter; 
        }
        current = current->next;
    }
    return nullptr;
}



void HashTable::Insert(Voter* voter) {
    int hash = HashFunction(voter->PIN, round,bucketentries);
    if (hash < FindpIndex()){
        
        hash = HashFunction(voter->PIN, round+1 , bucketentries);
    }
    // Does the key already exists?
    Node* current = hashTable[hash]->head;
    while (current) {
        if (current->voter->PIN == voter->PIN) {
            cout << "Key " << voter->PIN << " already exists." << endl;
            return;
        }
        current = current->next;
    }
    // Insert the new key
    Node* newNode = new Node(voter, nullptr);
    if (hashTable[hash]->NumOfKeys < bucketentries) {
        Node* current = hashTable[hash]->head;
        if (!current) {
            hashTable[hash]->head = newNode;
            
        } else {
            hashTable[hash]->tail->next = newNode;
        }
        hashTable[hash]->tail = newNode;
        hashTable[hash]->NumOfKeys++;
    } else {
        hashTable[hash]->overflowed++ ;
        Node* current = hashTable[hash]->head;
        if (!current) {
            hashTable[hash]->head = newNode;
            hashTable[hash]->tail = newNode;
        } else { //Key inserted in an overflowed bucket.
            hashTable[hash]->tail->next = newNode;
            hashTable[hash]->tail = newNode;
        }
    }
    voter->PrintVoter();
    cout << "Voter has been sucessfully added to the system" << endl;
    if (GetLoadFactor() > 0.75) {
        Split();    
    }
}

HashTable::~HashTable() {
    for (int j = 0; j < curBuckets; j++) {
        Node* current = hashTable[j]->head;
        while (current) {
            Node* next = current->next;
            delete current->voter;
            delete current; 
            current = next;
        }
        delete(hashTable[j]); 
    }
    free(hashTable);
}

void HashTable::Split() {
    curBuckets++;
    hashTable = (Bucket**)realloc(hashTable, curBuckets * sizeof(Bucket*));
    hashTable[curBuckets - 1] = new Bucket();
    int pIndex = FindpIndex();

    // Create a new bucket for p
    Bucket* newPBucket = new Bucket();

    Node* current = p->head;
    while (current) {
        int hash = HashFunction(current->voter->PIN, round + 1, bucketentries);
        Node* next = current->next;

        if (pIndex == hash) {
            if (newPBucket->NumOfKeys >=bucketentries){
                newPBucket->overflowed++;
            }else{
                newPBucket->NumOfKeys++;
            }
            if (newPBucket->head == nullptr) {
                newPBucket->head = current;
                newPBucket->tail = current;
            } else {
                Node* last = newPBucket->head;
                newPBucket->tail->next = current;
                newPBucket->tail = current;
            }
        } else {
                if (hashTable[hash]->NumOfKeys >=bucketentries){
                    hashTable[hash]->overflowed++;
                }else{
                    hashTable[hash]->NumOfKeys++;
                }
                Node* last = hashTable[hash]->head;
                if (hashTable[hash]->head == nullptr){
                    hashTable[hash]->head = current;
                    hashTable[hash]->tail = current;
                }
                else{
                    hashTable[hash]->tail->next = current;
                    hashTable[hash]->tail = current;
                }
                
        }
        current->next = nullptr;
        current = next;
        
    }

    delete p; // Delete the old p bucket

    // Update the p pointer and the hash table
    hashTable[pIndex] = newPBucket;
    p = hashTable[pIndex+1];

    if (curBuckets / orBuckets == 2) {
        round++;
        orBuckets = curBuckets;
        p = hashTable[0];
    }
}