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
    int KeysCount;
    double GrowFactor;
    int HashParamA;
    int InitialTableSize;
    
    vector<string> table;
    vector<bool> deleted;
    
    int Hash(const string&, size_t);
    int HashSecond(const string&, size_t);
    void growTable();
};


HASHTABLE::HASHTABLE() {
    KeysCount = 0;
    GrowFactor = 0.75;
    HashParamA = 37;
    InitialTableSize = 8;
    table = vector<string>(InitialTableSize);
    deleted = vector<bool>(InitialTableSize);
}


HASHTABLE::~HASHTABLE() {
}


int HASHTABLE::Hash(const string& data, size_t m) {
    int result = 0;
    for (int i = 0; i < static_cast<int>(data.length()); ++i)
        result = (result * HashParamA + data[i]) % m;
    return result;
}


int HASHTABLE::HashSecond(const string& data, size_t m) {
    int result = 0;
    for (int i = 0; i < static_cast<int>(data.length()); ++i)
        result = (data[i]) % m;
    return result;
}


bool HASHTABLE::Has(const string& data){
    int hash1 = Hash(data, table.size());
    int hash2 = HashSecond(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        if (table[hash1] == data && !deleted[hash1])
            return true;
        hash1 = (hash1 + hash2) % table.size();
    }
    return false;
}


bool HASHTABLE::Add(const string& data){
    if (KeysCount + 1 > GrowFactor * table.size()) {
        growTable();
    }
    int hash1 = Hash(data, table.size());
    int hash2 = HashSecond(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        if (table[hash1] == data && !deleted[hash1])
            return false;
        if (!deleted[hash1]){
            table[hash1] = data;
            deleted[hash1] = false; // ???
            ++KeysCount;
            return true;
        }
        hash1 = (hash1 + hash2) % table.size();
    }
    return false;
}


void HASHTABLE::growTable() {
    vector<string> newTable(table.size() * 2);
    vector<bool> newDeleted(deleted.size() * 2);
    deleted = newDeleted;
    
    for (int j = 0; j < table.size(); ++j) {
        int hash1 = Hash(table[j], newTable.size());
        int hash2 = HashSecond(table[j], newTable.size());
        for (int i = 0; i < newTable.size(); ++i){
            if (newDeleted[hash1] == false){
                newTable[hash1] = table[j];
                newDeleted[hash1] = true;
                break;
            }
            hash1 = (hash1 + hash2) % newTable.size();
        }
    }
    table = newTable;
}


bool HASHTABLE::Delete(const string& data){
    int hash1 = Hash(data, table.size());
    int hash2 = HashSecond(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        if (table[hash1] == data && !deleted[hash1]){
            deleted[hash1] = true;
            --KeysCount;
            return true;
        }
        hash1 = (hash1 + hash2) % table.size();
    }
    return false;
}


int main() {
    HASHTABLE tab;
    char operation;
    string word;
    
    /*
     FILE * pFile;
     freopen_s(&pFile, "C:\\123\\007.txt", "r", stdin);
     FILE * pF;
     freopen_s(&pF, "C:\\123\\out", "w", stdout);
     */
    
    while (cin >> operation >> word) {
        switch (operation){
            case '+':{
                cout << (tab.Add(word) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-':
                cout << (tab.Delete(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                cout << (tab.Has(word) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    
}
