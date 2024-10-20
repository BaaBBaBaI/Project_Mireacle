
#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"

#ifndef METHOD3_H
#define METHOD3_H

#include <iostream>

template<typename T1, typename T2>
void swapPair(std::pair<T1, T2>& p) {
    T1 temp = p.first;   // Store the first element in a temporary variable
    p.first = p.second;  // Assign the second element to the first
    p.second = temp;     // Assign the temporary variable to the second
}

#endif