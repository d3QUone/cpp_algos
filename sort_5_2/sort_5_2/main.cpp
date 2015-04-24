//
//  main.cpp
//  sort_5_2
//
//  Created by Владимир on 24.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


template <class T>
void merge_sort(T* array, int size, int k) {
    
}



int main(){
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    
    int* array = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    
    merge_sort<int>(array, n, k);
    
    for (int i = 0; i < n; ++i) {
        std::cout << array[i];
    }
}