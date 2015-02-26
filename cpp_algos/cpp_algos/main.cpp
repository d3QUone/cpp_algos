//
//  main.cpp
//  cpp_algos
//
//  Created by Владимир on 25.02.15.
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

int main(int argc, const char * argv[]) {
    //std::cout << "Hello, World!\n";
    
    printf("%.1f\n", Power(2, 100));
    return 0;
}
