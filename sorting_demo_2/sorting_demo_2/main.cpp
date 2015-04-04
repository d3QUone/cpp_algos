//
//  main.cpp
//  sorting_demo_2
//
//  Created by Владимир on 04.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


 // seminar 2, demo
 
 //2vn2-311d-e4am (caps) -- projector pass, Class_2
 // QuickSort
 // ( meeting iterators method )
 int partition(int* arr, int l, int r) {
     int pivot = arr[l];
     int i = l + 1;
     int j = r;
     
     
     //    for (;i < r; ++i) {
     //        if (arr[i] > pivot) {
     //            for (; j > i; --j) {
     //                if (arr[j] < pivot) {
     //                    std::swap(arr[l], arr[j]);
     //                }
     //            }
     //        }
     //    }
     
     
     while (true) {
         while (i <= r && arr[i] < pivot) {
             i++;
         }
         while (arr[j] > pivot) {
             j--;
         }
         if (i >= j) {
             std::swap(arr[l], arr[j]);
             return j;
         }
         std::swap(arr[i], arr[j]);
         i++ ;
         j-- ;
     }
 }
 
 
 
 
 
 int findStats(int* arr, int l, int r, int k){
     int pivotPos = partition(arr, l, k);
     
     if (pivotPos == k) {
         return arr[k];
     } else if (pivotPos < k ) {
         return findStats(arr, pivotPos + 1, r, k);
     } else {
         return findStats(arr, l, pivotPos - 1, k);
     }
 }
 
 
int main(){
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    int* arr = new int [n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::cout << findStats(arr, 0, n-1, k);
    delete [] arr;
}


/*
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
 void print_queue(){for (int i = 0; i < data_size; ++i) std::cout << data[i] << " "; std::cout << std::endl;}
 
 
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
 
 realloc(data, new_data_size);
 memcpy(data, buf_data, (data_size+1)*sizeof(*buf_data));
 delete[] buf_data; // release dat buffer-memory
 
 head = 0;
 tail = data_size; // new tail, surely last item now
 data_size = new_data_size;
 }
 }
 
 
 
 
 int maincc(){
 
 int* a = new int[3];
 for (int i = 0; i < 3; ++i) {
 a[i] = 2*i + 1; // 1 3 5
 std::cout << a[i] << " ";
 }
 std::cout << "\n";
 
 // -- test --
 std::cout << "&a: " << &a << "\n";
 std::cout << "a: " << a << "\n";
 std::cout << "*a: " << *a << "\n";
 
 // -- try --
 int* pointer = a;
 std::cout << pointer << "\n";
 
 for (int i = 0; i < 3; ++i) {
 std::cout << *(pointer + i) << " ";
 }
 
 
 return 0;
 }
 
 
 
 int mainvvv(){
 
 /// --- class
 
 Queue t1(3);
 t1.add_item(10);
 t1.print_queue();
 
 
 //int pointer = t1;
 
 //pointer.print_queue();
 return 0;
 }*/