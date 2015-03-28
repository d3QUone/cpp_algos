//
//  main.cpp
//  sort_1
//
//  Created by Владимир on 28.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>

/*
struct CPoint {
    int x;
    int y;
    CPoint(): x(0), y(0) {}
};

bool operator < (const CPoint& l, const CPoint& r) {
    return l.x < r.x;
}


bool is_less_x (const CPoint& l, const CPoint& r) {
    return l.x < r.x;
}

bool is_less_y (const CPoint& l, const CPoint& r) {
    return l.y < r.y;
}


template <class T>

void my_sort(T* arr, size_t l, size_t r, bool (*is_less)(const T&, const T&)) {
    for (size_t i = l; i < r; i++) {
        for (size_t j = l; j < r; j++) {
            if ( is_less(arr[j + 1], arr[j]) ) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}


int main_sem(){
    
    std::vector <CPoint> arr;
    CPoint pt;
    
    while (scanf("%d%d", &pt.x, &pt.y) == 2) {
        arr.push_back(pt);
    }
    
//    for (size_t i = 0; i < arr.size(); ++i) {
//        std::cout << arr[i].x << " " << arr[i].y << " " << "\n";
//    }
//    std::cout << "\n";
    
    my_sort<CPoint>(&arr[0], 0, arr.size(), is_less_x);
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i].x << " " << arr[i].y << " " << "\n";
    }
    
    std::cout << "\n--------\n";
    
    my_sort<CPoint>(&arr[0], 0, arr.size(), is_less_y);
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i].x << " " << arr[i].y << " " << "\n";
    }
    
    return 0;
}
*/

// compare ints
bool item_is_less(const int& l, const int& r) {
    return l < r;
}

template <class T>

void insertion_sort(T* a, size_t n, bool (*is_less)(const T&, const T&)) {
    for (size_t i = 1; i < n; ++i) {
        T tmp = a[i];
        for (size_t j = i; j > 0 && is_less(tmp, a[j-1]); --j) {
            a[j] = a[j-1];
            a[j - 1] = tmp;
        }
    }
}


int main(){
    std::vector <int> arr;
    int buf = 0;
    
    while ( scanf("%d", &buf) == 1 ) {
        arr.push_back(buf);
    }
    
    insertion_sort<int>(&arr[0], arr.size(), item_is_less);
    
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    
    return 0;
}

