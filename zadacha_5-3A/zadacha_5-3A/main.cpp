//
//  main.cpp
//  zadacha_5-3A
//
//  Created by Владимир on 14.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <assert.h>

/*
 5_3. Прямоугольники.
 
 В стек помещайте ступени в порядке увеличения высоты: пары
 <начало ступени, ее высота>. В стеке лежит своего рода лестница. При появлении нового
 прямоугольника бОльшей высоты, добавляйте его в стек как ступеньку. При появлении нового
 прямоугольника меньшей высоты, срезайте вершок со всех бОльших ступенек из
 стека.
 
 Срезаемый вершок может участвовать только в тех вписанных прямоугольниках,
 которые оканчиваются до последней ступеньки. Т.к. последняя ступенька ниже
 срезаемого вершка.
 
 Эти вершки могут содержать максимальный вписанный прямоугольник. Поэтому надо
 пересмотреть все прямоугольники под срезаемыми вершками. Если срезается m
 ступенек, то из стека по очереди извлекаются m ступенек и к каждой
 подстраивается прямоугольник. Каждый из таких прямоугольников — кандидат на
 максимум. После просмотра не забудьте добавить новую ступень с x-координатой
 срезанных ступенек и высотой нового прямоугольника.
 
 После просмотра всех прямоугольников нужно аналогично пересмотреть все
 накопленные ступени. Можно добавить фиктивный прямоугольник высоты 0, чтобы
 автоматически срезать все накопленные ступени и обновить максимум.
 */

///// stack on array

struct block{
    size_t width;
    size_t height;
};


class Stack{
public:
    Stack(size_t _bufferSize) : bufferSize(_bufferSize), realSize(0){
        buffer = new block[_bufferSize];
    }
    ~Stack(){ delete[] buffer; }
    
    void push(block a);
    block pop();
    bool isEmpty() const{ return realSize == 0; }
    void print_items();
    //void grow();
    
private:
    block* buffer;
    size_t bufferSize;
    size_t realSize;
};

/*
 void Stack::grow(){
	int newBufferSize = bufferSize * 2;
	int* newBuffer = new int[newBufferSize];
 
	memcpy(newBuffer, buffer, realSize);
 
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
 }*/

void Stack::push(block a){
    assert(realSize < bufferSize);
//    if (realSize == bufferSize) {
//        grow();
//    }
    buffer[realSize++] = a;
}

block Stack::pop(){
    assert(realSize > 0);
    return buffer[--realSize];
}

void Stack::print_items() {
    std::cout << "Stack print: ";
    for (int i = 0; i < realSize; ++i) {
        std::cout << buffer[i].width << "*" << buffer[i].height << " ";
    }
    std::cout << "\n";
}


size_t new_try(block* input, size_t ssize) {
    size_t max_square = 0;
    size_t last_height = 0;
    
    Stack* SStack = new Stack(ssize);
    block item;
    
    for (int i = 0; i < ssize; ++i) {
        if (input[i].height > last_height) {
            SStack -> push(input[i]);
            if (input[i].height * input[i].width > max_square) {
                max_square = input[i].height*input[i].width;
            }
        } else {
            // load last item from stack
            item = SStack -> pop();
            size_t buf_w = 0;
            size_t buf_h = item.height;
            
            while (buf_h >= input[i].height) {
                buf_w += item.width;
                if (buf_h * buf_w > max_square) {
                    max_square = buf_h * buf_w;
                }
                
                if (!SStack -> isEmpty()) {
                    item = SStack -> pop();
                    buf_h = item.height;
                } else break;
            }
            
            // push big block, check sq
            input[i].width += buf_w;
            if (input[i].width * input[i].height > max_square) {
                max_square = input[i].height*input[i].width;
            }
            
            SStack -> push(input[i]);
        }
        last_height = input[i].height;
        
        //SStack -> print_items(); // just see what happens there
    }
    delete SStack;
    return max_square;
}


int main(){
    int n = 0;
    std::cin >> n;
    
    // make array of structs, save blocks there
    block input_blocks[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> input_blocks[i].width;
        std::cin >> input_blocks[i].height;
    }
    // gap to make the algorythm work more generic
    input_blocks[n].width = 0;
    input_blocks[n].height = 0;
    
    size_t max = new_try(input_blocks, n + 1);
    std::cout << max;
    return 0;
}


///////// PROCESSOR /////////

size_t find_max(block* input, int ssize){
    long int max = 0;            // maximum square
    long int buf_max = 0;        // bufferizy max for several blocks
    
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
                } else break;
            }
        }
        last_height = input[index].height;
    }
    return max;
}
