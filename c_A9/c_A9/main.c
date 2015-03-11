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
        //memcpy(line, inp[i], MAX_SIZE);
        
        parsed_ok = 1;
        for (size_t t = 0; t < AMOUNT_OF_KEYS; ++t) {
            if (line[0] == keys[t][0]) {
                j = 1; // cause j = 0 already passed
                key_size = strlen(keys[t]);
                
                // process data while not end-of-line OR while key is true
                while (line[j] != '\n' && j < key_size) {
                    if (line[j] != keys[t][j]) {
                        parsed_ok = 0;
                        break; // error
                    }
                    j += 1;
                }
                if (parsed_ok == 1) {
                    strcpy(out[current_out_index], line); // perfect
                    current_out_index += 1;
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
    } else {
        for (size_t i = 0; i < MAX_SIZE; ++i) {
            big_array[i] = (char* )malloc(MAX_SIZE*sizeof(char));
        }
    }
    
    // fill array while any data
    size_t size = 0;
    char* buff = (char* )malloc(MAX_SIZE*sizeof(char));
    while (fgets(buff, MAX_SIZE, stdin) != 0) {
        strcpy(big_array[size], buff);
        size += 1;
    }
    free(buff);
    
    if (size == 0) {
        printf("[error]");
        for (int i = 0; i < MAX_SIZE; ++i) {
            free(big_array[i]);
        }
        free(big_array);
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
    } else {
        for (size_t i = 0; i < size; ++i) {
            result[i] = (char* )malloc(MAX_SIZE*sizeof(char));
        }
    }
    
    size_t out_size = 0;
    mail_filter(big_array, size, result, &out_size);
    for (size_t i = 0; i < out_size; ++i) {
        printf("%s", result[i]);
    }
    
    for (size_t i = 0; i < size; ++i) {
        free(result[i]);
    }
    free(result);
    
    for (size_t i = 0; i < MAX_SIZE; ++i) {
        free(big_array[i]);
    }
    free(big_array);
    return 0;
}