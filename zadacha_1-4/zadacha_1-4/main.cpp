//
//  Created by Владимир on 28.02.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

// or: void f(int& x)
// x = 1


// задача 1_4
// Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) максимален, A <= B.
// Вывести A и B. Если возможно несколько ответов - вывести ответ с минимальным A. Пример:
void get_NOD(int N, int* num, int* denum){
    int NOD = 0;
    for (int A = 1; 2*A <= N; ++A) {
        int B = N - A;
        // ищется максимальное А при котором остаток ноль - т.е А есть НОД 
        if (B % A == 0) {
            if (A > NOD) {
                NOD = A;
            }
        }
    }
    *num = NOD;
    *denum = N - NOD;
}


int main(int argc, const char * argv[]) {
    int N = 0; int A = 0; int B = 0;
    std::cin >> N;
    get_NOD(N, &A, &B);
    std::cout << A << " " << B;
    //std::cout << "\n-----\n" << A << " " << B;
    return 0;
}
