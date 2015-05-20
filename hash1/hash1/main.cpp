#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HASHTABLE {
public:
    HASHTABLE();
    ~HASHTABLE();
    bool Add(const string&);
    bool Delete(const string&);
    bool Has(const string&);
private:
    double loadFactor;
    int HashParamA;
    int initSize;
    int usedSize;
    
    vector<string> table;
    vector<bool> deleted;
    
    int getHash(const string&, size_t);
    void growTable();
};


HASHTABLE::HASHTABLE() {
    loadFactor = 0.75;
    initSize = 8;
    usedSize = 0;
    
    table = vector<string>(initSize);
    deleted = vector<bool>(initSize);
}


HASHTABLE::~HASHTABLE() {
}


//                              -- value -- table size --
int HASHTABLE::getHash(const string& data, size_t m) {
    int result = 0;
    for (int i = 0; i < static_cast<int>(data.length()); ++i) {
        result = (result*37 + data[i]) % m;
    }
    return result;
}


void HASHTABLE::growTable() {
    vector<string> newTable(table.size() * 2);
    vector<bool> newDeleted(deleted.size() * 2);
    deleted = newDeleted;
    
    for (int j = 0; j < table.size(); ++j) {
        int hash = getHash(table[j], newTable.size());
        for (int i = 0; i < newTable.size(); ++i){
            if (newDeleted[hash] == false){
                newTable[hash] = table[j];
                newDeleted[hash] = true;
                break;
            }
        }
    }
    table = newTable;
}


bool HASHTABLE::Has(const string& data){
    int hash = getHash(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        int actual_hash = (hash + i*(i + 1)/2) % table.size();
        if (table[actual_hash] == data && !deleted[actual_hash]) {
            return true;
        }
    }
    return false;
}


bool HASHTABLE::Add(const string& data){
    if (usedSize + 1 > loadFactor * table.size()) {
        growTable();
    }
    int hash = getHash(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        int actual_hash = (hash + i*(i + 1)/2) % table.size();
        if (table[actual_hash] == data && !deleted[actual_hash])
            return false;
        if (!deleted[actual_hash]){
            table[actual_hash] = data;
            deleted[actual_hash] = false; // ???
            ++usedSize;
            return true;
        }
    }
    return false;
}


bool HASHTABLE::Delete(const string& data){
    int hash = getHash(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        int actual_hash = (hash + i*(i + 1)/2) % table.size();
        if (table[actual_hash] == data && !deleted[actual_hash]){
            deleted[actual_hash] = true;
            --usedSize;
            return true;
        }
    }
    return false;
}


int main() {
    HASHTABLE tab;
    char operation;
    string word;
    while (cin >> operation >> word) {
        switch (operation) {
            case '+':
                cout << (tab.Add(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                cout << (tab.Delete(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                cout << (tab.Has(word) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    return 0;
}
