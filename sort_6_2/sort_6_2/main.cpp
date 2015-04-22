//
//  main.cpp
//  sort_6_2
//
//  Created by Владимир on 22.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

void LSD(long long*, int, int);
void countSort(int*, int);

int main(){
    int n = 0;
    std::cin >> n;
    
    long long* input = new long long[n];
    long long max_lenght = 0;
    
    for (int i = 0; i < n; ++i) {
        std::cin >> input[i];
        if (input[i] > max_lenght) {
            max_lenght = input[i];
        }
    }
    
    int num_of_bit = 0;
    while (max_lenght > 0) {
        max_lenght = max_lenght >> 2;
        num_of_bit += 1;
    }
    
    LSD(input, num_of_bit, n);
    for (int i = 0; i < n; ++i) {
        std::cout << input[i] << " ";
    }
    
    delete [] input;
    return 0;
}


void LSD(long long* array, int num_of_bit, int size) {
    
    for (int i = size - 1; i >= 0; ++i) {
        
        
        
        
        //char byte = array[i] << j & 1;
        
        
        
    }
    
}


void countSort(int* array, int size) {
    
}