#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <thread>
#include <cassert>
#include "method3.h"

std::vector<int> moreMoreMore (const std::string& a, const std::string& b) {
    std::pair<std::vector<int>, std::vector<int>> woo;
    woo = toVecPlus(a, b, 's');
    int over1, over2 = 0; std::vector<int> out;
    std::reverse(woo.first.begin(), woo.first.end());
    std::reverse(woo.second.begin(), woo.second.end());
    for (int i = 0; i < woo.first.size() + woo.second.size(); i++) {
        out.push_back(0); 
    }
    if (woo.first.size() >= woo.second.size()) {
        for (int i = 0; i < woo.second.size(); i++) {
            for (int j = 0; j < woo.first.size(); j++) {
                over1 = woo.first[j] * woo.second[i] + over2;
                out[i+j] += over1 % 10; over2 = over1 / 10;  
            }
            if (over2 != 0) {
                out[i+woo.first.size()] += over2; over2 = 0;
            }
        }
    }
    else {
        swapPair(woo);
        for (int i = 0; i < woo.second.size(); i++) {
            for (int j = 0; j < woo.first.size(); j++) {
                over1 = woo.first[j] * woo.second[i] + over2;
                out[i+j] += over1 % 10; over2 = over1 / 10;  
            }
            if (over2 != 0) {
                out[i+woo.first.size()] += over2; over2 = 0;
            }
        }
    }
    for (int zz = 0 ; zz < out.size(); zz++) {
        if (out[zz] > 9) {
            out[zz+1] += out[zz] / 10;
            out[zz] = out[zz] % 10;
        }
    }
    if (out[out.size()-1] == 0) { out.pop_back(); }
    std::reverse(out.begin(), out.end());
    return out;
}


int breather (const std::string& a, const std::string& b, char z) {
    bool giga;
    if (z == '*') { std::vector<int> outr = moreMoreMore(a, b); for(int c : outr) { std::cout << c;};std::cout << std::endl; return 1;}
    if (a.length() > b.length()) {giga = true;} else { giga = false;}
    std::pair<std::vector<int>, std::vector<int>> wo; std::vector<int> outer;
    wo = toVecPlus(a, b, 'a'); int over = 0;
    for (int c : wo.first) { std::cout << c << " ";} for (int c : wo.second) { std::cout << c << " ";}
    std::cout << std::endl;
    if (z == '+') {
    for (int i = wo.first.size()-1; i >= 0; i--) {
        outer.push_back((wo.first[i] + wo.second[i] + over) % 10 );
        over = (wo.first[i] + wo.second[i] + over) / 10;
    }
    if (over != 0) { outer.push_back(over); }
    }
    if (z == '-') {
        int tempc;
        if (giga) {
            for (int i = wo.first.size()-1; i >= 0; i--) {
                tempc = wo.first[i] - wo.second[i] - over;
                over = 0;
                if (tempc < 0) { tempc += 10; over += 1; }
                outer.push_back(tempc);
            }
            
        } else {
            for (int i = wo.first.size()-1; i >= 0; i--) {
                tempc = wo.second[i] - wo.first[i] - over;
                over = 0;
                if (tempc < 0) { tempc += 10; over += 1; }
                outer.push_back(tempc);
            }
        }
    }
    std::reverse(outer.begin(), outer.end());
    for (int c : outer){ std::cout << c;}
    std::cout << std::endl;
    return(toInt(outer));

}

int main() {
    std::string a, b; char z;
    std::cin >> a >> z >> b;
    std::cout << a << " " << b << "\n";
    breather(a, b, z);

    return 0;
}

