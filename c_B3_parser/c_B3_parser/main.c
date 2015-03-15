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


// needs to check priority
size_t get_power(char op) {
    if (op == '+')
        return 1;
    else if (op == '-')
        return 2;
    else if (op == '*')
        return 3;
    else if (op == '/')
        return 4;
    else if (op == 'm') // let binary minus has max priority
        return 5;
    else
        return 0;
}


// check if current char is operator
size_t operator_allowed(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/' || op == 'm')
        return 1;
    else
        return 0;
}


size_t digit_allowed(char op) {
    if (op == '1' || op == '2' || op == '3' ||
        op == '4' || op == '5' || op == '6' ||
        op == '7' || op == '8' || op == '9' ||
        op == '0' || op == '.')
        return 1;
    else
        return 0;
}


// evaulates array in Postfix
double evaulate_rpn(char* exp, size_t len) {
    double* stack = (double* ) malloc(len*sizeof(double)); // stack for operands
    size_t place = 0; // current stack size
    
    double a1 = 0.0;
    double a2 = 0.0; // buffers to save stack items
    
    //char* buffer = (char* )malloc(30);
    char buffer;
    size_t x0 = 0; // index of last space
    
    for (size_t i = 0; i < len; ++i) {
        if (exp[i] == ' ') {
            for (size_t j = x0; j < i; ++j) {
                buffer += exp[j]; // ? strcat ?
            }
            x0 = i + 1;
            printf("buf = %c", buffer);
        }
        /*
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
                exit(0);
            }
        } else {
            // is operand -> convert char to double -> save double to stack
            stack[place] = atof(exp[i]);
            place++ ;
        }
         */
    }
    return stack[0]; // result here
}



// transform from Infix to Postfix notation
double create_rpn(char* exp, size_t len){
    // stack for ()+-*/
    char* stack = (char* ) malloc(len*sizeof(char));
    size_t stack_top = 0;  // position of last item in stack
    
    // string for saving postfix notation
    char* result_str = (char* ) malloc(len*sizeof(char));
    size_t result_size = 0;
    
    char buffer; // one current char
    int bracket_deep = 0; // ? may be no need // check inside Stack repush
    size_t index = 0;
    while (index < len) {
        buffer = exp[index]; //printf("'%c', size = %zu\n", buffer, sizeof(buffer));
        
        if (digit_allowed(buffer) == 1) {
            result_str += buffer;
            
        } else if (operator_allowed(buffer) == 1) {
            stack += buffer;
            stack_top++ ;
            
            // pop -> push to res
            
        } else if (buffer == '(') {
            stack += buffer; // ok, but how to remove?
            stack_top++ ;
            //printf("check: %s\n", stack[top]);

            bracket_deep++ ;
            
        } else if (buffer == ')') {
            bracket_deep-- ;
            
            // in any case add Space and Buffer when pushing into result!
            
            // pop all from the end untill (
            
            while (buffer != '(') {
                buffer = stack[stack_top];
                
                result_str += ' ' + buffer;
                
                if (stack_top == 0) {
                    break;
                } else {
                    stack_top-- ;
                }
                
                printf("current buffer '%c', top: %zu\n", buffer, stack_top);
            }
        }
        else {
            // wrong char!
            printf("[error] - wrong char: '%c'", buffer);
            exit(0);
        }
        
        if (bracket_deep < 0) {
            printf("--wrong bracket expr!\n");
            exit(0);
        }
        
        index++ ;
    }
    
    // present result
    if (bracket_deep == 0)
        //return evaulate_rpn(stack, stack_top);
        return 0.0;
    else {
        // wrong brackets
        printf("[error] - wrong brackets");
        exit(0);
    }
}


int main(int argc, const char * argv[]) {
    char* expression = (char* ) malloc(MAX_LEN*sizeof(char));
    if (expression == NULL) {
        printf("[error]");
        exit(0);
    } else {
        // get input
        size_t len = 0;
        
        // switch to getch ???
        while (scanf("%c", &expression[len]) != -1) {
            if (expression[len] != ' ') {
                len++ ;
                // save everything except spaces
            }
            // can add resizing later here!
        }
        /*
        printf("\ncheck input:\n");
        for (int i = 0; i < len; ++i) {
            printf("%c", expression[i]);
        }
        exit(0);
        */
        
        //double result = create_rpn(expression, len);
        
        // -- v1 func --
        //char* test[] = {"1", "2", "+", "3", "4", "-", "+"}; // 2.00
        //char* test[] = {"10.3", "2", "+", "3", "4", "+", "+"}; // 19.30
        //char* test[] = {"11", "3", "9", "*", "+"}; // 38.00
        //double result = evaulate_rpn(test, sizeof(test)/sizeof(char* ));
        
        // -- v2 func --
        char* test = "10.3 20.1 + 31 491.3 - +";
        double result = evaulate_rpn(test, sizeof(test));
        
        //printf("%.2f", result);
        free(expression);
    }
    return 0;
}
