#include <vector>
#include <iostream>
#include <string>
#include <cmath>

int nod_recursive(int f_num, int s_num) {
    if (f_num == s_num) {
        return f_num;
    }
    if (f_num < s_num) {
        return nod_recursive((s_num - f_num), f_num);
    }
    if (f_num > s_num) {
        return nod_recursive(s_num, (f_num - s_num));
    }
} 

int main() {
    {
        std::cout << nod_recursive(128, 96);
    }
}