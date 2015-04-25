//
//  main.cpp
//  hashtable_1
//
//  Created by Владимир on 25.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>


const int HashParam = 37;
const int InitTableSize = 8;


int Hash(const std::string& s, size_t n){
    int result = 0;
    for (int i = 0; i < s.length(); ++i) {
        result = (result * HashParam + s[i]) % n;
    }
    return result;
}


class CHashTable {
public:
    CHashTable();
    bool Has(const std::string& s);
    bool Add(const std::string& s);  // return false if item already exists
    bool Remove(const std::string& s);  // return false if no item

private:
    struct CNode {
        std::string Data;
        CNode* next;
        CNode(const std::string& data): Data(data), next(0) {}
    };
    std::vector<CNode* > table;
    int size; // current used size
};


CHashTable::CHashTable() : table(InitTableSize), size(0) {}


bool CHashTable::Has(const std::string &s) {
    int hash = Hash(s, table.size());
    for (CNode* node = table[hash]; node != 0; node = node->next) {
        if (node->Data == s) {
            return true;
        }
    }
    return false;
}


bool CHashTable::Add(const std::string &s) {
    int hash = Hash(s, table.size());
    CNode* curr_node = table[hash];
    if (curr_node == 0) {
        table[hash] = new CNode(s);
        return true;
    }
    while (true) {
        if (curr_node->Data == s) {
            return false;
        }
        if (curr_node->next == 0) {
            break;
        } else {
            curr_node = curr_node->next;
        }
    }
    curr_node->next = new CNode(s);
    return true;
}


bool CHashTable::Remove(const std::string &s) {
    int hash = Hash(s, table.size());
    if (table[hash] == 0) {
        return false;
    }
    
    if (table[hash]->Data == s) {
        CNode* toDelete = table[hash];
        table[hash] = toDelete->next;
        delete toDelete;
        return true;
    }
    
    CNode* node = table[hash];
    while (node->next != 0) {
        if (node->next->Data == s) {
            CNode* toDelete = node->next;
            table[hash] = toDelete->next;
            delete toDelete;
            return true;
        }
    }
    
    return false;
}


int main(){
    CHashTable hashTable;
    char command = 0;
    std::string data;
    while (std::cin >> command >> data) {
        switch (command) {
            case '+':
                std::cout << (hashTable.Add(data) ? "OK" : "FAIL") << "\n";
                break;
            case '-':
                std::cout << (hashTable.Remove(data) ? "OK" : "FAIL") << "\n";
                break;
            case '?':
                std::cout << (hashTable.Has(data) ? "OK" : "FAIL") << "\n";
                break;
            default:
                break;
        }
    }
    return 0;
}