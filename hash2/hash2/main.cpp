//
//  main.cpp
//  hash2
//
//  Created by Владимир on 18.05.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

/* POST ORDER PRINTOUT */

#include <iostream>
#include <vector>

struct Node {
    int Key;
    Node* Left;
    Node* Right;
    Node(int k): Key(k), Left(NULL), Right(NULL) {}
    Node(Node* do_copy) {
        Key = do_copy -> Key;
        Left = do_copy -> Left;
        Right = do_copy -> Right;
    }
};


class BinTree {
public:
    ~BinTree();
    void Add(int );
    void PrintPostOrder();
private:
    Node* root;
    void clear(Node*& );
    void PrintContent(Node* );
    
    void AddRecoursive(int, Node*&);
};


BinTree::~BinTree() {
    clear(root);
}


void BinTree::clear(Node*& root_item) {
    if (root_item->Left != NULL) {
        clear(root_item->Left);
    }
    if (root_item->Right != NULL) {
        clear(root_item->Right);
    }
    
    if (root_item) {
        delete root_item;
        root_item = NULL;
    }
}


void BinTree::Add(int k) {
    AddRecoursive(k, root);
}


void BinTree::AddRecoursive(int k, Node*& node) {
    if (node == NULL) {
        node = new Node(k);
        return;
    }
    if (node -> Key > k) {
        AddRecoursive(k, node -> Left);
    } else {
        AddRecoursive(k, node -> Right);
    }
}


// from bottom to top
void BinTree::PrintContent(Node* leaf) {
    if (leaf != NULL) {
        PrintContent(leaf -> Left);
        PrintContent(leaf -> Right);
        
        std::cout << leaf -> Key << " ";
    } else {
        return;
    }
}


void BinTree::PrintPostOrder() {
    PrintContent(root);
}


int main() {
    BinTree* tree = new BinTree();
    
//    tree -> Add(2); // first item will be root
//    tree -> Add(1);
//    tree -> Add(3);
    
    int n = 0;
    std::cin >> n;
    int buf;
    for (int i = 0; i < n; ++i) {
        std::cin >> buf;
        tree -> Add(buf);
    }
    tree -> PrintPostOrder();
    
    delete tree;
    return 0;
}
