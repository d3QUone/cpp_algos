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
    char* line =(char* ) malloc(MAX_SIZE*sizeof(char));
    size_t error = 0; // 1 -> return error?
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
                while (line[j] != '\0' && j <= key_size) {
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
            
            if (error == 1) {
                printf("[error]"); // when???
            }
        }
    }
    free(line);
}


int main(){
    // init an array of nulls
    char** big_array = calloc(MAX_SIZE, sizeof(char* )*MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; ++i) {
        big_array[i] = calloc(MAX_SIZE, sizeof(char));
    }
    
    // fill array while any data
    size_t size = 0;
    char* buff = (char* ) malloc(MAX_SIZE*sizeof(char));
    while (gets(buff) != NULL) {
        strcpy(big_array[size], buff);
        size += 1;
    }
    free(buff);
    
    // debug...
    printf("\n------ check inp ------\ngot %zu lines\n\n", size);
    for (size_t i = 0; i < size; ++i) {
        printf("%s\n", big_array[i]);
    }
    
    // init an array of nulls to store result there
    char** result = calloc(size, sizeof(char* )*MAX_SIZE);
    for (int i = 0; i < size; ++i) {
        result[i] = calloc(MAX_SIZE, sizeof(char));
    }
    
    printf("\n------ do mail filter ------\n");
    mail_filter(big_array, size, result);
    
    printf("\n------ return output ------\n");
    for (size_t i = 0; i < size; ++i) {
        printf("%s\n", result[i]);
    }
    
    free(big_array);
    free(result);
    return 0;
}


/*
int main(int argc, const char * argv[]) {
    // read input strings
    char** big_array_of_strings = malloc(100*sizeof(char*));
    char buffer[STRING_MAX_SIZE];
    
    for (int i = 0; i < 100; ++i) {
        scanf("%1024[\n]", buffer);
        big_array_of_strings[i] = buffer;
        
 
        for (int c = 0; c < STRING_MAX_SIZE; ++c) {
            scanf("%c", &buffer[c]);  reads one char only
        }
 
    }
    
    free(big_array_of_strings);
    
    //mail_filter(&a, &b);
    //printf(b);
    
    return 0;
}*/