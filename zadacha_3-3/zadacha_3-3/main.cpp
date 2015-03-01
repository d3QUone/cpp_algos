//
//  main.cpp
//  zadacha_3-3
//
//  Created by Владимир on 01.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

//
// 3_3.
//
// Даны два массива неповторяющихся целых чисел, упорядоченные по неубыванию.
// A[0..n­1] и B[0..m­1]. n >> m. Найдите их пересечение. Требуемое время работы: O(m * log k), где k ­- позиция
// элемента B[m­1] в массиве A.. В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом
// поиска элемента B[i­1].


void repeat_arrs(int n, int m, int* A, int* B, int* res_size, int* res) {
    // find B in A
    
    int bufer = 0;
    int ret_size = 0;
    for (int i = 0; i < n; ++i) {
        bufer = A[i];
        for (int j = ret_size; j < m; ++j) {
            // j = 0 may be wrong
            if (bufer == B[j]) {
                res[ret_size] = bufer;
                ret_size += 1;
            }
        }
    }
    *res_size = ret_size;
}


int main(int argc, const char * argv[]) {
    // fill in array sizes
    int n = 0; int m = 0;
    std::cin >> n;
    std::cin >> m;
    
    // fill in arrays
    int* A = new int[n];
    for (int i = 0; i < n; ++i){
        std::cin >> A[i];
    }
    int* B = new int[m];
    for (int i = 0; i < m; ++i){
        std::cin >> B[i];
    }
    
    // prepare result template
    int res_size = 0;
    int* res = new int[n];
    
    // process all var'n'pointers
    repeat_arrs(n, m, A, B, &res_size, res);
    for (int i = 0; i < res_size; ++i) {
        std::cout << res[i] << " ";
    }
    // finish
    delete [] A; delete [] B; delete [] res;
    return 0;
}
