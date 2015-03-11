//
//  main.c
//  c_A9
//
//  Created by Владимир on 04.03.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Чтобы показать информацию о пришедшем письме, нужно сначала её найти.
 Для этого в файле письма необходимо найти специальные заголовки. Составить программу построчной фильтрации текста.
 Суть фильтра — отбор строк, начинающихся с одного из следующих выражений: «Date:», «From:»,«To:», «Subject:».
 Текстовые строки подаются на стандартный ввод программы, результат программы должен подаваться на стандартный вывод.
 Процедура фильтрации должна быть оформлена в виде отдельной функции, которой подается на вход массив строк, выделенных в динамической памяти и его длина.
 На выходе функция возвращает указатель на NULL-терминированный массив с найденными строками (последним элементом массива добавлен NULL для обозначения, что данных больше нет).
 Программа должна уметь обрабатывать возникающие ошибки (например, ошибки выделения памяти). В случае возникновения ошибки нужно вывести в поток стандартного вывода сообщение "[error]" и завершить выполнение программы.
*/

#define MAX_SIZE 1024 // 1024 chars in string, 1024 strings
#define AMOUNT_OF_KEYS 4
const char* keys[] = {"Date:", "From:", "To:", "Subject:"};


void mail_filter(char* inp, size_t characters, char* out, size_t* out_size){
    
    size_t key_size = 0;
    size_t parsed_ok = 0; // 1 - match, 0 - no matches
    size_t current_out_index = 0;
    
    
    size_t i = 0; // global search
    size_t j = 0; // in-key search
    char current; // saves current char

    
    while (i < characters){
        current = inp[i];
        parsed_ok = 1;
        
        for (size_t t = 0; t < AMOUNT_OF_KEYS; ++t) {
            if (current == keys[t][0]) {
                j = 1; // cause 0 is alredy passed
                key_size = strlen(keys[t]);  //printf("\nkey_size: %zu\n", key_size);
                
                // process data while not end-of-line OR while key is true
                while (line[j] != '\n' && j < key_size) {
                    if (line[j] != keys[t][j]) {
                        parsed_ok = 0;
                        break; // error
                    }
                    j += 1;
                }
                if (parsed_ok == 1) {
                    out[current_out_index] = line;
                    current_out_index += 1;
                }
            }
        }
        i ++ ;
    }
    *out_size = current_out_index;
}


int main() {
    char* array = (char*)malloc(MAX_SIZE);
    if (array == NULL) {
        printf("[error]");
        exit(1);
    } else {
        size_t filled = 0; // number of chars in array
        
        // read from stdin
        while (scanf("%c", &array[filled]) != -1) {
            if (array[filled] != ' ') {
                filled++;
            }
            if (filled % MAX_SIZE == 0) {
                // array is filled, create new..
                char* buffer = (char*)malloc(2*filled);
                
                if (buffer != NULL) {
                    memcpy(buffer, array, filled);
                    
                    if ((char *)realloc(array, 2*filled) != NULL) { // be careful here
                        memcpy(array, buffer, filled);
                        free(buffer);
                    } else {
                        free(array); // no memory
                        free(buffer);
                        printf("[error]");
                        exit(1);
                    }
                } else {
                    free(array); // no memory
                    printf("[error]");
                    exit(1);
                }
            }
        }
        
        // check input:
//        printf("\n\n--checkup--\n\n");
//        for (size_t i = 0; i < filled; ++i) {
//            printf("%c", array[i]);
//        }
        
        // parse data ...
        char* result = (char*)malloc(filled); // calloc(size, sizeof(char* ));
        if (result == NULL) {
            printf("[error]");
            free(array);
            exit(1);
        } else {
            size_t out_size = 0;
            mail_filter(array, filled, result, &out_size);
            
            for (size_t i = 0; i < out_size; ++i) {
                printf("%c", result[i]);
            }
            free(result);
            free(array);
        }
    }
    return 0;
}

/*
int main(){
    char* big_array = (char*)malloc(MAX_SIZE*sizeof(char* ));
    if (big_array == NULL) {
        printf("[error]");
        exit(1);
    } else {
        for (size_t i = 0; i < MAX_SIZE; ++i) {
            //big_array[i] = (char*) malloc(MAX_SIZE); // calloc(1, sizeof(char* ));
        }
    }
    
    // fill array while any data
    size_t size = 0;
    char* buff = (char*)malloc(MAX_SIZE);
    while (fgets(buff, MAX_SIZE, stdin) != 0) {
        strcpy(big_array[size], buff);
        size += 1;
    }
    free(buff); buff = NULL;
    
    if (size == 0) {
        printf("[error]");
        for (int i = 0; i < MAX_SIZE; ++i) {
            free(big_array[i]);
        }
        free(big_array); big_array = NULL;
        exit(1);
    }
 
    // debug...
//    printf("\n------ check inp ------\ngot %zu lines\n\n", size);
//    for (size_t i = 0; i < size; ++i) {
//        printf("%s", big_array[i]);
//    }
 
    char** result = (char** ) malloc(size*sizeof(char* )); // calloc(size, sizeof(char* ));
    if (result == NULL) {
        printf("[error]");
        exit(1);
    } else {
        for (size_t i = 0; i < size; ++i) {
            result[i] = (char* ) malloc(MAX_SIZE); //calloc(1, sizeof(char* ));
        }
    }
    
    size_t out_size = 0;
    mail_filter(big_array, size, result, &out_size);
    for (size_t i = 0; i < out_size; ++i) {
        printf("%s", result[i]);
        //free(result[i]); //// -- leak
    }
    
    for (size_t i = 0; i < out_size; ++i) {
        free(result[i]); //// -- leak at '\0'
    }
    free(result); result = NULL;
    
    for (size_t i = 0; i < MAX_SIZE; ++i) {
        free(big_array[i]); // smth wrong here! // invalid free() '\0'
    }
    free(big_array); big_array = NULL;
    return 0;
}*/

