#include <iostream>
#include "Bucket.h"

extern int bucketentries;

int Bucket::GetNumOfKeys(){
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    if (count > bucketentries) {
        return count - bucketentries;
    }
    return 0;
}

int Bucket::GetOverflowed() {
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    if (count > bucketentries) {
        return count - bucketentries;
    }
    return 0;
}
