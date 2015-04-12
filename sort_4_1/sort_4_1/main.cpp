//
//  main.cpp
//  sort_4_1
//
//  Created by Владимир on 12.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


// реализовать стратегию выбора опорного элемента "медиана трех"
// (ср арифметического от первого, центрального и последнего эл-тов)


template <class T>
T median_of_three(T* a0, T* a1, T* a2, bool (*is_less)(const T&, const T&)){
    if (is_less(*a2, *a0)) {
        std::swap(*a2, *a0);
    }
    
    if (is_less(*a2, *a1)) {
        std::swap(*a2, *a1);
        return *a2;
    } else {
        if (is_less(*a0, *a1)) {
            return *a1;
        } else {
            std::swap(*a0, *a1);
            return *a0;
        }
    }
}


template <class T>
T partition(T* array, int asize, bool (*is_less)(const T&, const T&)){

    // find base item
    int i = 0;
    int j = asize-1;
    int base_index = asize/2;
    T base = median_of_three(&array[i], &array[base_index], &array[j], is_less);
    
    
    for (; i < asize; ) {
        
        if (array[i] < array[base_index]) {
            
        }
        
    }
    
    return 0;
}



bool compare_ints(const int& L, const int& R) {
    return L < R;
}


// -- test --
int main_median_test() {
    int test[3] = {1, 2, 3};
    int res = median_of_three<int>(&test[0], &test[1], &test[2], compare_ints);
    std::cout << res << "\n";
    
    for (int i = 0; i < 3; ++i) {
        std::cout << test[i] << " ";
    }
    return 0;
}


// -- partition test --
int main() {
    
    // - demo

    int n = 8;
    int array[] = {2, 8, 7, 1, 3, 5, 6, 4};
    
    // - in release
    
//    std::cin >> n;
//    int* array = new int[n];
//    for (int i = 0; i < n; ++i) {
//        std::cin >> array[i];
//    }
    
    int K_stat = partition<int>(array, n, compare_ints);
    std::cout << K_stat;
    
    return 0;
}
