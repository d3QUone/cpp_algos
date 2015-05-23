#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct CData {
    string data;
    int flag;
    // -1: deleted,
    //  0: empty,
    //  1: busy
};


class HASHTABLE {
public:
    HASHTABLE();
    ~HASHTABLE();
    bool Add(const string&);
    bool Delete(const string&);
    bool Has(const string&);
private:
    double loadFactor;
    int usedSize;
    vector<CData> table;
    int getHash(const string&, size_t);
    void growTable();
    bool performAdd(std::vector<CData>&, const string&);
};


HASHTABLE::HASHTABLE() {
    loadFactor = 0.75;
    usedSize = 0;
    table = vector<CData>(8);
}


HASHTABLE::~HASHTABLE() {
    table.clear();
}


int HASHTABLE::getHash(const string& data, size_t m) {
    int result = 0;
    for (int i = 0; i < static_cast<int>(data.length()); ++i) {
        result = (result*37 + data[i]) % m;
    }
    return result;
}


bool HASHTABLE::Has(const string& data){
    int hash = getHash(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        int actual_hash = (hash + i*(i + 1)/2) % table.size();
        if (table[actual_hash].flag == 0) {
            return false;
        }
        if (table[actual_hash].data == data && table[actual_hash].flag == 1) {
            return true;
        }
    }
    return false;
}


bool HASHTABLE::Add(const string& data){
    return performAdd(table, data);
}


bool HASHTABLE::Delete(const string& data){
    int hash = getHash(data, table.size());
    for (int i = 0; i < table.size(); ++i){
        int actual_hash = (hash + i*(i + 1)/2) % table.size();
        if (table[actual_hash].flag == 0) {
            return false;
        }
        if (table[actual_hash].data == data && table[actual_hash].flag == 1){
            table[actual_hash].flag = -1;
            return true;
        }
    }
    return false;
}



void HASHTABLE::growTable() {
    vector<CData> newTable(table.size() * 2);
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].flag == 1) {
            performAdd(newTable, table[i].data);
        }
    }
    table = newTable;
}


bool HASHTABLE::performAdd(std::vector<CData>& tab, const string& data) {
    if (usedSize + 1 > loadFactor * tab.size()) {
        growTable();
    }
    int found_index = -1;
    int hash = getHash(data, tab.size());
    for (int i = 0; i < tab.size(); ++i){
        int actual_hash = (hash + i*(i + 1)/2) % tab.size();
        if (tab[actual_hash].data == data && tab[actual_hash].flag == 1) {
            return false;
        }
        if (tab[actual_hash].flag == -1) {
            found_index = actual_hash;
        }
        if (tab[actual_hash].flag == 0) {
            if (found_index == -1) {
                found_index = actual_hash;
            }
            break;
        }
    }

    if (found_index != -1) {
        tab[found_index].data = data;
        tab[found_index].flag = 1;
        ++usedSize;
        return true;
    } else {
        return false;
    }
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
