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
Выражения могут содержать: знаки операций '+', '-', '/', '*', cкобки '(', ')', целые и вещественные числа
в нотации '123', '123.345'.
все операции должны быть вещественны, а результаты выведены с точностю до двух знаков после запятой в том
числе целые '2.00'. необходимо учитывать приоритеты операций, и возможность унарного минуса, 
пробелы ничего не значат
Если в выражении встретилась ошибка требуется вывести в стандартный поток вывода "[error]"
*/

#define MAX_LEN 1024

// needs to check priority
int get_power(char op) {
    if (op == '+') {
        return 2;
    } else if (op == '-') {
        return 2;
    } else if (op == '*') {
        return 4;
    } else if (op == '/') {
        return 4;
    } else {
        return 0;
    }
}


// checks if current char is operator
int is_operator(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/') {
        return 1;
    } else {
        return 0;
    }
}


// checks if current char is digit
int is_digit(char op) {
    if ((op >= '0' && op <= '9') || op == '.') {
        return 1;
    } else {
        return 0;
    }
}


// evaulates array in Postfix
double evaulate_rpn(char** exp, size_t len) {
    double* stack = (double* ) malloc(len*sizeof(double)); // stack for operands
    double a1 = 0.0;
    double a2 = 0.0;  // buffers to save stack items
    size_t place = 0; // current stack size
    for (size_t i = 0; i < len; ++i) {
        if (is_operator(*exp[i]) == 1) {
            // takes out last 2 operands, processes
            if (place > 1) {
                a1 = stack[place - 2];
                a2 = stack[place - 1];
                
                if (strncmp(exp[i], "+", 1) == 0) {
                    stack[place - 2] = a1 + a2;
                } else if (strncmp(exp[i], "-", 1) == 0) {
                    stack[place - 2] = a1 - a2;
                } else if (strncmp(exp[i], "*", 1) == 0) {
                    stack[place - 2] = a1 * a2;
                } else if (strncmp(exp[i], "/", 1) == 0) {
                    stack[place - 2] = a1 / a2;
                }
                place -= 1;
                
            } else if (place == 1) {
                // unary minus, unary plus..
                a1 = stack[place - 1];
                
                if (strncmp(exp[i], "-", 1) == 0) {
                    stack[place - 1] = 0 - a1;
                } else if (strncmp(exp[i], "+", 1) == 0) {
                    stack[place - 1] = a1;
                }
                
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
    }
    float res = stack[0];
    free(stack);
    return res; // result here
}


void push_to_stack(char*** reverse, size_t* inited_lines, size_t* used_lines, char* item, size_t size) {
    if(*inited_lines <= *used_lines){
        *inited_lines *= 2;
        char** buf = (char** ) realloc(*reverse, (*inited_lines)*sizeof(char** ));
        if (buf) {
            *reverse = buf;
        } else {
            printf("[error]");
            exit(0);
        }
    }
    char* str = calloc(size + 1, sizeof(char));
    if (str) {
        memcpy(str, item, size + 1);
        str[size] = '\0';
        
        (*reverse)[*used_lines] = str;
        (*used_lines)++ ;
    } else {
        printf("[error]");
        exit(0);
    }
}


// transform from Infix to Postfix notation
double create_rpn(char* exp, size_t len){
    
    // stack of chars for operands ()+-*/
    char* stack = (char* ) malloc(len);
    if (stack == NULL) {
        printf("[error]");
        exit(0);
    }
    size_t stack_top = 0;  // position of last item in stack
    
    // array of numbers
    size_t inited_lines = 1;
    size_t used_lines = 0;
    char** reverse = (char** ) malloc(inited_lines*sizeof(char* ));
    if (reverse == NULL) {
        printf("[error]");
        exit(0);
    }
    
    char buffer;
    
    int bracket_deep = 0;
    int digit = 0; // flag to start parsing Numbers/digits
    size_t start_index = 0; // for parsing Long-Vals
    size_t index = 0;
    while (index <= len) {
        buffer = exp[index];  // buffer constats only 1 char but it is a string
        if (is_digit(buffer) == 1) {
            // save first digit place
            if (digit == 0) {
                start_index = index;
                digit = 1;
            }
        } else {
            // push to stack when Num is over
            if (digit == 1) {
                digit = 0;
                size_t size = index - start_index; // size of str
                push_to_stack(&reverse, &inited_lines, &used_lines, exp + start_index, size);
            }
            
            // push Operands + check priority
            if (is_operator(buffer) == 1) {
                size_t power = get_power(buffer);
                for (int i = stack_top - 1; i >= 0; --i) {
                    if (stack[i] == '(') {
                        break;
                    }
                    if (get_power(stack[i]) >= power) {
                        push_to_stack(&reverse, &inited_lines, &used_lines, &stack[i], 1);
                        stack_top-- ;
                    }
                }
                // push current Operand to stack
                stack[stack_top++ ] = buffer;
                
            } else if (buffer == '(') {
                stack[stack_top++ ] = buffer;
                bracket_deep++ ;
                
            } else if (buffer == ')') {
                // push operands to result
                bracket_deep-- ;
                stack_top-- ; // if no, '' will be added to output
                while (stack[stack_top] != '(') {
                    push_to_stack(&reverse, &inited_lines, &used_lines, &stack[stack_top], 1);
                    if (stack_top > 0) {
                        stack_top-- ;
                    } else {
                        break;
                    }
                }
            } else if (buffer == ' ' || buffer == '\n') {
                // ignore this case
                
            } else if (buffer == '\0') {
                for (int i = stack_top - 1; i >= 0; --i) {
                    push_to_stack(&reverse, &inited_lines, &used_lines, &stack[i], 1);
                }
                stack_top = 0;
            } else {
                printf("[error]"); // - wrong char: '%s', %c\n", buffer, *buffer); // wrong char!
                exit(0);
            }
        }
        if (bracket_deep < 0) {
            printf("[error]"); // wrong bracket expr
            exit(0);
        }
        index++ ;
    }
    free(stack);
    
    if (bracket_deep == 0) {
        double res = evaulate_rpn(reverse, used_lines);
        for (int i = 0; i < inited_lines; i++) {
            free(reverse[i]);
        }
        free(reverse);
        return res;
    } else {
        printf("[error]");  // wrong brackets
        exit(0);
    }
}


int main() {
    char* expression = (char* ) malloc(MAX_LEN*sizeof(char));
    if (expression) {
        size_t len = 0;
        while (scanf("%c", &expression[len]) != -1) {   // switch to getch ???
            if (expression[len] != ' ') {   // save everything except spaces
                len++ ;
            }
        }
        //expression[len] = '\0';
        double result = create_rpn(expression, len);
        printf("%.2f", result);
    } else {
        printf("[error]");
        exit(0);
    }
    free(expression);
    return 0;
}
