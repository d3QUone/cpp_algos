//
//  main.c
//  c_B3_parser
//
//  Created by Владимир on 12.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


/*

Требуется написать программу, которая способна вычислять арифметические выражения.
Выражения могут содержать: 
 1) знаки операций '+', '-', '/', '*' 
 2) Скобки '(', ')' 
 3) Целые и вещественные числа, в нотации '123', '123.345', все операции должны быть вещественны, а результаты выведены с точностю до двух знаков после запятой в том числе целые '2.00' 
 4) необходимо учитывать приоритеты операций, и возможность унарного минуса, пробелы ничего не значат 
 5) Если в выражении встретилась ошибка требуется вывести в стандартный поток вывода "[error]"
 
*/

#define MAX_LEN 1024


// add simple stack here?...



size_t operators(char to_check) {
    if (to_check == '+' ||
        to_check == '-' ||
        to_check == '*' ||
        to_check == '/')
        return 1;
    else
        return 0;
}


// Reverse Polish Notation - processor
double RPN(char* exp, size_t len){
    double result = 0.0;
    
    // .1234567890+-*/()
    
    // - check if char is 'enabled' -> parse doubles
    
    // - find the deepest sub-expression
    
    // - eval in recursion?
    
    return result;
}


int main(int argc, const char * argv[]) {
    char* expression = (char* ) malloc(MAX_LEN*sizeof(char));
    if (expression == NULL) {
        printf("[error]");
        exit(1);
    } else {
        // get input
        size_t len = 0;
        while (scanf("%c", &expression[len]) != -1) {
            if (expression[len] != ' ') {
                len ++;
                // save everything except spaces
            }
            
            // can add resizing later here!
        }
        double result = RPN(expression, len);
        printf("%.2f", result);
        free(expression);
    }
    return 0;
}
