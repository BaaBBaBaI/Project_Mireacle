#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

std::unordered_map<char, int> mapMergeTools (std::string& J) {
    std::unordered_map<char, int> po;
    for (char c : J) {
        po[c]++;
    }
    return po;  
}

int main() {
    std::unordered_map<char, int> op;
    int a; std::string oo;
    getline(std::cin, oo);
    op = mapMergeTools(oo);
    for (const auto iter : op) {
        std::cout << iter.first << " used " << iter.second << " times. " << std::endl;
    }

    return 0;
}