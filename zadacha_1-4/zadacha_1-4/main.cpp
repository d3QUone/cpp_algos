//
//  Created by Владимир on 28.02.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

// or: void f(int& x)
// x = 1

/*
// задача 1_4
// Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) максимален, A <= B.
// Вывести A и B. Если возможно несколько ответов - вывести ответ с минимальным A. Пример:
void get_NOD(int N, int* num, int* denum){
    int NOD = 0; int B = 0;
    for (int A = N/2; A > 0; --A) {
        // ищется максимальное А при котором остаток ноль - т.е А есть НОД
        B = N - A;
        if (B % A == 0) {
            NOD = A;
            break;
        }
    }
    *num = NOD;
    *denum = N - NOD;
}


char *f(){
    static char s[256]; // +- static
    strcpy(s, "Hello world!");
    return s;
}


int main(int argc, const char * argv[]) {
 
    int N = 0; int A = 0; int B = 0;
    std::cin >> N;
    get_NOD(N, &A, &B);
    std::cout << A << " " << B;
    return 0;
 
    printf("%s\n", f());
    fflush(stdout);
    return 0;
}
*/


int g = 0x70;
int foo(){
    return g << 1;
}
int bar(){
    int g = 70;
    return g << 2;
}
int main(int, char* []){
    std::cout << std::hex << (foo() | bar()) << std::endl;
}
