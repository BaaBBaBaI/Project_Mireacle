#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

int toInt(const std::vector<int>& vec) {
    int result = 0;
    for (const auto& digit : vec) {
        result = result * 10 + digit;
    }
    return result;
}

std::vector<int> toVector(int a) {
    std::vector<int> retVal;
    if (a == 0) {
        retVal.push_back(0);
    } else {
        while (a > 0) {
            retVal.push_back(a % 10);
            a /= 10;
        }
        std::reverse(retVal.begin(), retVal.end());
    }
    return retVal;
}
std::pair<std::vector<int>, std::vector<int>> toVecPlus(int aint, int bint) {
    std::vector<int> a = toVector(aint); std::vector<int> b = toVector(bint);
    while (a.size() != b.size()) {
        if (a.size() > b.size()) { b.insert(b.begin(), 0); }
        if (a.size() < b.size()) { a.insert(b.begin(), 0); }
    } return std::make_pair(a, b);
}

int breather (const int& a, const int& b, char z) {
    bool giga;
    if (a > b) {giga = true;} else { giga = false;}
    std::pair<std::vector<int>, std::vector<int>> wo; std::vector<int> outer;
    wo = toVecPlus(a, b); int over = 0;
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
     for (int c : outer) { std::cout << c << " ";}
    std::cout << std::endl;
    return(toInt(outer));

}


int main() {
    int a, b; char z;
    std::cin >> a >> z >> b;
    std::cout << breather(a, b, z) << std::endl;

    return 0;
}