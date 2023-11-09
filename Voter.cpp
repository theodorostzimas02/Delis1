#include "Voter.h"
#include <iostream>
#include <cstring>
using namespace std;

Voter::Voter(int PIN,char* firstName,char* lastName ,int ZIPCode){
    this->PIN = PIN;
    this->lastName = strdup(lastName);
    this->firstName = strdup(firstName);
    this->ZIPCode = ZIPCode;
    this->hasVoted = false;
}

Voter::~Voter(){
    free(firstName);
    free(lastName);
}

void Voter::PrintVoter() {
    cout << "PIN: " << PIN << " Last Name: " << lastName << " First Name: " << firstName << " ZIP Code: " << ZIPCode << " Has Voted: " << (hasVoted ? "Yes" : "No") <<endl;
}

