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

void print_strings(char** , size_t);

void print_chars(char* , size_t);


// needs to check priority
size_t get_power(char op) {
    if (op == '+') {
        return 2;
    } else if (op == '-') {
        return 2;
    } else if (op == '*') {
        return 4;
    } else if (op == '/') {
        return 4;
    } else if (op == 'm') {
        return 5;  // let unary minus has max priority ???? absolutly not tested
    } else {
        return 0;
    }
}


// checks if current char is operator
size_t is_operator(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/' || op == 'm') {
        return 1;
    } else {
        return 0;
    }
}


// checks if current char is digit
size_t is_digit(char op) {
    if ((op >= '0' && op <= '9') || op == '.') {
        return 1;
    } else {
        return 0;
    }
}


// evaulates array in Postfix
/*
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
        
//        if ( is_operator(*exp[i]) == 1) {
//            // takes out last 2 operands, processes
//            if (place > 1) {
//                a1 = stack[place - 2];
//                a2 = stack[place - 1];
//                
//                if (strncmp(exp[i], "+", 1) == 0)
//                    stack[place - 2] = a1 + a2;
//                else if (strncmp(exp[i], "-", 1) == 0)
//                    stack[place - 2] = a1 - a2;
//                else if (strncmp(exp[i], "*", 1) == 0)
//                    stack[place - 2] = a1 * a2;
//                else if (strncmp(exp[i], "/", 1) == 0)
//                    stack[place - 2] = a1 / a2;
//                
//                place -= 1;
//            } else {
//                // wrong order / anything else
//                printf("[error]");
//                exit(0);
//            }
//        } else {
//            // is operand -> convert char to double -> save double to stack
//            stack[place] = atof(exp[i]);
//            place++ ;
//        }
        
    }
    return stack[0]; // result here
}
*/


void push_to_stack(char*** reverse, size_t* inited_lines, size_t* used_lines, const char* item, size_t size) {
    if(*inited_lines >= *used_lines){
        *inited_lines *= 2;
        char** buf = (char** ) realloc(*reverse, (*inited_lines)*sizeof(char** ));
        if (buf) {
            *reverse = buf;
        } else {
            printf("[error] - no memory");
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
        printf("[error] - no memory2");
        exit(0);
    }
}


// testing 'push_to_stack'
int main_TEST_PTS(){
    size_t inited_lines = 1;
    size_t used_lines = 0;
    char** reverse = (char** ) malloc(inited_lines*sizeof(char* ));
    
    size_t n = 4;
    const char* test[] = {"10.3", "20.1", "31", "491.3"};
    
    for (size_t i = 0; i < n; ++i) {
        push_to_stack(&reverse, &inited_lines, &used_lines, test[i], strlen(test[i]));
        print_strings(reverse, used_lines);
    }
    printf("Done\n");
    return 0;
}


// transform from Infix to Postfix notation
double create_rpn(char* exp, size_t len){
    printf("Exp: %s, %zu chars\n", exp, len);
    
    int bracket_deep = 0; // ? may be no need // check inside Stack repush
    
    // stack of chars for operands ()+-*/
    char* stack = (char* ) malloc(len*sizeof(char));
    size_t stack_top = 0;  // position of last item in stack
    
    // array of numbers
    size_t inited_lines = 1;
    size_t used_lines = 0;
    char** reverse = (char** ) malloc(inited_lines*sizeof(char* ));
    
    char* buffer = (char* ) malloc(1); // for one current char
    
    int digit = 0; // flag to start parsing Numbers/digits
    size_t start_index = 0; // for parsing Long-Vals
    
    size_t index = 0;
    while (index <= len) {
        // buffer constats only 1 char but it is a string
        memcpy(buffer, &exp[index], 1);

        if (*buffer != ' ') {
            printf("buffer: '%s'\n", buffer);
        }
        
        if (is_digit(*buffer) == 1) {
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
                
                printf("\nRPN: ");
                print_strings(reverse, used_lines);
            }
            
            // push Operands + check priority
            if (is_operator(*buffer) == 1) {
                size_t power = get_power(*buffer);
                for (int i = stack_top; i >= 0; --i) {
                    if (stack[i] == '(') {
                        break;
                    }
                    
                    if (get_power(stack[i]) >= power) {
                        push_to_stack(&reverse, &inited_lines, &used_lines, &stack[i], 1);
                        stack_top-- ;
                    }
                }
                // push current Operand to stack
                stack[stack_top++ ] = *buffer;
                
                printf("\n~stack now: ");
                print_chars(stack, stack_top);

                printf("~result updated: ");
                print_strings(reverse, used_lines);
                
            } else if (*buffer == '(') {
                stack[stack_top++ ] = *buffer;
                
                bracket_deep++ ;
                
                printf("-stack now: ");
                print_chars(stack, stack_top);
            } else if (*buffer == ')') {
                // push operands to result
                bracket_deep-- ;
                stack_top --;
                while (stack[stack_top] != '(') {
                    push_to_stack(&reverse, &inited_lines, &used_lines, &stack[stack_top], 1);
                    printf("current item '%c', stack size: %zu\n", stack[stack_top], stack_top);
                    if (stack_top > 0) {
                        stack_top-- ;
                    } else {
                        break;
                    }
                }
                stack_top --; // delete '('
                
                printf(".stack check: ");
                print_chars(stack, stack_top);
                
                printf(".result str: ");
                print_strings(reverse, used_lines);
                
            } else if (*buffer == ' ') {
                // ignore this case
            } else if (*buffer == 0) {
                printf("EOF - push %zu from stack\n", stack_top);
                for (int i = stack_top; i >= 0; --i) {
                    push_to_stack(&reverse, &inited_lines, &used_lines, &stack[i], 1);
                }
                stack_top = 0;
            } else {
                printf("[error] - wrong char: '%s', %c\n", buffer, *buffer); // wrong char!
                exit(0);
            }
        }
        
        if (bracket_deep < 0) {
            printf("--wrong bracket expr!\n");
            exit(0);
        }
        index++ ;
    }
    free(buffer);
    
    if (bracket_deep == 0) {
        //return evaulate_rpn(stack, stack_top);
        
        printf("\nout stack check:\n");
        print_chars(stack, stack_top);
        
        printf("\nout result str:\n");
        print_strings(reverse, used_lines);
        return 0.0;
    } else {
        // wrong brackets
        printf("[error] - wrong brackets");
        exit(0);
    }
}


