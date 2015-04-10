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
10 5
1 2 3 4 5 6 7 8 9 10
 
*/


/*
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
*/