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
    int log = int(std::log2(n)) + 1;
    //std::cout << "log = " << log << ", 2^log = " << pow(2, log) << "\n";
    
    int p = 0; // last used power of 2
    int t_p = 1; // 2^p
    int t_p_2 = 2; // 2*2^p
    int ret_size = 0; // stores return-arr-size (== last index)
    
    // binary search init
    int min = 0; int max = 0; int mid = 0;
    
    // fix i = 0, cause 2^0 == 1..
    int i = 0; int j = 0;
    if (A[0] == B[0]) {
        res[ret_size] = A[0];
        ret_size += 1;
        i = 1;
    }
    
    int t1 = 0;
    for (; i < m; ++i) {
        t1 = B[i];  // just for debug
        
        // seek among powers of 2
        j = p; // last (max used) power of 2
        while (j <= log) {
            t_p = int(pow(2, j)); // bufferize to count this power only once
            // 2*t_p may be out of range when j = log - 1
            // 2*t_p == 2^j == 2^log / 2 ==
            
            // ok, but I have to process end of array, with indexes < 2^max_power
            // e.g. I have 10 items, but 2^max_power that covers all my items is 16 -- so I have to
            // work with 2*t_p = n when 2*t_p > n
            
            if (A[t_p] <= B[i]) {
                if (2*t_p > n) t_p_2 = n;
                else t_p_2 = 2*t_p;
                
                if (A[t_p_2] > B[i]) {
                    // do binary-search here
                    min = t_p;
                    max = 2*t_p;
                    while (true) {
                        mid = min + (max - min)/2;
                        if (B[i] > A[mid]) {
                            min = mid;
                        } else if (B[i] == A[mid]) {
                            p = j; // j + 1 ??? or dangerous?
                            res[ret_size] = A[mid];
                            ret_size += 1;
                            break;
                        } else {
                            max = mid;
                        }
                    }
                }
            }
            j += 1;
        }
    }
    *res_size = ret_size;
}


int main(int argc, const char * argv[]) {
    //for (int i = 1; i < 100; ++i) std::cout << "log2 " << i << " = " << std::log2(i) << "\n";
    //return 0;
    
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
