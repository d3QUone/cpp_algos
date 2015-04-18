//
//  main.cpp
//  sort_4_1
//
//  Created by Владимир on 12.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

/*
 
 4_1. ​Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 
*/


bool compare_ints(const int& L, const int& R) {
    return L < R;
}


template <class T>
T median_of_three(T* arr, int l, int r, bool (*is_less)(const T&, const T&)) {
    int cntr = (r + l + 1)/2;
    if (is_less(arr[r], arr[l])) {
        std::swap(arr[r], arr[l]);
    }
    if (is_less(arr[cntr], arr[l])) {
        std::swap(arr[cntr], arr[l]);
    }
    if (is_less(arr[r], arr[cntr])) {
        std::swap(arr[r], arr[cntr]);
    }
    std::swap(arr[cntr], arr[r]);
    return arr[r];
}


// returns an index
template <class T>
int partition(T* arr, int l, int r, bool (*is_less)(const T&, const T&)) {
    T pivot = median_of_three<T>(arr, l, r, is_less);
    
    int i = l;
    int j = l + 1;
    int pivot_index = r;
    while (j < pivot_index) {
        if (is_less(pivot, arr[j])) {
            j++ ;
        } else {
            std::swap(arr[++i ], arr[j++ ]);
        }
    }
    
    if (i + 1 < r) {
        i++ ;
        std::swap(arr[pivot_index], arr[i]);
    }
    return i;
}


template <class T>
T find_K_stat(T* array, int asize, int k, bool (*is_less)(const T&, const T&)) {
    int l = 0;
    int r = asize - 1;
    while (true) {
        int index = partition(array, l, r, is_less);
        if (index == k) {
            return array[k];
        } else if (k < index) {
            r = index;
        } else {
            l = index + 1;
        }
    }
}



int main_test() {
//    int n = 8;
//    int array[] = {2, 8, 7, 1, 3, 26, 5, 40};
//    int correct[] = {1, 2, 3, 5, 7, 8, 26, 40};

    int n = 10;
    for (int k = 0; k < n; k++) {
        
        int array[] = {3, 10, 5, 2, 1, 8, 13, 6, 9, 11};
        int correct[] = {1, 2, 3, 5, 6, 8, 9, 10, 11, 13};
        
        int res = find_K_stat<int>(array, n, k, compare_ints);
        std::cout << "K(" << k << ")=" << res;

        if (res != correct[k]) {
            std::cout << ", INCORRECT -> K(" << k << ")=" << correct[k];
        }
        std::cout << "\n";
        
        std::cout << "Processed arr: ";
        for (int i = 0; i < n; ++i) {
            std::cout << array[i] << " ";
        } std::cout << "\n-------------------------------------\n";
    }
    return 0;
}

/*
int maixvcxn(){
    int t[8] = {2, 8, 7, 1, 3, 26, 5, 40};;
    std::cout << median_of_three<int>(t, 0, 7, compare_ints) << "\n";
    
    for (int i = 0; i < 8; ++i) {
        std::cout << t[i] << " ";
    }
    return 0;
}
*/

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    int* array = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    std::cout << find_K_stat<int>(array, n, k, compare_ints);
    return 0;
}
