//
//  main.c
//  c_B3_parser
//
//  Created by Владимир on 12.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


// check if current char is operator
size_t is_operator(char to_check) {
    if (to_check == '+' ||
        to_check == '-' ||
        to_check == '*' ||
        to_check == '/')
        return 1;
    else
        return 0;
}


// evaulates array in Postfix
double evaulate_rpn(char** exp, size_t len) {
    double* stack = (double* ) malloc(len*sizeof(double)); // stack for operands
    size_t place = 0;
    
    // used to process sub eval
    double a1 = 0.0;
    double a2 = 0.0;
    
    for (size_t i = 0; i < len; ++i) {
        printf("%s\n", exp[i]);
        
        if ( is_operator(*exp[i]) == 1) {
            // takes out last 2 operands, processes
            if (place > 1) {
                a1 = stack[place - 2];
                a2 = stack[place - 1];
                
                if (strncmp(exp[i], "+", 1) == 0)
                    stack[place - 2] = a1 + a2;
                else if (strncmp(exp[i], "-", 1) == 0)
                    stack[place - 2] = a1 - a2;
                else if (strncmp(exp[i], "*", 1) == 0)
                    stack[place - 2] = a1 * a2;
                else if (strncmp(exp[i], "/", 1) == 0)
                    stack[place - 2] = a1 / a2;
                
                place -= 1;
            } else {
                // wrong order / anything else
                printf("[error]");
                exit(1);
            }
        } else {
            // is operand -> convert char to double -> save double to stack
            stack[place] = atof(exp[i]);
            place++ ;
        }
    }
    return stack[0]; // result here
}



// transform from Infix to Postfix notation
double create_rpn(char* exp, size_t len){
    char buffer; // one current char
    //char* doubles = (char* ) malloc(len*sizeof(char)); // to convert string to double
    
    char** stack = (char** ) malloc(len*sizeof(char* )); // stack for numbers, operators
    
    size_t index = 0;
    size_t top = 0;  // position of last item in stack
    //size_t flag = 0; // used to separate digits
    
    while (index < len) {
        buffer = exp[index]; //printf("%c\n", buffer);
        
        if (buffer == '(' || buffer == ')' ) {
            // pull out of stack?
            
        } else {
            
            /*if ( is_operator(buffer) == 1 ) {
                // operator...
                
            } else {
             
             // operand!
             
             // parse doubles
             
            }*/
        }
        index++ ;
    }
    return evaulate_rpn(stack, top);
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
        //double result = create_rpn(expression, len);
        
        //char* test[] = {"1", "2", "+", "3", "4", "-", "+"}; // 2.00
        //char* test[] = {"10.3", "2", "+", "3", "4", "+", "+"}; // 19.30
        char* test[] = {"11", "3", "9", "*", "+"}; // 38.00
        double result = evaulate_rpn(test, sizeof(test)/sizeof(char* ));
        printf("%.2f", result);
        free(expression);
    }
    return 0;
}
