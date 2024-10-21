
#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define cpprint std::cout

#ifndef METHOD3_H
#define METHOD3_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


std::vector<int> toVector(std::string a) {
    std::vector<int> retVal;
    for (int i = 0; i < a.length(); i++ ) {
        retVal.push_back(a[i] - '0');
    }
    return retVal;
}


int toInt(const std::vector<int>& vec) {
    int result = 0;
    for (const auto& digit : vec) {
        result = result * 10 + digit;
    }
    return result;
}

int toInt(const std::string a) {
    return toInt(toVector(a));
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
    return std::pair<std::vector<int>, std::vector<int>> {-1, -1};
}


template<typename T1, typename T2>
std::pair<T2, T1> swapPair(std::pair<T1, T2>& p) {
    std::pair<T2, T1> smallPox(p.second, p.first);
    return smallPox;
}

#endif