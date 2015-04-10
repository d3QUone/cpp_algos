//
//  heap_sort.cpp
//  sort_2_3
//
//  Created by Владимир on 10.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <stdio.h>


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
    std::swap(arr[1], arr[n]); // top item is out

    // i = 1 - base parent, sift down now
    for (int i = 1; 2*i < n;) {
        int max_child = 2*i; // first it is left_child
        if (max_child + 1 < n && is_less(arr[max_child + 1], arr[max_child])){
            max_child++ ;
        }
        
        //std::cout << "max_child on " << max_child << " = " << arr[max_child] << "\n";
        if (is_less(arr[max_child], arr[i])) {
            std::swap(arr[i], arr[max_child]);
        }
        i *= 2;
    }
}

/*
// is not tested yet
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
void quick_heap_sort(T* arr, int n, bool (*is_less)(const T&, const T&)) {
    make_heap(arr - 1, n, is_less);
    for (int i = 0; i < n; ++i) {
        heap_pop(arr - 1, n, is_less);
    }
}
*/


template <class T>
void heap_sort(T* arr, int n, bool (*is_less)(const T&, const T&), void present(T* arr, int start, int stop)){
    T* buf = new T[n+1];
    for (int i = 0; i < n; ++i) {
        heap_insert(buf, i, arr[i], is_less);
        
        std::cout << "Insert: \n";
        present(buf, 1, i+2);
    }
    std::cout << "//////////////////////////////////////////////\n\n";
    for (int i = 0; i < n; ++i) {
        arr[i] = buf[1];
        heap_pop(buf, n-i, is_less);
        
        std::cout << "Pop " << arr[n-1-i] << " -> " << n-i-1 << "\n";
        std::cout << "Pop\n";
        present(buf, 1, n+1-i);
        present(arr, 0, n);
    }
    delete [] buf;
}


// release
template <class T>
void heap_sort(T* arr, int n, bool (*is_less)(const T&, const T&)){
    T* buf = new T[n+1];
    for (int i = 0; i < n; ++i) {
        heap_insert(buf, i, arr[i], is_less);
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = buf[1];
        heap_pop(buf, n-i, is_less);
    }
    delete [] buf;
}