int main(){
    //char* expression = "(10.3  +20.1 + 31)- 491.3";    // -> "10.3 20.1 + 31 + 491.3 -"
//    char* expression = "3 + 4 * 2 / ( 1 - 5)";
//    char* rpn = "3 4 2 * 1 5 - / +";
    
    char* expression = "((3 + 4) * 2 - 7) / 13";
    char* rpn = "3 4 2 * + 7 - 13 /";
    
    double result = create_rpn(expression, strlen(expression));
    
    // -- v1 func --
    //char* test[] = {"1", "2", "+", "3", "4", "-", "+"}; // 2.00
    //char* test[] = {"10.3", "2", "+", "3", "4", "+", "+"}; // 19.30
    //char* test[] = {"11", "3", "9", "*", "+"}; // 38.00
    //double result = evaulate_rpn(test, sizeof(test)/sizeof(char* ));
    
    // -- v2 func --
    //char* test = "10.3 20.1 + 31 491.3 - +";
    //double result = evaulate_rpn(test, sizeof(test));
    
    printf("%.2f\n", result);
    printf("%s", rpn);
    return 0;
}


int main_rel() {
    char* expression = (char* ) malloc(MAX_LEN*sizeof(char));
    if (expression == NULL) {
        printf("[error]");
        exit(0);
    } else {
        // get input
        size_t len = 0;
        
        // switch to getch ???
        while (scanf("%c", &expression[len]) != -1) {
            // save everything except spaces
            if (expression[len] != ' ') {
                len++ ;
            }
            // can add resizing later here!
        }
        double result = create_rpn(expression, len);
        printf("%.2f", result);
        free(expression);
    }
    return 0;
}


///// PRINTING FUNCTIONS /////

void print_strings(char** array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%s ", array[i]);
    }
    printf("\n");
}


void print_chars(char* array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%c", array[i]);
    }
    printf("\n");
}
