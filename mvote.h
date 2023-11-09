#include "HashTable.h"
#include "InvertedIndex.h"

class mvote{
    public:
    HashTable catalog;
    InvertedIndex ZIPIndex;

    void l_search(int PIN);
    void i_add(int PIN, char* lname, char * fname,int ZIP);
    void m_changeVote(int PIN);
    void v_votersCount();
    void bv_readVoters(const char* filename);
    void perc();
    void z_IndexVoters(int ZIP);
    void o_sort();
    void read_file(const char* filename);
    void pr_printTable();
    void BubbleSort(ZIPNode** zipArray, int numofZIP);
};