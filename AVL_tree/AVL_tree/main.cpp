//
//  main.cpp
//  AVL_tree
//
//  Created by Владимир on 21.05.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <vector>


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
    
private:
    Node* root;
    
};


int main() {
    
    
}
