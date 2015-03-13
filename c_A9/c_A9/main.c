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


void mail_filter(char** inp, size_t lines, char** out, size_t* out_size){
    char* line = (char* )malloc(MAX_SIZE*sizeof(char));
    size_t j = 0;
    size_t key_size = 0;
    size_t parsed_ok = 0; // 1 - match, 0 - no matches
    size_t current_out_index = 0;
    
    for (size_t i = 0; i < lines; ++i){
        strcpy(line, inp[i]); // perfect
        parsed_ok = 1;
        for (size_t t = 0; t < AMOUNT_OF_KEYS; ++t) {
            if (line[0] == keys[t][0]) {
                j = 1; // cause j = 0 already passed
                
                // process data while not end-of-line OR while key is true
                key_size = strlen(keys[t]);
                while (line[j] != '\n' && j < key_size) {
                    if (line[j] != keys[t][j]) {
                        parsed_ok = 0;
                        break; // it is not a key
                    }
                    j += 1;
                }
                if (parsed_ok == 1) {
                    out[current_out_index] = (char* )malloc(MAX_SIZE*sizeof(char)); // allocate on-the-go
                    strcpy(out[current_out_index], line); // perfect
                    current_out_index += 1;
                    break; // one key was found, no more in current char
                }
            }
        }
    }
    *out_size = current_out_index;
    free(line);
}


int main(){
    char** big_array = (char** )malloc(MAX_SIZE*sizeof(char* ));
    if (big_array == NULL) {
        printf("[error]");
        exit(1);
    }
    
    // fill array while any data
    size_t size = 0;
    char* buff = (char* )malloc(MAX_SIZE*sizeof(char));
    while (fgets(buff, MAX_SIZE, stdin) != NULL) {
        big_array[size] = (char* )malloc(MAX_SIZE*sizeof(char)); // allocate on-the-go
        strcpy(big_array[size], buff);
        size += 1;
    }
    free(buff);
    
    if (size == 0) {
        free(big_array);
        printf("[error]");
        exit(1);
    }
    /*
    // debug...
    printf("\n------ check inp ------\ngot %zu lines\n\n", size);
    for (size_t i = 0; i < size; ++i) {
        printf("%s", big_array[i]);
    }*/
    
    char** result = (char** )malloc(size*sizeof(char* ));
    if (result == NULL) {
        printf("[error]");
        exit(1);
    }
    
    // process
    size_t out_size = 0;
    mail_filter(big_array, size, result, &out_size);
    for (size_t i = 0; i < out_size; ++i) {
        printf("%s", result[i]);
    }
    
    // free
    for (size_t i = 0; i < size; ++i) {
        free(big_array[i]);
        
        if (i < out_size) {
            free(result[i]);
        }
    }
    free(big_array);
    free(result);
    return 0;
}