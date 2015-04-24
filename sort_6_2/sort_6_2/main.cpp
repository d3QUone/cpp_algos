//
//  main.cpp
//  sort_6_2
//
//  Created by Владимир on 22.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

#define TOTAL_BYTES 256

void LSD(long long* array, int size, long long min_value) {
    long long* result = new long long[size];
    int* sub_array = new int[TOTAL_BYTES];
    int count;
    
    // do LSD
    for (int i = 0; i < 8; ++i) {
        // refill array of i-bits every cycle
        int* bits = new int[size];
        for (int j = 0; j < size; ++j) {
            bits[j] = (array[j] >> 8*i) & (TOTAL_BYTES - 1);
            result[j] = 0;
        }
        for (int j = 0; j < TOTAL_BYTES; ++j) {
            sub_array[j] = 0;
        }
        
        // init other counters
        count = 0;
        for (int j = 0; j < size; ++j) {
            ++sub_array[bits[j]];
        }
        
        for (int j = 0; j < TOTAL_BYTES; ++j) {
            int buf = sub_array[j];
            sub_array[j] = count;
            count += buf;
        }
        
        for (int j = 0; j < size; ++j) {
            result[sub_array[bits[j]]] = array[j];
            ++sub_array[bits[j]];
        }
        
        for (int j = 0; j < size; ++j) {
            array[j] = result[j];
        }
        delete [] bits;
    }
    delete [] result;
    delete [] sub_array;
}


int main(){
    int n = 0;
    std::cin >> n;
    long long* input = new long long[n];
    long long inp_min = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> input[i];
        if (input[i] < inp_min || i == 0) {
            inp_min = input[i];   // to reduce amount of used bytes
        }
    }
    
    LSD(input, n, inp_min);
    //std::cout << "Result: ";
    for (int i = 0; i < n; ++i) {
        std::cout << input[i] << " ";
    }
    
    delete [] input;
    return 0;
}
