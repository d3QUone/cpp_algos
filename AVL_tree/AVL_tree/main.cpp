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
    
    Node(int k): Key(k), Left(NULL), Right(NULL), Height(0) {}
    
    Node(Node* do_copy) {
        Key = do_copy -> Key;
        Height = do_copy -> Height;
        Left = do_copy -> Left;
        Right = do_copy -> Right;
    }
};


class AVL_tree {
public:
    AVL_tree(){};
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
    int nodeHeight(Node*);
    Node* getMinNode(Node*);
    Node* removeMinNode(Node*);
    void Clear(Node* node);
};


AVL_tree::~AVL_tree() {
    Clear(root);
}


// recursive cleaning....
void AVL_tree::Clear(Node* node) {
    if (node -> Left != NULL) {
        Clear(node -> Left);
        delete node -> Left;
        node -> Left = NULL;
    }
    if (node -> Right != NULL) {
        Clear(node -> Right);
        delete node -> Right;
        node -> Right = NULL;
    }
}


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


Node* AVL_tree::getMinNode(Node* node) {
    return node -> Left ? getMinNode(node -> Left) : node;
}


Node* AVL_tree::removeMinNode(Node* node) {
    if (node -> Left == NULL) {
        return node -> Right;
    } else {
        node -> Left = removeMinNode(node -> Left);
        Balance(node);
        return node;
    }
}


// Delete-realisation
void AVL_tree::DeleteRecursioly(Node*& node, int value) {
    if (node != NULL) {
        if (value < node -> Key) {
            DeleteRecursioly(node -> Left, value);
            Balance(node);
        } else if (value > node -> Key) {
            DeleteRecursioly(node -> Right, value);
            Balance(node);
        } else {
            Node* Lbuf = node -> Left;
            Node* Rbuf = node -> Right;
            if (Rbuf == NULL) {
                node = Lbuf;
            } else {
                Node* minNode = getMinNode(Rbuf);
                minNode -> Right = removeMinNode(Rbuf);
                minNode -> Left = Lbuf;
                Balance(minNode);
                node = minNode;
            }
        }
    }
}


// Height-interface
int AVL_tree::getHeight() {
    return nodeHeight(root);
}


// Height-realisation
int AVL_tree::nodeHeight(Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        return node -> Height;
    }
}


void AVL_tree::RotateRight(Node*& node) {
    Node* buf = node -> Left;
    node -> Left = buf -> Right;
    buf -> Right = node;
    UpdateHeight(node);
    UpdateHeight(buf);
    node = buf;
}


void AVL_tree::RotateLeft(Node*& node) {
    Node* buf = node -> Right;
    node -> Right = buf -> Left;
    buf -> Left = node;
    UpdateHeight(node);
    UpdateHeight(buf);
    node = buf;
}


void AVL_tree::Balance(Node*& node) {
    UpdateHeight(node);
    if (nodeHeight(node->Right) - nodeHeight(node->Left) == 2) {
        if (nodeHeight(node->Right->Right) - nodeHeight(node->Right->Left) < 0) {
            RotateRight(node->Right);
        }
        RotateLeft(node);
    }
    if (nodeHeight(node->Right) - nodeHeight(node->Left) == -2) {
        if (nodeHeight(node->Left->Right) - nodeHeight(node->Left->Left) > 0) {
            RotateLeft(node->Left);
        }
        RotateRight(node);
    }
}


void AVL_tree::UpdateHeight(Node*& node) {
    if (nodeHeight(node->Left) > nodeHeight(node->Right)) {
        node->Height = nodeHeight(node->Left) + 1;
    } else {
        node->Height = nodeHeight(node->Right) + 1;
    }
}


//////////////////////////////////////////////////////


int main() {
    AVL_tree* tree = new AVL_tree();
    int data;
    while (std::cin >> data) {
        if (data > 0) {
            tree -> Add(data);
        } else {
            tree -> Delete(-1*data);
        }
    }
    std::cout << tree -> getHeight() << "\n";
    delete tree;
    return 0;
}
