#include <iostream>
#include <cstring>
#include <cstdlib>
#include "mvote.h"
using namespace std;

int bucketentries;

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Usage: " << argv[0] << " -f <input_file> -b <bucket_entries>" << endl;
        return 1;
    }

    const char* filename = nullptr;

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-f") == 0) {
            filename = argv[i + 1];
        } else if (strcmp(argv[i], "-b") == 0) {
            bucketentries = atoi(argv[i + 1]);
        } else {
            cout << "Invalid argument: " << argv[i] << endl;
            return 1;
        }
    }

    if (filename == nullptr || bucketentries < 0) {
        cout << "Invalid arguments." << endl;
        return 1;
    }

    
    mvote election; 
    election.read_file(filename);
    while (true) {
        char input[50];
        cout << "Enter a command: ";
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';  // Remove the newline character



        char* token = strtok(input, " ");
        if (token == NULL) {
            cout << "Invalid command. Please try again." << endl;
            continue;
        }

        if (strcmp(token, "l") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) {
                int PIN = atoi(token);
                election.l_search(PIN);
            }
        } else if (strcmp(token, "i") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) {
                int PIN = atoi(token);
                token = strtok(NULL, " ");
                char* lastName;
                if (token != NULL) {
                    strncpy(lastName,token,sizeof(token));
                    token = strtok(NULL, " ");
                    char* firstName;
                    if (token != NULL) {
                        strncpy(lastName,token,sizeof(token));
                        token = strtok(NULL, " ");
                        if (token != NULL) {
                            int ZIP = atoi(token);
                            election.i_add(PIN, firstName, lastName, ZIP);
                        }
                    }
                }
            }
        } else if (strcmp(token, "m") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) {
                int PIN = atoi(token);
                election.m_changeVote(PIN);
            }else{
                cout << "Give a PIN please!" << endl;
            }
        } else if (strcmp(token, "bv") == 0) {
            token = strtok(NULL, " ");
            char filename[50];
            if (token != NULL) {
                strcpy(filename, token);
                election.bv_readVoters(filename);
            }
        } else if (strcmp(token, "v") == 0) {
            election.v_votersCount();
        } else if (strcmp(token, "perc") == 0) {
            election.perc();
        } else if (strcmp(token, "z") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) {
                int ZIP = atoi(token);
                election.z_IndexVoters(ZIP);
            }else{
                cout << "Give a ZIP please!" << endl;
            }
        } else if (strcmp(token, "o") == 0) {
            election.o_sort(); 
        } else if (strcmp(token, "exit") == 0) {
            cout << "Exiting the program." << endl;
            return 0;
        } else if (strcmp(token, "pr") == 0){
            election.pr_printTable();
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    return 0;
}