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
#include <vector>


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


int get_sin(const CPoint& point) {
    return (CPoint::baseX - point.x)/sqrt(CPoint::baseX*point.x + CPoint::baseY*point.y);
}


bool angle(const CPoint& L, const CPoint& R){
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
    }
    for (int i = 0; i < n; ++i) {
        arr[n-1-i] = buf[1];
        heap_pop(buf, n-i, is_less);
    }
}


int main(){

    // 1 - sort by point absolute pos
    
    int n = 0;
    std::cin >> n;

    CPoint min;
    CPoint* arr = new CPoint[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].x >> arr[i].y;
        
        // get min point
        if (i == 0) {
            min.x = arr[0].x;
            min.y = arr[0].y;
        } else {
            if (item_is_less(arr[i], min)) {
                min = arr[i];
            }
        }
    }
    
    std::cout << "Min: " << min.x << " " << min.y << "\n";
    CPoint::SetBase(min.x, min.y);
    
    heap_sort<CPoint>(arr, n, angle);
    
    std::cout << "Result:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i].x << " " << arr[i].y << "\n";
    }
    
    delete [] arr;
    return 0;
}


/*
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
*/