//
//  main.cpp
//  hash4
//
//  Created by Владимир on 18.05.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

/* develop AVL-tree */

#include <iostream>


struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(NULL), right(NULL), height(1) {}
};


int GetHeight(Node* leaf) {
    return leaf ? leaf->height : 0;
}


void UpdateHeight(Node* leaf) {
    if (GetHeight(leaf->left) > GetHeight(leaf->right)) {
        leaf->height = GetHeight(leaf->left) + 1;
    } else {
        leaf->height = GetHeight(leaf->right) + 1;
    }
}


Node* RotateRight(Node* leaf) {
    Node* L = leaf->left;
    leaf->left = L->right;
    L->right = leaf;
    UpdateHeight(leaf);
    UpdateHeight(L);
    return L;
}


Node* RotateLeft(Node* leaf) {
    Node* R = leaf->right;
    leaf->right = R->left;
    R->left = leaf;
    UpdateHeight(leaf);
    UpdateHeight(R);
    return R;
}


Node* BalanceTree(Node* leaf) {
    Node* temp = NULL;
    UpdateHeight(leaf);
    if (GetHeight(leaf->right) - GetHeight(leaf->left) == 2) {
        if (GetHeight(leaf->right->right) - GetHeight(leaf->right->left) < 0) {
            leaf->right = RotateRight(leaf->right);
        }
        temp = RotateLeft(leaf);
    }
    if (GetHeight(leaf->right) - GetHeight(leaf->left) == -2) {
        if (GetHeight(leaf->left->right) - GetHeight(leaf->left->left) > 0) {
            leaf->left = RotateLeft(leaf->left);
        }
        temp = RotateRight(leaf);
    }
    return temp == NULL ? leaf : temp;
}


Node* AddLeaf(Node* leaf, int k){
    Node* temp;
    if (leaf == NULL) {
        temp = new Node(k);
    } else {
        if (k < leaf->key) {
            leaf->left = AddLeaf(leaf->left, k);
        } else {
            leaf->right = AddLeaf(leaf->right, k);
        }
        temp = BalanceTree(leaf);
    }
    return temp;
}


Node* FindMin(Node* leaf) {
    return leaf->left ? FindMin(leaf->left) : leaf;
}


Node* RemoveMin(Node* leaf) {
    Node* temp;
    if (leaf->left == NULL) {
        temp = leaf->right;
    } else {
        leaf->left = RemoveMin(leaf->left);
        temp = BalanceTree(leaf);
    }
    return temp;
}


Node* Remove(Node* leaf, int k){
    Node* temp = NULL;
    if (leaf != NULL) {
        if (k < leaf->key) {
            leaf->left = Remove(leaf->left, k);
        } else if (k > leaf->key) {
            leaf->right = Remove(leaf->right, k);
        } else {
            Node* L = leaf->left;
            Node* R = leaf->right;
            delete leaf;
            if (R == NULL) {
                return L;
            } else {
                Node* Min = FindMin(R);
                Min->right = RemoveMin(R);
                Min->left = L;
                return BalanceTree(Min);
            }
        }
        temp = BalanceTree(leaf);
    }
    return temp;
}


void Delete(Node* root){
    if (root->left != NULL){
        Delete(root->left);
        delete root->left;
        root->left = NULL;
    }
    if (root->right != NULL){
        Delete(root->right);
        delete root->right;
        root->right = NULL;
    }
}


int main() {
    Node *root = NULL;
    int command;
    while (std::cin >> command, !std::cin.eof()) {
        if (command >= 0) {
            root = AddLeaf(root, command);
        } else {
            root = Remove(root, -1 * command);
        }
    }
    std::cout << root->height << std::endl;
    Delete(root);
    delete root;
}