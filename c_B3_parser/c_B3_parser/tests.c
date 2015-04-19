//
//  tests.c
//  c_B3_parser
//
//  Created by Владимир on 19.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <stdio.h>


void print_strings(char** array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%s ", array[i]);
    }
    printf("\n");
}


void push_to_stack(char*** reverse, size_t* out_lines, size_t* used_lines, char* item, size_t size) {
    if(*out_lines >= *used_lines){
        *out_lines *= 2;
        *reverse = (char** )realloc(*reverse, *out_lines * sizeof(char**));
    }
    
    char* str = calloc(size + 1, sizeof(char));
    if (str) {
        
        //    for(int i = 0; i < size; i++){
        //        str[i] = item[i];
        //    }
        memcpy(str, item, size + 1);
        //str[size] = '\0';
        
        *reverse[*used_lines] = str;
        *used_lines++;
    } else {
        printf("[error] - no memory2");
        exit(0);
    }
}


// testing 'push_to_stack'
int main(){
    size_t out_lines = 1;
    size_t used_lines = 0;
    char** reverse = (char** ) malloc(out_lines*sizeof(char* ));
    
    size_t n = 4;
    const char* test[] = {"10.3cc", "20.1", "31", "491.3"};
    
    for (size_t i = 0; i < n; ++i) {
        push_to_stack(&reverse, &out_lines, &used_lines, test[i], sizeof(test[i]));
        print_strings(reverse, out_lines);
    }
    
    printf("\nDone\n");
    return 0;
}



