//
//  main.cpp
//  sort_2_3
//
//  Created by Владимир on 01.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <math.h>

struct CPoint {
    int x;
    int y;

    static void SetBase(int x, int y) { baseX = x; baseY = y; }
    static int baseX;
    static int baseY;

};

int CPoint::baseX=0;
int CPoint::baseY=0;


// first round
bool item_is_less(const CPoint& L, const CPoint& R){
    if (L.x != R.x) {
        return L.x < R.x;
    } else {
        return L.y < R.y;
    }
}


double get_sin(const CPoint& point) {
    if (CPoint::baseY - point.y != 0) {
        return atan((CPoint::baseX - point.x)/(CPoint::baseY - point.y));
    } else {
        return sqrt(2)/2;
    }
}


bool angle(const CPoint& L, const CPoint& R){
    std::cout << CPoint::baseX << " " << CPoint::baseY << " -- " << L.x << " " << L.y << ", atan = " << get_sin(L) << "\n";
    std::cout << CPoint::baseX << " " << CPoint::baseY << " -- " << R.x << " " << R.y << ", atan = " << get_sin(R) << "\n\n";
    
    return get_sin(L) < get_sin(R);
}


template <class T>
void heap_insert(T* arr, int n, T x, bool (*is_less)(const T&, const T&)){
    arr[n+1] = x;
    
    for (int i = n + 1; i > 1; --i) {
        if (is_less(arr[i/2], arr[i])) {
            std::swap(arr[i], arr[i/2]);
            i = i/2;
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

/*
template <class T>
void make_heap(T* arr, int n, bool (*is_less)(const T&, const T&)) {
    int k = 0;
    for (int i = n/2; i >= 1; --i) {
        for (int j = i; j <= n/2;) {
            k = j*2;
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
*/

/*
// issue with first item
template <class T>
void quick_heap_sort(T* arr, int n, bool (*is_less)(const T&, const T&)) {
    make_heap(arr - 1, n, is_less);
    for (int i = 0; i < n; ++i) {
        heap_pop(arr - 1, n, is_less);
    }
}
*/


template <class T>
void heap_sort(T* arr, int n, bool (*is_less)(const T&, const T&)) {
    T* buf = new T[n+1];
    for (int i = 0; i < n; ++i) {
        heap_insert(buf, i, arr[i], is_less);
        //std::cout << "i\n";
    }
    for (int i = 0; i < n; ++i) {
        arr[n-1-i] = buf[1];
        heap_pop(buf, n-i, is_less);
        //std::cout << "j\n";
    }
}


int main(){

    // 1 - sort by point absolute pos
    
    int n = 0;
    int min_point = 0;
    std::cin >> n;
    CPoint min;
    CPoint* arr = new CPoint[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].x >> arr[i].y;
        if (i == 0) {
            min = arr[0];
        } else {
            if (item_is_less(arr[i], min)) {
                min = arr[i];
                min_point = i;
            }
        }
    }
    
//    for (int i = 0; i < n; ++i) {
//        std::cout << arr[i].x << " " << arr[i].y << "\n";
//    } std::cout << "----\n";
    
    // delete dat base-point from sorting
    CPoint::SetBase(min.x, min.y);
    CPoint* new_arr = new CPoint[n-1];
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (i != min_point) {
            new_arr[j] = arr[i];
            j++;
        }
    }
    delete [] arr;
    
    heap_sort<CPoint>(new_arr, n-1, angle);
    std::cout << CPoint::baseX << " " << CPoint::baseY << "\n";
    for (int i = 0; i < n-1; ++i) {
        std::cout << new_arr[i].x << " " << new_arr[i].y << "\n";
    }
    
    delete [] new_arr;
    return 0;
}
