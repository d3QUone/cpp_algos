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

// tests aren't unfinished yet
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


/*
 5_3. Прямоугольники.
 
 Дана последовательность ​N​ прямоугольников различной ширины и высоты (w​i,​h​i)​.
 Прямоугольники расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо). 
 Требуется найти ​M​­ площадь максимального прямоугольника (параллельного осям координат), 
 который можно вырезать из этой фигуры.
*/


/*
 короче в стэк кидал прямоугольник, только если его высота больше предыдущего
 если меньше
 рассматривал его площадь
 рассматривал площади предущих, вернее
 и доставал их из стэка, но оставлял прямоугольник с его шириной, но высотой предыдущего
 и так, пока не дойду до прямоугольника с высотой ниже высоты нового
*/


int max_sq(int n, int* blocks) {
    CStack* s;
    
    int last_H = 0;
    
    int max_sq = 0;
    
    for (int i = 0; i < n; ++i) {
        
        // W = b[i][0], H = b[i][1]
        if (blocks[2*i + 1] > last_H) {
            last_H = blocks[2*i + 1];
            s -> push(i); // save index only
        } else {
            
            //
            
            
        }
        
        
        
    }
    
    
    delete s;
    return 0; // - ans
}



int main(int argc, const char * argv[]) {
    int n = 0;
    std::cin >> n;
    
    // [0, 1], [2, 3], [4, 5], ..., [2*i, 2i+1], ...
    int* bl = new int[2*n];
    for( int i = 0; i < n; ++i) std::cin >> bl[2*i] >> bl[2*i+1];
    
    std::cout << max_sq(n, bl);
    return 0;
}
