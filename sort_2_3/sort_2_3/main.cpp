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
#include "heap_sort.cpp"

struct CPoint {
    int x;
    int y;

    static void SetBase(int x, int y) { baseX = x; baseY = y; }
    static int baseX;
    static int baseY;

};

int CPoint::baseX=0;
int CPoint::baseY=0;


////////////////////////////// printing ////////////////////////////////////////////////////

void present_i(int* arr, int start, int stop) {
    for (int i = start; i < stop; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n\n";
}


void present_s(CPoint* arr, int start, int stop) {
    for (int i = start; i < stop; ++i) {
        std::cout << arr[i].x << " " << arr[i].y << "\n";
    }
    std::cout << "\n\n";
}


//////////////////////////////// comparing /////////////////////////////////////////////////

// tests with one-dimensional array
bool int_is_less(const int& L, const int& R){
    return L < R;
}

// first round
bool item_is_less(const CPoint& L, const CPoint& R){
    if (L.x != R.x) {
        return L.x < R.x;
    } else {
        return L.y < R.y;
    }
}

// second round
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


////////////////////////////////////////////////////////////////////////////////////////////

int maccin(){
    int n = 5;
    int* arr = new int[n+1];
    //int test[] = {1, 4, 2, 5, 3, 4}; // sorted: 1 2 3 4 4 5
    int test[] = {1, 5, 3, 4, 2}; // sorted: 1 2 3 4 5
    //int res[n];
    
    // testing heap_insert:
    for (int i = 0; i < n; ++i) {
        heap_insert<int>(arr, i, test[i], int_is_less);
        present_i(arr, 1, i+2);
    }
    
    std::cout << "Testing heap pop:\n\n";
    for (int i = 0; i < n; ++i) {
        //res[i] = arr[n-i];
        
        heap_pop<int>(arr, n-i, int_is_less);
        present_i(arr, 1, n+1);
    }
    //std::cout << "Result: ";
    //present_i(res, 0, n);
    
    delete [] arr;
    return 0;
}


// testing heap sort
int main(){
    int n = 9;
    int arr[] = {1, 4, 5, 0, 3, 4, 2, 2, 1}; // n =9
    //int arr[] = {10, 11, 1, 3}; // n = 4
    
    heap_sort<int>(arr, n, int_is_less); //present_i
    //quick_heap_sort<int>(arr, n, int_is_less);
    
    std::cout << "Result: ";
    present_i(arr, 0, n);
    return 0;
}


/////////////////////////// test task //////////////////////////////////////////////////////
/*
int mainxxx(){
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
    present_s(arr, 0, n);
    
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
    present_s(new_arr, 0, n-1);
    
    heap_sort<CPoint>(new_arr, n-1, angle, present_s);

    std::cout << CPoint::baseX << " " << CPoint::baseY << "\n";
    present_s(new_arr, 0, n-1);
    delete [] new_arr;
    return 0;
}
*/
