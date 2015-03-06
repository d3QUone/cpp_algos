//
//  main.cpp
//  zadach-4-4
//
//  Created by Владимир on 06.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


// zadacha 4 1
// ​Реализовать очередь с динамическим буфером.


class Queue {
public:
    Queue( int n ) {
        data_size = n + 1; // not 0
        data = new int[data_size];
        head = 0;
        tail = 0;
    };
    
    ~Queue(){
        delete [] data;
    };
    
    // dynamic buffer here
    void add_item( int item ){
        if ( (tail + 1) % data_size != head) {
            data[tail] = item;
            tail = (tail + 1) % data_size;
        } else {
            // out of buffer_size - re_init 'data', copy from head to tail, return new -> dynamic Q
            
            int new_data_size = 2*data_size + 1;
            int* buf_data = new int[new_data_size];
            
            int resave_buffer = 0;
            for (int i = 0; i < data_size; ++i){
                resave_buffer = del_item(); // best way to get data from head to tail
                if (resave_buffer != -1) {
                    buf_data[i] = resave_buffer;
                    //std::cout << buf_data[i] << " ";
                } else {
                    break;
                }
            }
            //std::cout << "\ndone\n";
            
            data_size = new_data_size;
            *data = *buf_data;
            data[tail] = item; // wrong tail ?
            tail = (tail + 1) % data_size;
            head = 0;
            delete [] buf_data; // release dat buffer-memory
            
            /*
            for (int i = 0; i < data_size; ++i){
                std::cout << data[i] << " ";
            }
            std::cout << "\n";
            */
        }
    };
    
    int del_item(){
        if ( head != tail ) {
            int res = data[head];
            head = (head + 1) % data_size;
            return res;
        }
        return -1; // - means error
    };
    bool is_empty() { return head == tail; }; // isn't used yet
    
private:
    int data_size;
    int* data;
    int head; // first item in data
    int tail; // last item in data
};


int main(int argc, const char * argv[]) {
    // do test cases manually from keybord, n times
    int n = 0; int code = 0; int arg = 0; int buf = 0; int error = -1;
    std::cin >> n;
    Queue* q1 = new Queue(n); // init dynamic queue
    for (int i = 0; i < n; ++i) {
        std::cin >> code >> arg; // get inp
        // codes can be '2' or '3' only
        if (code == 2) {
            buf = q1 -> del_item();
            //std::cout << buf << " released\n";
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
