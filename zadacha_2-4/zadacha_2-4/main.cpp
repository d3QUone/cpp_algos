//
//  main.cpp
//  zadacha_2-4
//
//  Created by Владимир on 28.02.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


int kill_counter(int N, int k) {
    bool *alive_people = new bool[N];
    for (int i = 0; i < N; ++i) {
        alive_people[i] = true;
    }
    
    int killed = 0; int ch = 0; // счетчик от 1 до К
    while (N - killed > 1) {
        // check and kill ?
        if ( ch % k == 0) {
            if (alive_people[ch]) {
                alive_people[ch] = false;
                killed += 1;
                std::cout << ch + 1<< "\n";
            }
        }
        ch += k;
        if (ch >= N) ch -= N; // decrease 'ch'
    }
    // find alive one
    for (int l = 0; l < N; ++l) {
        if (alive_people[l]) {
            return l + 1;
        }
    }
    delete [] alive_people;
    return -1;
}


int main(int argc, const char * argv[]) {
    int N = 0; int k = 0;
    std::cin >> N >> k;
    
    int res = kill_counter(N, k);
    std::cout << "Alive: " << res;
    
    return 0;
}
