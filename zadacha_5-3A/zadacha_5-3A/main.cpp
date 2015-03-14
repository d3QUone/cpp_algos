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
    size_t width;
    size_t height;
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


/*
 5_3. Прямоугольники.
 
 Дана последовательность ​N​ прямоугольников различной ширины и высоты (w​i,​h​i)​.
 Прямоугольники расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо).
 Требуется найти ​M​­ площадь максимального прямоугольника (параллельного осям координат),
 который можно вырезать из этой фигуры.
 */


///////// PROCESSOR /////////

size_t find_max(block* input, int ssize){
    size_t max = 0;            // maximum square
    size_t buf_max = 0;        // bufferizy max for several blocks
    
    size_t last_height = 0;    // stores the height of last checked block
    size_t buffer_wid = 0;     // bufferizy forms
    size_t buffer_hig = 0;     // - . - . -
    
    for (int index = 0; index < ssize; ++index) {
        // check SQ of every block
        buffer_hig = input[index].height;
        buffer_wid = input[index].width;
        if (buffer_wid*buffer_hig > max) {
            max = buffer_wid*buffer_hig;
        }
        
        if (input[index].height < last_height) {
            
            // cut from (index - 1) - the first bigger block - OK
            for (int k = index - 1; k >= 0; --k) {
                //size_t comp1 = input[index].height; size_t comp2 = input[k].height;
                if (input[index].height < input[k].height) {
                    
                    // do full Sq eval here: array [0; index) is sorted - OK
                    for (int i = 0; i < index; ++i) {
                        buf_max = 0;
                        for (int l = i; l < index; ++l) {
                            buf_max += input[i].height*input[l].width;
                        }
                        if (buf_max > max) {
                            max = buf_max;
                        }
                    }
                    //printf("height: %zu ", input[k].height);
                    input[k].height = input[index].height;
                    //printf("->  %zu; max now: %zu\n", input[k].height, max);
                } else {
                    //printf("steps = %i (k = %i; k0 = %i)\n", index - 1 - k, k, index - 1);
                    break;
                }
                //printf("steps = %i (k = %i; k0 = %i)\n", index - 1 - k, k, index - 1);
            }
        }
        last_height = input[index].height;
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
    input_blocks[n].width = 10;
    input_blocks[n].height = 0;
    
    size_t max = find_max(input_blocks, n + 1);
    std::cout << "\nProcessing... Max = " << max << "\n"; // debug
    //std::cout << max; // release
}
