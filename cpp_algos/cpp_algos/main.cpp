//
//  main.cpp
//  cpp_algos
//
//  Created by Vladimir on 25.02.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

// returns a^n
double Power(double a, int n) {
    double result = 1.0;
    double aInDegreeOf2 = a;
    while (n > 0) {
        if ((n & 1) == 1) {
            result *= aInDegreeOf2;
        }
        aInDegreeOf2 *= aInDegreeOf2;
        n = n >> 1;
    }
    return result;
}


// 28 feb 2015 updates

// найти все простые числа в [1, n]
int main(int argc, const char * argv[]) {
    // get 'n' from input
    int maxN = 0;
    std::cin >> maxN;
    
    // init bool array
    bool *isPrime = new bool[maxN + 1];
    // i*i <= maxN
    for (int i = 0; i <= maxN; ++i){
        isPrime[i] = true;
    }
    
    // do Eratosfer stuff
    for (int i= 2; i <= maxN; ++i){
        // remove all next kratn nums
        if (isPrime[i]) {
            // j = i*i
            for (int j = 2*i; j <= maxN; j += i ) {
                isPrime[j] = false;
            }
        }
    }
    
    // return result
    for (int i = 0; i <= maxN; ++i) {
        if (isPrime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
    delete [] isPrime;
    return 0;
}
