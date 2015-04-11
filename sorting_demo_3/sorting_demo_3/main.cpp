//
//  main.cpp
//  sorting_demo_3
//
//  Created by Владимир on 11.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


void countSort(int* data, int n) {
    int minValue = data[0];
    int maxValue = data[0];
    for (int i = 1; i < n; ++i) {
        minValue = std::min(minValue, data[i]);
        maxValue = std::max(maxValue, data[i]);
    }
    int valueCount = maxValue - minValue + 1;
    int* valuesData = new int[valueCount];
    
    std::memset(valuesData, 0, valueCount*sizeof(int)); // better for char
    
    for (int i = 0; i < n; ++i) {
        valuesData[data[i] - minValue]++;
    }
    
    // simple variant, but unstable
//    int index = 0;
//    for (int i = 0; i < valueCount; ++i) {
//        for (int j = 0; j < valuesData[i]; ++j) {
//            data[index] = i + minValue;
//            index++ ;
//        }
//    }
    
    // better for LSD
    for (int i = 1; i < n; ++i) {
        valuesData[i] += valuesData[i - 1];
    }
    
    int* tempData = new int[n];
    for (int i = n - 1; i >= 0; --i) {
        int valueIndex = data[i] - minValue;
        valuesData[valueIndex]-- ;
        tempData[valuesData[valueIndex]] = data[i];
    }
    std::memcpy(data, tempData, n*sizeof(int));
    delete [] tempData;
}


int main(){
    int n;
    int* data = new int[n];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    
    countSort(data, n);
    
    for (int i = 0; i < n; ++i) {
        std::cout << data[i] << " ";
    }
    delete [] data;
    return 0;
}