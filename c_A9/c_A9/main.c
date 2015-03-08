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
const char* keys[] = {"Date:", "From:", "To:", "Subject:"}; //printf("%s\n", keys[3]);


void mail_filter(char** inp, size_t lines, char** out){
    char* line = (char* ) malloc(MAX_SIZE*sizeof(char));
    size_t j = 0;
    size_t key_size = 0;
    size_t parsed_ok = 0; // 1 - match, 0 - no matches
    size_t current_out_index = 0;
    
    for (size_t i = 0; i < lines; ++i){
        line = inp[i];
        parsed_ok = 1;
        for (size_t t = 0; t < AMOUNT_OF_KEYS; ++t) {
            if (line[0] == keys[t][0]) {
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
    }
    free(line);
}

//Стандартная функция calloc(n, size) возвращает указатель на n элементов памяти
//размера size, заполненных нулями.

int main(){
    // init an array of nulls, n=MAX_SIZE items
    char** big_array = (char** ) calloc(MAX_SIZE, sizeof(char** ));
    if (big_array == NULL) {
        printf("[error]");
        free(big_array);
        exit(1); // vg-exitcode
    }
    // 1 line, MAX_SIZE-lenght
    else for (int i = 0; i < MAX_SIZE; ++i) big_array[i] = calloc(1, MAX_SIZE*sizeof(char));
    
    // fill array while any data
    size_t size = 0;
    char* buff = (char* ) malloc(MAX_SIZE*sizeof(char* ));
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
        exit(1); // vg-exitcode
    }
    
    /*
    // debug...
    printf("\n------ check inp ------\ngot %zu lines\n\n", size);
    for (size_t i = 0; i < size; ++i) {
        printf("%s", big_array[i]);
    }*/
    
    
    // init an array of nulls to store result there
    char** result = calloc(size, sizeof(char* ));
    for (int i = 0; i < size; ++i) {
        result[i] = calloc(1, MAX_SIZE*sizeof(char));
    }
    mail_filter(big_array, size, result);

    for (size_t i = 0; i < size; ++i) {
        printf("%s", result[i]);
        free(result[i]); //// -- leak
    }
    free(result); //// -- leak
    
    for (int i = 0; i < MAX_SIZE; ++i) free(big_array[i]); // smth wrong here! // invalid free()
    free(big_array); //// -- leak

    return 0;
}