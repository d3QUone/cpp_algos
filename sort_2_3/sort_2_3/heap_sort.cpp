//
//  heap_sort.cpp
//  sort_2_3
//
//  Created by Владимир on 10.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <stdio.h>


/*
 template <class T>
 void sift_up(T* arr, int len, bool (*is_less)(const T&, const T&)){
 
 }
 
 template <class T>
 void sift_down(T* arr, int len, bool (*is_less)(const T&, const T&)){
 
 }
 
 template <class T>
 void sort(T* arr, int len, bool (*is_less)(const T&, const T&)){
 
 }
 */

// insert 'x' in heap, 'n' - current heap size
template <class T>
void heap_insert(T* arr, int n, T item, bool (*is_less)(const T&, const T&)){
    // insert
    arr[n+1] = item;
    
    // do sift-up
    for (int i = n + 1; i > 1; --i) {
        //int parent = i/2;
        int left_child = (i/2 + 1);
        int right_child = (i/2 + 2);
        if (i == right_child && is_less(arr[right_child], arr[left_child])) {
            std::swap(arr[right_child], arr[left_child]);
        }
        
        std::cout << "i=" << i << " i/2=" << i/2 << "\n";
        std::cout << "left=" << left_child << " right=" << right_child << "\n";
        
        if (is_less(arr[i], arr[i/2])) {
            std::swap(arr[i], arr[i/2]);
            i /= 2;
        } else {
            break;
        }
    }
}


template <class T>
void heap_pop(T* arr, int n, bool (*is_less)(const T&, const T&)){
    std::swap(arr[n], arr[1]);
    for (int i = 1; 2*i < n;) {
        i *= 2;
        if (i + 1 < n && is_less(arr[i], arr[i+1])) {
            i += 1;
        }
        if (is_less(arr[i/2], arr[i])) {
            std::swap(arr[i/2], arr[i]);
        }
    }
}


template <class T>
void make_heap(T* arr, int n, bool (*is_less)(const T&, const T&)) {
    for (int i = n/2; i >= 1; --i) {
        for (int j = i; j <= n/2;) {
            int k = j*2;
            if (k + 1 <= n && is_less(arr[k], arr[k+1])) {
                ++k;
            }
            
            if (is_less(arr[j], arr[k])) {
                std::swap(arr[j], arr[k]);
                j = k;
            } else {
                break;
            }
        }
    }
}


template <class T>
void heap_sort(T* arr, int n, bool (*is_less)(const T&, const T&), void present(T* arr, int n)) {
    //make_heap(arr, n, is_less); /// <- fix!
    //present(arr, n);
    
    T* buf = new T[n+1];
    for (int i = 0; i < n; ++i) {
        heap_insert(buf, i, arr[i], is_less);
        
        std::cout << "Insert: \n";
        present(buf, n+1);
    }
    for (int i = 0; i < n; ++i) {
        arr[n-1-i] = buf[1];
        heap_pop(buf, n-i, is_less);
        
        //std::cout << "\nPop " << arr[n-1-i] << " -> " << n-i-1 << "\n";
        std::cout << "\nPop\n";
        present(buf, n+1);
        present(arr, n);
    }
    delete [] buf;
}


////////////////////////////////////////////////////////////////////////////////////////////


template <class T>
void quick_heap_sort(T* arr, int n, bool (*is_less)(const T&, const T&)) {
    make_heap(arr - 1, n, is_less);
    for (int i = 0; i < n; ++i) {
        heap_pop(arr - 1, n, is_less);
    }
}


////////////////////////new sorting/////////////////////////////////////////////////////////


template <class T>
void max_heapify(T a[], int size, int i) {
    int left =  (i + 1) * 2 - 1;
    int right = (i + 1) * 2;
    int largest = i;
    if (left < size && a[left] > a[largest])
        largest = left;
    if (right < size && a[right] > a[largest])
        largest = right;
    if (largest != i) {
        std::swap(a[i], a[largest]);
        
        max_heapify(a, size, largest); // <- fuck this
    
    }
}

template <class T>
void build_max_heap(T a[], int size) {
    for (int i = size / 2; i >= 0; i--) {
        max_heapify(a, size, i);
    }
}

template <class T>
void heapsort(T a[], int size) {
    build_max_heap(a, size);
    int heap_size = size;
    for (int i = size-1; i > 0; i--) {
        std::swap(a[0], a[i]);
        heap_size--;
        max_heapify(a, heap_size, 0);
    }
}

