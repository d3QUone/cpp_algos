//
//  main.cpp
//  zadach-4-4
//
//  Created by Владимир on 06.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

// UNCOMMENT TO PASS EJUNDE! so headers, very ejudge...
//#include <cstring> 
//#include <malloc.h>


// zadacha 4 1
// ​Реализовать очередь с динамическим буфером.


class Queue {
public:
    Queue( int n ) {
        data_size = n + 1; // definetly not 0
        data = new int[data_size];
        head = 0;
        tail = 0;
    };
    ~Queue(){ delete[] data; };
    void add_item(int item);
    int del_item();
    
private:
    int data_size;
    int* data;
    int head; // first item in data
    int tail; // last item in data
};


int Queue::del_item() {
    if ( head != tail ) {
        int res = data[head];
        head = (head + 1) % data_size;
        return res;
    }
    return -1; // - means error
}


void Queue::add_item(int item) {
    if ((tail + 1) % data_size != head) {
        data[tail] = item;
        tail = (tail + 1) % data_size;
    } else {
        // out of buffer_size - re_init 'data', copy from head to tail
        int new_data_size = 2*data_size + 1;
        int* buf_data = new int[new_data_size];
        
        memcpy(buf_data, data, (data_size-head)*sizeof(*data));
        if (data_size - tail > 0 && head > tail) {
            memcpy(buf_data, data, (data_size-tail)*sizeof(int));
        }
        buf_data[tail] = item; // add item...
        
        /*
        std::cout << "bufer: \n";
        for (int i = 0; i < new_data_size; ++i) std::cout << buf_data[i] << " ";
        std::cout << "\n";
         */
        
        realloc(data, new_data_size);
        memcpy(data, buf_data, (data_size+1)*sizeof(*buf_data));
        delete[] buf_data; // release dat buffer-memory
        
        head = 0;
        tail = data_size; // new tail, surely last item now
        data_size = new_data_size;
    }
}


/*
// tests of memcpy
int main1(){
    size_t size0; size_t size1;
    std::cin >> size0 >> size1;
    
    int* data = new int[size0]; int* buf_data = new int[size1];
    for (int i = 0; i < size0; ++i) std::cin >> data[i];
    
    if (size0 >= size1) memcpy(buf_data, data, size1*sizeof(*data));
    else memcpy(buf_data, data, size0*sizeof(*data));
    
    std::cout << "result: ";
    for (int i = 0; i < size1; ++i) std::cout << buf_data[i] << " ";
    std::cout << "\n";
    
    delete [] data; delete [] buf_data;
    return 0;
}
*/


int main(int argc, const char * argv[]) {
    // do test cases manually from keybord, n times
    int n = 0; int code = 0; int arg = 0; int buf = 0; int error = -1;
    std::cin >> n;
    Queue* q1 = new Queue(0); // init dynamic queue
    for (int i = 0; i < n; ++i) {
        std::cin >> code >> arg; // get inp
        // codes can be '2' or '3' only
        if (code == 2) {
            buf = q1 -> del_item();
            if (buf != arg) {
                error = 1; // - test isnt passed !
            }
        } else if (code == 3) {
            q1->add_item(arg);
        }
    }
    if (error == 1) {
        std::cout << "NO";
    }
    else {
        std::cout << "YES";
    }
    delete q1; // and finally release memory
}
