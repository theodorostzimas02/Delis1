#include <iostream>
#include "InvertedIndex.h"
#include "ZIPNode.h"
#include "Voter.h"
using namespace std;

InvertedIndex::~InvertedIndex(){
    ZIPNode* currentZIP = PostalCodes;
    while (currentZIP) {
        ZIPNode* nextZIP = currentZIP->next;
        Node* currentNode = currentZIP->head;
        while (currentNode) {
            Node* nextNode = currentNode->next;
            delete currentNode; 
            currentNode = nextNode;
        }
        delete currentZIP; 
        currentZIP = nextZIP;
    }
}

ZIPNode* InvertedIndex::Search(int ZIP) {
    ZIPNode* current = PostalCodes;
    while (current) {
        if (current->ZIP == ZIP) {
            return current; 
        }
        current = current->next;
    }
    return nullptr; 
}

int InvertedIndex::Size() {
    ZIPNode* current = PostalCodes;
    int count = 0;
    while (current) {
        count++;
        current = current->next; 
    }
    return count;
}

void InvertedIndex::Insert(Voter* voter) {
    int ZIP = voter->ZIPCode;
    ZIPNode* current = PostalCodes;
    while (current) {
        if (current->ZIP == ZIP) {
            Node* newNode = new Node(voter, nullptr);
            if (current->tail) {
                current->tail->next = newNode;
            } else {
                current->head = newNode;
            }
            current->tail = newNode;
            current->ZIPCount++;
            VotersCount++;
            return;
        }
        current = current->next;
    }

    ZIPNode* newZIPNode = new ZIPNode();
    newZIPNode->ZIP = ZIP;
    newZIPNode->next = PostalCodes;
    PostalCodes = newZIPNode;

    Node* newNode = new Node(voter, nullptr);
    newZIPNode->head = newNode;
    newZIPNode->tail = newNode;

    newZIPNode->ZIPCount++;
    VotersCount++;

}


void InvertedIndex::Print(int ZIP) {
    ZIPNode* currentZIPNode = Search(ZIP); 
    if (currentZIPNode) {
        cout << "ZIP: " << currentZIPNode->ZIP << endl;
        Node* currentNode = currentZIPNode->head;
        while (currentNode) {
            cout << " Voter PIN: " << currentNode->voter->PIN << endl;
            cout << " First Name: " << currentNode->voter->firstName << endl;
            cout << " Last Name: " << currentNode->voter->lastName << endl;
            cout << " ZIP: " << currentNode->voter->ZIPCode << endl;
            cout << endl;
            currentNode = currentNode->next;
        }
    } else {
        cout << "ZIP: " << ZIP << " not found." << endl;
    }
}

void InvertedIndex::PrintAllIndex() {
    ZIPNode* currentZIPNode = PostalCodes;
    while (currentZIPNode) {
        cout << currentZIPNode->ZIP << " | ";
        Node* currentNode = currentZIPNode->head;
        while (currentNode) {
            cout << currentNode->voter->PIN << " / ";
            currentNode = currentNode->next;
        }
        cout << endl; 
        currentZIPNode = currentZIPNode->next;
    }
}


