//
//  main.cpp
//  sort_5_2
//
//  Created by Владимир on 24.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


// merging - OK
template <class T>
void merge_two_arrays(T* result, T* array1, T* array2, int size1, int size2) {
    int i = 0; 
    int j = 0;
    for (; i < size1 && j < size2;) {
        if (array1[i] < array2[j]) {
            result[i + j] = array1[i];
            i++ ;
        } else {
            result[i + j] = array2[j];
            j++ ;
        }
    }
    // load lest data if any  
    if (i == size1) {
        for (; j < size2; ++j) {
            result[i + j] = array2[j];
        }
    } else if (j == size2) {
        for (; i < size1; ++i) {
            result[i + j] = array1[i];
        }
    }
}


template <class T>
void merge_sort(T* array, int size) {
    T* buf = new T[size];
    int stop;   // buffer for end index
    for (int i = 1; i < size; i *= 2) {
        int sorted = 0;
        // array[sorted..(sorted+i)] + array[(sorted+i)..(sorted + 2*i) OR end]
        for (; sorted + i < size; sorted += 2*i) {
            // find end index for second part
            if (i < size - i - sorted) {
                stop = i;
            } else {
                stop = size - i - sorted;
            }
                             // res           arr1            arr2              len1  len2
            merge_two_arrays<T>(buf + sorted, array + sorted, array + sorted + i, i, stop);
        }

        // copy the rest items
        for (int j = sorted; j < size; ++j) {
            buf[j] = array[j];
        }

        // rewrite this sorted part
        for (int j = 0; j < size; ++j) {
            array[j] = buf[j];
        }
    }
    delete [] buf;
}


template <class T>
void SORT(T* array, int size, int k) {
    int last = 0;
    if (k < size) {
        last = k;
    } else {
        last = k - size;
    }
    merge_sort(array, k);
    for (int i = k; i < size; i += k) {
        merge_sort(array + i, k); // sort all k's
        merge_two_arrays(array, array, array + i, k, last);
    }
}



int main(){
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    
    int* array = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    
    SORT<int>(array, n, k);
    
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    delete [] array;
    return 0;
}