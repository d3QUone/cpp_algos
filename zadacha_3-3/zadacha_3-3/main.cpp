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

// finds B in A
void repeat_arrs(int n, int m, int* A, int* B, int* res_size, int* res) {
    int log = int(std::log(n)) + 3; // + 1 to get full, +1 to maximize
    //std::cout << "int(log)+1: " << log << ", log: " << std::log(n);
    
    int p = 0; // last used power of 2
    int t_p = 1; // 2^p
    int ret_size = 0; // stores return-arr-size (== last index)
    
    // binary search init
    int min = 0; int max = 0; int mid = 0;
    
    // fix 2^0 == 1..
    if (A[0] == B[0]) {
        res[ret_size] = A[0];
        ret_size += 1;
    }
    
    for (int i = 1;  i < m; ++i) {
        for (int j = p; j <= log; ++j) {
            
            t_p = int(pow(2, j)); // bufferize to count this power only once
            if (A[t_p] <= B[i] && A[2*t_p] > B[i]) {
                // do binary-search here
                min = t_p;
                max = 2*t_p;
                while (true) {
                    mid = min + (max - min)/2;
                    if (B[i] > A[mid]) {
                        min = mid;
                    } else if (B[i] == A[mid]) {
                        p = j;
                        res[ret_size] = A[mid];
                        ret_size += 1;
                        
                        break;
                    } else {
                        max = mid;
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
