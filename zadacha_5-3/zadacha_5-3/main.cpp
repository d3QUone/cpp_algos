//
//  main.cpp
//  zadacha_5-3
//
//  Created by Владимир on 06.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


// one node, list item
struct CNode {
    int Data;
    CNode* Next;
    CNode(): Data(0), Next(0) {}; // default
    CNode(int data): Data(data), Next(0) {}; // custom
};


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

// ------- stack -------


class CStack {
public:
    CStack() {};
    void push( int x );
    int pop();
private:
    CList* list;
};


void CStack::push(int x) {
    list->add_first(new CNode(x));
}


int CStack::pop(){
    assert(list->is_empty() == false);
    int data = list->get_first()->Data;
    list->del_first();
    return data;
}


// tests //


void write_command(std::vector<int> stack, bool need_push, int data){
    if (need_push) {
        std::cout << "1 " << data << "\n";
        stack.push_back(data);
    } else {
        int stack_data = stack.back();
        std::cout << "2 " << stack_data << "\n";
        stack.pop_back();
    }
}


void generate_test(){
    std::vector<int> stack;
    std::cout << 2000 << "\n";
    for (int i =0; i < 1000; ++i) {
        write_command(stack, true, rand());
        write_command(stack, rand()%2==0, rand());
    }
}


FILE *f;
int main_test(){
    //freopen_s();
    //generate_test();
    //return 0;
    
    int n = 0;
    std::cin >> n;
    CStack* stack;
    for (int i = 0; i < n; ++i) {
        int op;
        std::cin >> op;
        assert(op == 1 || op == 2);
        
        int data = 0;
        std::cin >> data;
        
        if (op == 1) {
            stack->push(data);
        } else {
            if ( stack -> pop() != data ) {
                std::cout << "NO";
                return 0;
            }
        }
        
    }
    return 0;
}


//
// -- my task --
//
// stack of INTs
//

class Stack {
public:
    Stack( int init_size ){
        top = 0;
        buffer_size = 0;
        max_size = init_size;
        buffer = new int[max_size];
    };
    
    ~Stack(){
        delete[] buffer;
    };
 
    int pull(){
        // pulls last var of stack
        return 0;
    };
 
    void push( int x ) {
        // adds to the end
    };
 
    bool is_empty() { return buffer_size == 0; };
 
private:
    int buffer_size;
    int* buffer; // all data here
    int top; // index of last item
    int max_size;
};


// solves the problem
int max_sq(int n, int* blocks) {
    Stack* s = new Stack(n);
    
    
    delete s;
    
    return 0; // - ans
}



int main(int argc, const char * argv[]) {
    int n = 0;
    std::cin >> n;
    
    int* bl = new int[2*n];
    for( int i = 0; i < n; ++i) {
        std::cin >> bl[2*i] >> bl[2*i+1];
        
        // [1, 2], [3, 4], [5, 6], ..., [2*i, 2i+1], ...
        // i = 0: 0, 1
        // i = 1; 2, 3
        // i = 2; 4, 5
    }
    std::cout << max_sq(n, bl);
    return 0;
}
