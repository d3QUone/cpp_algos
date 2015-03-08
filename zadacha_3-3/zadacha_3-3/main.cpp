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
    int log = int(std::log2(n)) + 1; //// - EJEDGE THROWS AN EXCEPTION HERE (NO LOG2 IN IT, LOL)
    //std::cout << "log = " << log << ", 2^log = " << pow(2, log) << "\n";
    
    int p = 0; // last used power of 2
    int t_p = 1; // 2^p
    int t_p_2 = 2; // 2*2^p
    int ret_size = 0; // stores return-arr-size (== last index)
    
    // binary search init
    // int min = 0; int max = 0;
    int mid = 0;
    
    int saved = 0;
    
    // fix i = 0, cause 2^0 == 1..
    int i = 0; int j = 0;
    if (A[0] == B[0]) {
        res[ret_size] = A[0];
        ret_size += 1;
        i = 1;
    }
    
    for (; i < m; ++i) {
        saved = 0;

        // seek among powers of 2
        j = p; // last (max used) power of 2
        while (j <= log) {
            t_p = int(pow(2, j)); // bufferize to count this power only once
            
            // ok, but I have to process end of array, with indexes < 2^max_power
            // e.g. I have 10 items, but 2^max_power that covers all my items is 16 -- so I have to
            // work with 2*t_p = n-1 when 2*t_p > n
            
            if (A[t_p] <= B[i]) {
                if (2*t_p > n) t_p_2 = n - 1; // fuck yeah! last bug!
                else t_p_2 = 2*t_p;
                
                if (A[t_p_2] > B[i]) {
                    // do binary-search here
                    while (true) {
                        mid = t_p + (t_p_2 - t_p)/2;
                        if (B[i] > A[mid]) {
                            t_p = mid;
                        } else if (B[i] == A[mid]) {
                            p = j;
                            res[ret_size] = A[mid];
                            ret_size += 1;
                            saved = 1;
                            break;
                        } else {
                            t_p_2 = mid;
                        }
                    }
                }
            }
            j += 1;
            
            // out cycle if found smth cause B[i] is const on this level
            if (saved == 1) break;
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
