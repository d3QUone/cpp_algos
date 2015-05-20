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
    void clear(Node* );
    void PrintContent(Node* );
};


BinTree::~BinTree() {
    clear(root);
}


void BinTree::clear(Node* root_item) {
    if (root_item->Left != NULL) {
        clear(root_item->Left);
        delete root_item;
        root_item = NULL;
    }
    if (root_item->Right != NULL) {
        clear(root_item->Right);
        delete root_item;
        root_item = NULL;
    }
}


void BinTree::Add(int k) {
    Node* leaf = new Node(k);
    if (root == NULL) {
        root = leaf;
        delete leaf;
        leaf = NULL;
        return;
    }
    Node* place = new Node(root);
    while (place != NULL) {
        if (leaf->Key > place->Key) {
            if (place -> Right != NULL) {
                place = place -> Right;
            } else {
                place -> Right = leaf;
                break;
            }
        } else {
            if (place -> Left != NULL) {
                place = place -> Left;
            } else {
                place -> Left = leaf;
                break;
            }
        }
    }
//    root = place;
    
    delete leaf;
    leaf = NULL;
    delete place;
    place = NULL;
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
    
    tree -> Add(2); // first item will be root
    tree -> Add(1);
    tree -> Add(3);
    
//    int n = 0;
//    std::cin >> n;
//    int buf;
//    for (int i = 0; i < n; ++i) {
//        std::cin >> buf;
//        tree -> Add(buf);
//    }
    tree -> PrintPostOrder();
    
    delete tree;
    return 0;
}
