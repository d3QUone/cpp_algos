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
    int max = 0;            // maximum square
    int buf_max = 0;        // bufferizy max for several blocks
    
    int last_height = 0;    // stores the height of last checked block
    int buffer_wid = 0;     // bufferizy forms
    int buffer_hig = 0;     // - . - . -
    
    int stack_size = 0;     // num of processed items
    
    int j = 0;              // index for cutting blocks
    
    for (int i = 0; i < ssize; ++i) {
        if (input[i].height < last_height) {
            //printf("curr height = %i; last height = %i\n", input[i].height, last_height);
            
            // count sq of every j-th item - OK
            j = i; //input[j].height <= input[i].height && 
            while (j >= 0) {
                buffer_hig = input[j].height;
                buffer_wid = input[j].width;
                if (buffer_wid*buffer_hig > max) {
                    max = buffer_wid*buffer_hig;
                }
                j-- ;
            }
            if (j < 0) j = 0;
            
            // cut from j - the first bigger block ~ ~ ~
            for (int k = j; k >= 0; --k) {
                //int comp1 = input[i].height; // just for debug
                //int comp2 = input[j].height;
                
                if (input[i].height < input[j].height) {
                    input[j].height = input[i].height; /// error!
                    // sets 0 if last was 0!!!
                } else {
                    break;
                }
            }
            
//            last_height = input[i].height; // update the last (prev) height
//            stack_size++ ;
            
            // array [0; stack_size] is sorted, eval it's Total sq - OK
            for (int i = 0; i < stack_size; ++i) {
                buf_max = 0;
                for (int k = i; k < stack_size; ++k) {
                    buf_max += input[i].height*input[k].width;
                }
                if (buf_max > max) {
                    max = buf_max;
                }
            }
            
            printf("j-brake: %i; height: %i; max now: %i\n", j, input[j].height, max);
        }
        
            // only update data...
        last_height = input[i].height;
        stack_size++ ;
        
        
        /*
            //// stack - trash ////
             
            // get sq of one current block
            for (int i = 0; i < stack_size; ++i) {
                buffer = stack -> pop();
                buffer_stack -> push(buffer);
                
                buffer_wid = buffer.width;
                buffer_hig = buffer.height;
                
                if (buffer_wid * buffer_hig > max) {
                    max = buffer_wid * buffer_hig;
                }
             
            }
            
            // cut blocks
            for (int i = 0; i < stack_size; ++i) {
                buffer = buffer_stack -> pop();
                
                // save back cut blocks
                if (buffer.height > input[i].height) {
                    buffer.height = input[i].height;
                    stack -> push(buffer);
                }
            } // finally buffer-stack is empty, stack has cutted blocks
            
            // wrong!!!
            // do recalc of max square
            last_height = input[i].height;
            stack -> push(input[i]);
            stack_size++ ;
            
            
            for (int i = 0; i < stack_size; ++i) {
                int _max = 0;
                for (int j = i; j < stack_size; ++j) {
                    _max += input[i].height*input[j].width;
                }
                
                if (_max > max) {
                    max = _max;
                }
                
//                buffer = stack -> pop();
//                buffer_stack -> push(buffer);
//                _max += buffer.height*buffer.width;
            }
             */
        
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
    // gap to make the algorythm  work more generic
    input_blocks[n].width = 0;
    input_blocks[n].height = 0;
    
    int max = find_max(input_blocks, n + 1);
    std::cout << "\nProcessing...\n" << max << "\n";
}
