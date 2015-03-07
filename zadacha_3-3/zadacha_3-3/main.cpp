//
//  main.cpp
//  zadacha_3-3
//
//  Created by Владимир on 01.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>
#include <cmath>

/*
 3_3.

 Даны два массива неповторяющихся целых чисел, упорядоченные по неубыванию.
 A[0..n­1] и B[0..m­1]. n >> m. Найдите их пересечение. Требуемое время работы: O(m * log k), где k ­- позиция
 элемента B[m­1] в массиве A.. В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i­1].
*/


void repeat_arrs(int n, int m, int* A, int* B, int* res_size, int* res) {
    // find B in A
    int log = int(std::log(n)) + 2;
    //std::cout << "int(log)+1: " << log << ", log: " << std::log(n);
    
    int p = 0; // last power of 2
    int t_p = 1; // 2^p
    
    int ret_size = 0;
    
    // fix 2^0 == 1..
    if (A[0] == B[0]) {
        res[ret_size] = A[0];
        ret_size += 1;
    }
    
    for (int i = 1;  i < m; ++i) {
        for (int j = p; j < log + 1; ++j) {
            
            t_p = int(pow(2, j)); // buffer, count this power only once
    
            if (A[t_p] <= B[i] && A[t_p*2] > B[i]) {
                
                for (int x = t_p; x < t_p*2 && x < n ; ++x) {
                    if (A[x] == B[i]) {
                        p = j;
                        res[ret_size] = A[x];
                        ret_size += 1;
                    }
                }
            }
        }
    }
    *res_size = ret_size;
}


int main(int argc, const char * argv[]) {
    // fill in array sizes
    int n = 0; int m = 0;
    std::cin >> n >> m;
    
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
    int res_size = 0; // can be only less or equal 'm'
    int* res = new int[m];
    
    // process all var'n'pointers
    repeat_arrs(n, m, A, B, &res_size, res);
    for (int i = 0; i < res_size; ++i) {
        std::cout << res[i] << " ";
    }
    
    // finish
    delete [] A; delete [] B; delete [] res;
    return 0;
}
