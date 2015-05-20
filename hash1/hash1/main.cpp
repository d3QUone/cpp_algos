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
    int initSize;
    int usedSize;
    
    vector<string> table;
    /**
     @brief Stores status of every item
     @return -1: deleted
     @return 0: empty
     @return 1: has data
    */
    vector<int> status;
    
    int getHash(const string&, size_t);
    void growTable();
};


HASHTABLE::HASHTABLE() {
    loadFactor = 0.75;
    initSize = 8;
    usedSize = 0;
    
    table = vector<string>(initSize);
    status = vector<int>(initSize);
}


HASHTABLE::~HASHTABLE() {
    table.clear();
    status.clear();
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
    vector<int> newStatus(status.size() * 2);
    
    for (int j = 0; j < table.size(); ++j) {
        int hash = getHash(table[j], newTable.size());
        for (int i = 0; i < newTable.size(); ++i){
            int actual_hash = (hash + i*(i + 1)/2) % table.size();
            if (newStatus[actual_hash] == 0 && newTable[actual_hash] != table[j]){
                newTable[actual_hash] = table[j];
                newStatus[actual_hash] = 1; // means the place is busy
                break;
            }
        }
    }
    table = newTable;
    status = newStatus;
    std::cout << " # grow # ";
}


bool HASHTABLE::Has(const string& data){
    int hash = getHash(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        int actual_hash = (hash + i*(i + 1)/2) % table.size();
        if (table[actual_hash]==data && status[actual_hash]==1) {
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
        if (status[actual_hash]==1 && table[actual_hash] == data) {
            return false;
        }
        if (status[actual_hash]==0 && table[actual_hash] != data){
            table[actual_hash] = data;
            status[actual_hash] = 1;
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
        if (table[actual_hash] == data && status[actual_hash]==1){
            status[actual_hash] = -1;
            --usedSize;
            return true;
        }
    }
    return false;
}


int main() {
    HASHTABLE tab;
    /*
    for (int i = 0; i < 40; i++) {
        std::cout << "+" << std::to_string(i) << (tab.Add(std::to_string(i)) ? " OK" : " FAIL") << std::endl;
    } std::cout << "--------\n";
    
    for (int i = 0; i < 40; i = i*2 + 1) {
        std::cout << "-" << std::to_string(i) << (tab.Delete(std::to_string(i)) ? " OK" : " FAIL") << std::endl;
    } std::cout << "--------\n";
    
    for (int i = 0; i < 45; i++) {
        std::cout << "?" << std::to_string(i) << (tab.Has(std::to_string(i)) ? " OK" : " FAIL") << std::endl;
    } std::cout << "--------\n";
    
    
    for (int i = 0; i < 40; i++) {
        std::cout << "+" << std::to_string(i) << (tab.Add(std::to_string(i)) ? " OK" : " FAIL") << std::endl;
    } std::cout << "--------\n";
    
    for (int i = 0; i < 45; i++) {
        std::cout << "?" << std::to_string(i) << (tab.Has(std::to_string(i)) ? " OK" : " FAIL") << std::endl;
    }*/
    
    
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
