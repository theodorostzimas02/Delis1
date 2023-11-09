#include <iostream>
#include <cstring>
#include "mvote.h"
using namespace std;

void mvote::l_search(int PIN){
    Voter* searchv = catalog.Search(PIN);
    if(searchv){
            searchv->PrintVoter();
    }
    else {
        cout << "User with PIN: " <<PIN << " doesnt exist!!" << endl;
    }


    return;
}

void mvote::i_add(int PIN, char* lname, char* fname,int ZIP){
    Voter* newVoter = new Voter(PIN, lname, fname, ZIP);
    catalog.Insert(newVoter);
    return;
}

void mvote::m_changeVote(int PIN){
    Voter* searchv = catalog.Search(PIN);
    if (searchv){
        if (searchv->hasVoted == false){
            searchv->hasVoted = true;
            ZIPIndex.Insert(searchv);
            cout << "Voter with PIN: " <<searchv->PIN << " has voted." << endl; 
        }
        else{
            cout << "Voter with PIN: " <<searchv->PIN << " has already voted." << endl; 
        }
        
    }
    else{
        cout << "Voter with PIN: " <<searchv->PIN << " doesnt exist." << endl; 
    }
    return;
}

void mvote::v_votersCount(){
    cout << ZIPIndex.VotersCount << " people have voted." <<endl;
    return;
}

void mvote::perc(){
    float percentage = float(ZIPIndex.VotersCount * 100) / float (catalog.TotalKeys()+catalog.overFlowKeys()) ;
    cout << percentage << "% of voters has voted." << endl;;
}

void mvote::z_IndexVoters(int ZIP){
    ZIPNode* newZIP = ZIPIndex.Search(ZIP);
    if (newZIP){
        cout <<"For ZIP: " << ZIP << " we have " << newZIP->ZIPCount << " voters" <<endl;
        cout << "List of voters: " << endl;
        ZIPIndex.Print(ZIP);
    }
    else{
        cout << "No voters with ZIP:" << ZIP << endl;
    }
    return;
}

void mvote::BubbleSort(ZIPNode** zipArray, int numofZIP) {
    for (int i = 0; i < numofZIP - 1; i++) {
        for (int j = 0; j < numofZIP - i - 1; j++) {
            if (zipArray[j]->ZIPCount < zipArray[j + 1]->ZIPCount) {
                ZIPNode* temp = zipArray[j];
                zipArray[j] = zipArray[j + 1];
                zipArray[j + 1] = temp;
            }
        }
    }
}

void mvote::o_sort() {
    int numofZIP = ZIPIndex.Size();
    cout << "Number of ZIPs: " << numofZIP << endl;
    ZIPNode** zipArray = (ZIPNode**)malloc(sizeof(ZIPNode*) * numofZIP);
    ZIPNode* currentZIP = ZIPIndex.PostalCodes;

    int i = 0;
    while (currentZIP) {
        zipArray[i] = currentZIP;
        currentZIP = currentZIP->next;
        i++;
    }

    BubbleSort(zipArray, numofZIP);

    for (int i = 0; i < numofZIP; i++) {
        cout << "ZIP: " << zipArray[i]->ZIP << " ZIPCount: " << zipArray[i]->ZIPCount << endl;
    }

    free(zipArray); 
}


void mvote::bv_readVoters(const char* filename){
    FILE *file = fopen(filename, "r");

    if (file == NULL){
        cout << "Error: Could not open the file." << endl;
        return;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, " ");
        int PIN = atoi(token);
        if (token != NULL) {
            m_changeVote(PIN);
        }
    }
}


void mvote::read_file(const char* filename){
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        cout << "Error: Could not open the file." << endl;
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, " ");
        int count = 0;
        int PIN;
        char firstName[50];
        char lastName[50];
        int ZIPCode;

        while (token != NULL) {
            if (count == 0) {
                PIN = atoi(token);
            } else if (count == 1) {
                strcpy(lastName, token);
            } else if (count == 2) {
                strcpy(firstName, token);
            } else if (count == 3) {
                ZIPCode = atoi(token);
            }
            token = strtok(NULL, " ");
            count++;
        }
        Voter* newVoter = new Voter(PIN, lastName, firstName, ZIPCode);
        catalog.Insert(newVoter);
    }
    fclose(file);
    return;
}

void mvote::pr_printTable(){
    catalog.PrintTable();
}