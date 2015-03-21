//
//  main.cpp
//  zadacha_6-3
//
//  Created by Владимир on 19.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <assert.h>

/*
// bad Dynamic array of ints
class CArray {
public:
    CArray(): buffer(0), bufferSize(0), realSize(0) {}
    ~CArray() { delete [] buffer; }
    
    int GetAt(int index) const;
    //int operator[] (int index) const { return GetAt(index); }
    //int& operator[] (int index);
    
    void Add(int element);
    int Size() { return realSize; }
    bool isEmpty() { return realSize == 0; }
    void deleteFirst();
    
private:
    int* buffer;
    int bufferSize;     // how much memory allocated
    int realSize;       // items in buffer

    void grow();
};


int CArray::GetAt(int index) const {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}


void CArray::grow() {
    int new_size = bufferSize*2;
    int* new_buffer = new int[new_size];
    
    for (int i = 0; i < realSize; ++i) {
        new_buffer[i] = buffer[i];
    }
    delete [] buffer;
    buffer = new_buffer;
    bufferSize = new_size;
}


void CArray::Add(int element) {
    if (realSize == bufferSize) {
        grow();
    }
    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}


void CArray::deleteFirst() {
    assert(realSize > 1);
    int* new_buffer = new int[realSize--];
    for (int i = 0; i < realSize; ++i) {
        new_buffer[i] = buffer[i+1];
    }
    delete [] buffer;
    buffer = new_buffer;
}
*/


class Heap {
public:
    Heap(int n) {
        size = 0;
        arr = new int[n];
    }
    ~Heap() { delete [] arr; }
    
    void AddItem(int item);
    void SiftDown(int i);
    void SiftUp(int i);
    int ExtractMin();
    int GetSize() { return size; }
    int firstItem() { return arr[0]; }
    void print_items();
    
private:
    int size;
    int* arr;
};


void Heap::SiftDown(int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int min = i;
    if (left < size && arr[left] < arr[i]) {
        min = left;
    }
    if (right < size && arr[right] < arr[min]) {
        min = right;
    }
    // Sift if any
    if (min != i) {
        std::swap(arr[i], arr[min]);
        SiftDown(min);
    }
}


void Heap::SiftUp(int i) {
    int parrent = (i - 1)/2;
    while (i > 0) {
        if (arr[i] >= arr[parrent]) {
            break;
        }
        std::swap(arr[i], arr[parrent]);
        i = parrent;
        parrent = (i - 1)/2;
    }
}


int Heap::ExtractMin() {
    assert(size > 0);
    int result = arr[0];
    size-- ;
    arr[0] = arr[size]; // last index = size - 1
    SiftDown(0);
    return result;
}


void Heap::AddItem(int item) {
    arr[size] = item;
    SiftUp(size);
    size++ ;
}


void Heap::print_items() {
    std::cout << "heap: ";
    for (int j = 0; j < size; ++j) {
        std::cout << arr[j] << " ";
    }
    std::cout << "\n";
}


/*
void BuildHeap(int* arr, int size, int i) {
    for (int i = size/2 - 1; i >= 0; --i) {
        SiftDown(arr, size, i);
    }
}*/


/*
 Тупики. Очередь электричек, упорядоченных по времени отъезда.
 Извлекаются отбывшие электрички на момент прибытия новой.
 */


int min_routes(int* time_in, int* time_out, int n){
    int max_size = 0;
    int current_depart_time = 0;
    int current_arrive_time = 0;
    
    Heap* hip = new Heap(n);
    
    int debug = 0;
    
    for (int i = 0; i < n; ++i) {
        if (debug == 1) std::cout << "--------------------------------\n";
        
        current_arrive_time = time_in[i];
        current_depart_time = time_out[i];
        
        if (hip->GetSize() > 0) {
            while (hip -> firstItem() < current_arrive_time && hip->GetSize() > 0) {
                hip -> ExtractMin();
            }
        }
        
        hip -> AddItem(current_depart_time);
        
        // check max size of tree
        if (hip->GetSize() > max_size) {
            max_size = hip->GetSize();
        }
        
        if (debug == 1) hip -> print_items();
    }
    delete hip;
    return max_size;
}


int main(){
    int n = 0;
    std::cin >> n;
    
    int* heap_time_in = new int[n];  // прибытие
    int* heap_time_out = new int[n]; // отбытие
    for (int i = 0; i < n; ++i) {
        std::cin >> heap_time_in[i] >> heap_time_out[i];
    }
    int res = min_routes(heap_time_in, heap_time_out, n);
    std::cout << res;
    
    delete [] heap_time_in;
    delete [] heap_time_out;
}