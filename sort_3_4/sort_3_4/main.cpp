//
//  main.cpp
//  sort_3_4
//
//  Created by Владимир on 11.04.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


struct Dot {
    int x;
    bool flag = false;
};


bool is_less(const Dot& L, const Dot& R) {
    if (L.flag == R.flag) {
        return L.x < R.x;
    } else {
        return L.flag;
        
//        // the same...
//        if (L.flag == true) {
//            return true;
//        } else {
//            return false;
//        }
        
    }
}


// for merge-sort test
//bool is_less(const Dot& L, const Dot& R) {
//    return L.x < R.x;
//}


template <class T>
void merge_sort(T* arr, int len, bool (*is_less)(const T&, const T&)) {
    T* buf = new T[len];
    
    // split array into K parts
    for (int k = 1; k < len; k *= 2) {
        
        for (int left = 0; left + k < len; left += 2*k) {
            int right = left + k;
            
            int rend = right + k; // why?
            if (rend > len) rend = len;
            
            int out_index = left;
            int i = left;
            int j = right;
            
            while (i < right && j < rend) {
                if (is_less(arr[i], arr[j])) {
                    buf[out_index++ ] = arr[i++ ];
                } else {
                    buf[out_index++ ] = arr[j++ ];
                }
            }
            
            while (i < right) {
                buf[out_index++ ] = arr[i++ ];
            }
            
            while (j < rend) {
                buf[out_index++ ] = arr[j++ ];
            }
            
            // save into target array
            for (out_index = left; out_index < rend; out_index++) {
                arr[out_index] = buf[out_index];
            }
        }
    }
}


int main(){
    int n = 0;
    std::cin >> n;
    Dot* input = new Dot[2*n];
    for (int i = 0; i < n; ++i) {
        std::cin >> input[2*i].x >> input[2*i + 1].x;
        input[2*i].flag = true;         // start-point
        //input[2*i + 1].flag = false;    // end-point
    }
    
    merge_sort<Dot>(input, 2*n, is_less);
    
    for (int i = 0; i < 2*n; ++i) {
        std::cout << input[i].x << " ";
    }
    return 0;
}
