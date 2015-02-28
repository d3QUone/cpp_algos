//
//  main.cpp
//  cpp_first_lect
//
//  Created by Владимир on 28.02.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    
    // slide 22 example
    int a[128] = {5, [120] = 1, 2, 3};
    std::cout << "pointer to the first item: " << *a << "\n";
    for (int i = 1; i < 128; ++i) {
        std::cout << a[i] << " ";
    }
    
}
