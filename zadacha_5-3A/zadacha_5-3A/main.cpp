//
//  main.cpp
//  zadacha_5-3A
//
//  Created by Владимир on 14.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <assert.h>


///////// MAIN STRUCTURE /////////

struct block{
    int width;
    int height;
};


///////// NODE /////////

struct CNode {
    block Data;
    CNode* Next;
    
    CNode(block data) {
        data.width = Data.width;
        data.height = Data.height;
        Next = 0;
    };
};


///////// LIST /////////

class CList {
public:
    CList(): first(0) {};
    ~CList();
    
    void add_first(CNode*);
    void del_first();
    CNode* get_first() { return first; }
    bool is_empty() const { return first == 0; };

private:
    CNode* first;
};


CList::~CList(){
    while (first != 0) {
        del_first();
    }
}


void CList::add_first(CNode* node) {
    if (first == 0){
        first = node;
    } else {
        CNode* second = first;
        first = node;
        node->Next = second;
    }
}


void CList::del_first() {
    assert(first != 0);
    
    CNode* second = first -> Next;
    delete first;
    first = second;
}


///////// STACK /////////

class CStack {
public:
    CStack() {};
    void push( block x );
    block pop();
    
private:
    CList* list;
};


void CStack::push(block x) {
    list->add_first(new CNode(x));
}


block CStack::pop(){
    assert(list->is_empty() == false);
    block data = list->get_first()->Data;
    list->del_first();
    return data;
}



///////// PROCESSOR /////////

int find_max(block* input, int ssize){
    int max = 0;
    
    for (int i = 0; i < ssize; ++i) {
        //std::cout << "| i = " << i << " | " << input[i].width << " | " << input[i].height << " |\n";
        
        
        
    }
    
    
    
    
    return max;
}



int main(int argc, const char * argv[]) {
    // get number of Blocks
    int n = 0;
    std::cin >> n;
    
    // make array of structs, save blocks there
    block input_blocks[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> input_blocks[i].width;
        std::cin >> input_blocks[i].height;
    }
    
    std::cout << "\nProcessing...\n" << find_max(input_blocks, n);
}
