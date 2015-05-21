//
//  main.cpp
//  AVL_tree
//
//  Created by Владимир on 21.05.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


struct Node {
    int Key;
    int Height;
    Node* Left;
    Node* Right;
    
    Node(int k): Key(k), Left(NULL), Right(NULL), Height(1) {}
    
    Node(Node* do_copy) {
        Key = do_copy -> Key;
        Height = do_copy -> Height;
        Left = do_copy -> Left;
        Right = do_copy -> Right;
    }
};


class AVL_tree {
public:
    AVL_tree();
    ~AVL_tree();
    void Add(int);
    void Delete(int);
    int getHeight();
private:
    Node* root;
    void RotateRight(Node*&);
    void RotateLeft(Node*&);
    void Balance(Node*&);
    void UpdateHeight(Node*&);
    void AddRecursioly(Node*&, int);
    void DeleteRecursioly(Node*&, int);
};


// Add-interface
void AVL_tree::Add(int value) {
    AddRecursioly(root, value);
}


// Add-realisation
void AVL_tree::AddRecursioly(Node*& node, int value) {
    if (node == NULL) {
        node = new Node(value);
    } else if (value > node -> Key) {
        AddRecursioly(node -> Right, value);
    } else {
        AddRecursioly(node -> Left, value);
    }
    Balance(node);
}


// Delete-interface
void AVL_tree::Delete(int value) {
    DeleteRecursioly(root, value);
}


// Delete-realisation
void AVL_tree::DeleteRecursioly(Node*& node, int value) {
    
}


void AVL_tree::RotateRight(Node*& node) {
    Node* buf = node -> Left;
    node -> Left = buf -> Right;
    buf -> Right = node;
    node = buf;
    UpdateHeight(buf);
    UpdateHeight(node);
}


void AVL_tree::RotateLeft(Node*& node) {
    Node* buf = node -> Right;
    node -> Right = buf -> Right;
    buf -> Left = node;
    node = buf;
    UpdateHeight(buf);
    UpdateHeight(node);
}


void AVL_tree::Balance(Node*& node) {
    UpdateHeight(node);
    
    if (node -> Right -> Height - node -> Left -> Height == 2) {
        
    }
    
    if (node -> Right -> Height - node -> Left -> Height == -2) {
        
    }
}


void AVL_tree::UpdateHeight(Node*& node) {
    if (node->Left->Height > node->Right->Height) {
        node->Height = node->Left->Height + 1;
    } else {
        node->Height = node->Right->Height + 1;
    }
}


int AVL_tree::getHeight() {
    return root -> Height;
}


//////////////////////////////////////////////////////


int main() {
    AVL_tree* tree = new AVL_tree();
    int data;
    while (std::cin >> data) {
        if (data > 0) {
            tree -> Add(data);
        } else {
            tree -> Delete(data);
        }
    }
    std::cout << tree -> getHeight() << "\n";
    delete tree;
    return 0;
}
