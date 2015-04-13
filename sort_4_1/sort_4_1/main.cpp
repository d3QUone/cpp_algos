//
//  main.cpp
//  sort_4_1
//
//  Created by Владимир on 12.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


bool compare_ints(const int& L, const int& R) {
    return L < R;
}

// реализовать стратегию выбора опорного элемента "медиана трех"
// (ср арифметического от первого, центрального и последнего эл-тов)

/*
 // issues with placing
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
}*/


template <class T>
T median_of_three(T* arr, int l, int r, bool (*is_less)(const T&, const T&)) {
    int cntr = (r - l)/2;
    if (is_less(arr[r], arr[l])) {
        std::swap(arr[r], arr[l]);
    }
    if (is_less(arr[cntr], arr[l])) {
        std::swap(arr[cntr], arr[l]);
    }
    if (is_less(arr[r], arr[cntr])) {
        std::swap(arr[r], arr[cntr]);
    }
    std::swap(arr[cntr], arr[r-1]);
    return arr[r-1];
}


// returns an index
template <class T>
int partition(T* arr, int l, int r, bool (*is_less)(const T&, const T&)) {
    
    T pivot = median_of_three<T>(arr, l, r, is_less);
    std::cout << "pvt=" << pivot << "\n";
    
    int i = l;
    int j = l + 1;
    int base_index = r - 1;
    
    //std::cout << "itm: " << arr[l] << " " << arr[base_index] << " " << arr[r] << "\n";
    //std::cout << "ind: " << l << " " << base_index << " " << r << "\n";
    
    /*
    while (j < base_index && i < base_index) {
        if (is_less(pivot, arr[j])) {
            j++ ;
        } else {
            std::swap(arr[i++ ], arr[j++ ]);
//            std::swap(arr[i], )
        }
        
        for (int a = l; a <= r; ++a) {
            std::cout << arr[a] << " ";
        } std::cout << "\n";
    }*/
    
    while (is_less(pivot, arr[j]) && j < base_index) {
        j++ ;
    }
    
    while (is_less(arr[j], pivot) && j < base_index) {
        std::swap(arr[i++ ], arr[j++ ]);
        
//        for (int a = l; a <= r; ++a) {
//            std::cout << arr[a] << " ";
//        } std::cout << "\n";
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


/*
template <class T>
void find_stats(T* array, int asize, bool (*is_less)(const T&, const T&)){
    int base_index = asize/2; // base item will be here
    T base = median_of_three(&array[0], &array[base_index], &array[asize-1], is_less);
    std::cout << "Base = " << base << "\n\n";
    
    std::swap(array[asize-1], array[base_index]);
    base_index = asize - 1;
    
    int i = 0; // points to the begining of sorted group
    int j = 1; // points to the next item
    for (; i < base_index && j < base_index;) {
        std::cout << "i=" << i << ", j=" << j << " arr[j]=" << array[j] << "\n";
        if (array[j] > array[base_index]) {
            j++ ;
        } else {
            i++ ;
            
            std::cout << "swap " << array[i] << " " << array[j] << "\n";
            std::swap(array[i], array[j++ ]);
        }
        
        
        for (int x = 0; x < asize; ++x) {
            std::cout << array[x] << " ";
        } std::cout << "\n\n";
    }
    
    // last step..
    std::swap(array[base_index], array[++i]);
}
*/


int main() {
    int n = 8;
    int array[] = {2, 8, 7, 1, 3, 26, 5, 40};
    int correct[] = {1, 2, 3, 5, 7, 8, 26, 40};
    
    for (int k = 0; k < n; k++) {
        
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


int maixvcxn(){
    int t[8] = {2, 8, 7, 1, 3, 26, 5, 40};;
    std::cout << median_of_three<int>(t, 0, 7, compare_ints) << "\n";
    
    for (int i = 0; i < 8; ++i) {
        std::cout << t[i] << " ";
    }
    return 0;
}


int release() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    int* array = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    
    return 0;
}
