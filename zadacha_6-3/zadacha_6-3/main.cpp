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
// Dynamic array of ints

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


// do Heap on array!
/*
class Heap {
public:
    Heap(): size(0), buffer(0) {}
    ~Heap() { delete [] buffer; }
    
    void SiftUp();
    
private:
    int size;
    int* buffer;
};
*/



// heap methods

void SiftDown(int* arr, int size, int i){
    // branches
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    // find the largest Child
    int largest = i;
    if (left < size && arr[left] > arr[i]) {
        largest = left;
    }
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // Sift if any largest
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        SiftDown(arr, size, largest);
    }
}


void BuildHeap(int* arr, int size, int i) {
    for (int i = size/2 - 1; i >= 0; --i) {
        SiftDown(arr, size, i);
    }
}


void SiftUp(int* arr, int i) {
    int parrent = 0;
    while (i > 0) {
        parrent = (i - 1)/2;
        if (arr[i] < arr[parrent])
            break;
        std::swap(arr[i], arr[parrent]);
        i = parrent;
    }
}


void Add(int* arr, int size, int item) {
    arr[size++] = item;
    SiftUp(arr, size - 1); // sift up from its current place
}


int ExtractMax(int* arr, int size) {
    assert(size > 0);
    int result = arr[0];
    
    int* new_buffer = new int[size--];
    for (int i = 0; i < size; ++i) {
        new_buffer[i] = arr[i+1];
    }
    delete [] arr;
    arr = new_buffer;
    
    if (size != 0) {
        SiftDown(arr, size, 0);
    }
    return result;
}


/*
 Тупики. Очередь электричек, упорядоченных по времени отъезда.
 Извлекаются отбывшие электрички на момент прибытия новой.
 */


int min_routes(int* time_in, int* time_out, int n){
    int* heap = new int[n];
    int size = 0;
    
    int current_depart_time = 0;
    int current_arrive_time = 0;
    
    for (int i = 0; i < n; ++i) {
        current_arrive_time = time_in[i];
        current_depart_time = time_out[i]; // sort it: min dep-time on the top
        
        // 1) delete all trains form tail to head which have departed
        while (size > 0 && heap[size-1] < current_arrive_time) {
            size-- ;
        }
        
        // 2) Add(heap, size++, current_depart_time);
        // sort by min out..
        heap[size++] = current_depart_time;
        BuildHeap(heap, size, size-1);
        
        /*
        std::cout << "heap: ";
        for (int j = 0; j < size; ++j) {
            std::cout << heap[j] << " ";
        }
        std::cout << "\n";
        */
    }
    return size;
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
    std::cout << res;
}


