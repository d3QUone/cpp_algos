//
//  main.cpp
//  zadacha_2-4
//
//  Created by Владимир on 28.02.15.
//  Copyright (c) 2015 Kasatkin. All rights reserved.
//

#include <iostream>


int solver(int N, int k) {
    bool *alive_people = new bool[N];
    for (int i = 0; i < N; ++i) {
        alive_people[i] = true;
    }
    int pos = 0; // absolute position
    int sch = 0; // counter from 1 to k
    int killed = 0;
    while (true) {
        if (alive_people[pos]) {
            sch += 1;
        }
        if (sch%k == 0) {
            if (alive_people[pos]) {
                alive_people[pos] = false; // 'kill'
                sch = 0; // new loop
                killed += 1;
                //std::cout << pos + 1 << "; killed " << killed << " total\n";
            }
        }
        pos += 1;
        
        if (pos >= N) pos -= N; // go to the beginnig (like a circle)
        if (N - killed == 1) {
            // one is alive, find him and return
            for (int l = 0; l < N; ++l) {
                if (alive_people[l]) {
                    delete [] alive_people;
                    return l + 1;
                }
            }
        }
    }
    delete [] alive_people;
    return -1; // if nothing found
}


int main(int argc, const char * argv[]) {
    int N = 0; int k = 0;
    std::cin >> N >> k;
    
    int res = solver(N, k);
    //std::cout << "\nAlive: " << res; // debug
    std::cout << res; // release
    return 0;
}
