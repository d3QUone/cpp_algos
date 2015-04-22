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
        max_lenght = max_lenght >> 1;
        num_of_bit += 1;
    }
    std::cout << "Num = " << num_of_bit << "\n";
    
    LSD(input, num_of_bit, n);
    for (int i = 0; i < n; ++i) {
        std::cout << input[i] << " ";
    }
    
    //delete [] input;
    return 0;
}


void LSD(long long* array, int num_of_bit, int size) {
    int* sub_array = new int[size];
    int* count = new int[size + 1];
    int* aux = new int[size];
    
    for (int i = 1; i <= num_of_bit; i++ ) {
        // fill array of i-bits
        for (int j = 0; j < size; ++j) {
            sub_array[j] = array[j] >> i & 1;
            std::cout << sub_array[j] << " ";
        } std::cout << "\n";
        
        count[0] = 0;
        for (int j = 0; j < size; ++j) {
            ++count[sub_array[j] + 1];
        }
        
        for (int j = 1; j < size + 1; ++j) {
            count[j] += count[j - 1];
        }
        
        for (int j = 0; j < size; ++j) {
            aux[count[sub_array[j]]++ ] = sub_array[j];
        }
        
        for (int j = 0; j < size; ++j) {
            sub_array[j] = aux[j];
        }
        
        // print res:
        for (int j = 0; j < size; ++j) {
            std::cout << sub_array[j] << " ";
        } std::cout << "\n-------------\n";
    }
    
    free(sub_array);
    free(count);
    free(aux);
}


void countSort(int* array, int size) {
    
}