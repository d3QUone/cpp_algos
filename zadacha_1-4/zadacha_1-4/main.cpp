//
//  main.cpp
//  zadacha_1-4
//
//  Created by Владимир on 28.02.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


void get_NOD(int N, int* num, int* denum){
    int NOD = 0;
    for (int A = 2; 2*A <= N; ++A) {
        int B = N - A;
        if (B % A == 0) {
            if (A > NOD) {
                NOD = A;
            }
        }
    }
    int A = NOD;
    int B = N - A;
    //std::cout << "inside func " << A << " " << B << "\n";
    
    *num = A;
    *denum = B;
}


int main(int argc, const char * argv[]) {
    int N = 0; int A = 0; int B = 0;
    std::cin >> N;
    get_NOD(N, &A, &B);
    
    std::cout << A << " " << B;
    return 0;
}
