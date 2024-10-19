#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <thread>
#include <cassert>
#include "color.h"

int toInt(const std::vector<int>& vec) {
    int result = 0;
    for (const auto& digit : vec) {
        result = result * 10 + digit;
    }
    return result;
}

std::vector<int> toVector(std::string a) {
    std::vector<int> retVal;
    for (int i = 0; i < a.length(); i++ ) {
        retVal.push_back(a[i] - '0');
    }
    return retVal;
}
std::pair<std::vector<int>, std::vector<int>> toVecPlus(std::string aint, std::string bint, char o) {
    /* 's' for standart vectorization of 2 strings, 'a' for advanced */
    switch (o)
    {
    case 's': {
        return std::make_pair( toVector(aint), toVector(bint));
        break;
    }
    case 'a': {
        std::vector<int> a = toVector(aint); std::vector<int> b = toVector(bint);
        while (a.size() != b.size()) {
            if (a.size() > b.size()) { b.insert(b.begin(), 0); }
            if (a.size() < b.size()) { a.insert(b.begin(), 0); }
        } return std::make_pair(a, b);
        break;
    }
    default:
        std::cout << YELLOW << "Warning: wrong char provided. Use 's' for standart vectorization of 2 strings, 'a' for advanced.\n "  << RESET;
        break;
    }
    

}


std::vector<int> moreMoreMore (const std::string& a, const std::string& b) {
    bool giga;
    std::pair<std::vector<int>, std::vector<int>> woo; int over1, over2 = 0; std::vector<int> out;
    std::reverse(woo.first.begin(), woo.first.end());
    std::reverse(woo.second.begin(), woo.second.end());
    std::vector<std::vector<int>> J;
    woo = toVecPlus(a, b, 's');
    if (woo.first.size() >= woo.second.size()) {
        J[woo.second.size()];
        for (int i = 0; i < woo.second.size(); i++) {
            for (int zz = 0; zz < i; zz++) { J[i].push_back(0); }
            for (int j = 0; j < woo.first.size(); j++) {
                over1 = woo.first[j] * woo.second[i] + over2;
                J[i].push_back(over1 % 10); over2 = over1 / 10;
            }
            if (over2 != 0) { J[i].push_back(over2); }   
        } 
    } else {
        J[woo.first.size()];
        for (int i = 0; i < woo.first.size(); i++) {
            for (int zz = 0; zz < i; zz++) { J[i].push_back(0); }
            for (int j = 0; j < woo.second.size(); j++) {
                over1 = woo.first[j] * woo.second[i] + over2;
                J[i].push_back(over1 % 10); over2 = over1 / 10;
            }
            if (over2 != 0) { J[i].push_back(over2); }   
        } 
    }
    
    
    
    
}

int breather (const std::string& a, const std::string& b, char z) {
    bool giga;
    if (z == '*') { std::vector<int> outr = moreMoreMore(a, b);for(int c : outr) { std::cout << c;};std::cout << std::endl; }
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
    system("clear");
    for (int c : outer) { std::cout << c;}
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