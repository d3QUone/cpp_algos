//
//  main.cpp
//  zadacha_5-3
//
//  Created by Владимир on 06.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


// stack of INTs
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
 



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
