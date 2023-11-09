#pragma once

class Voter{
public:
    int PIN;
    int ZIPCode;
    bool hasVoted;
    char* firstName;
    char* lastName;
    void PrintVoter();
    Voter(int PIN,char* firstName,char* lastName ,int ZIPCode);
    ~Voter();
};

