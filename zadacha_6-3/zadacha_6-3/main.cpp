//
//  main.cpp
//  zadacha_6-3
//
//  Created by Владимир on 19.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <assert.h>


// Dynamic array of ints

class CArray {
public:
    CArray(): buffer(0), bufferSize(0), realSize(0) {}
    ~CArray() { delete [] buffer; }
    
    int GetAt(int index) const; // ? to int?
    int operator[] (int index) const { return GetAt(index); }
    int& operator[] (int index);
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


// do Heap on Dynamic array!

void SiftDown(CArray& arr, int i){
    // branches
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    // find the largest Child
    int largest = i;
    if (left < arr.Size() && arr[left] > arr[i]) {
        largest = left;
    }
    if (right < arr.Size() && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // Sift if any largest
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        SiftDown(arr, largest);
    }
}


void SiftUp(CArray& arr, int i) {
    int parrent = 0;
    while (i > 0) {
        parrent = (i - 1)/2;
        if (arr[i] < arr[parrent])
            break;
        std::swap(arr[i], arr[parrent]);
        i = parrent;
    }
}


void BuildHeap(CArray& arr, int i) {
    for (int i = arr.Size() / 2 - 1; i >= 0; --i) {
        SiftDown(arr, i);
    }
}


void Add(CArray& arr, int item) {
    arr.Add(item);
    SiftUp(arr, arr.Size() - 1); // sift up from its current place
}


/// order by out-max

int ExtractMax(CArray& arr) {
    assert(!arr.isEmpty());
    
    int result = arr[0];
    arr.deleteFirst();
    if (!arr.isEmpty()) {
        SiftDown(arr, 0);
    }
    return result;
}


/*
 Тупики. Очередь электричек, упорядоченных по времени отъезда.
 Извлекаются отбывшие электрички на момент прибытия новой.
 */


int min_routes(int* time_in, int* time_out, int n){
    // sort by out..
    
    // reheap heap on every arr item..
    
    
    return 0;
}


int main(){
    int n = 0;
    std::cin >> n;
    
    int heap_time_in[n]; // прибытие
    int heap_time_out[n]; // отбытие
    for (int i = 0; i < n; ++i) {
        std::cin >> heap_time_in[i] >> heap_time_out[i];
    }
    
    int res = min_routes(heap_time_in, heap_time_out, n);
    std::cout << "Min routes = " << res;
}


