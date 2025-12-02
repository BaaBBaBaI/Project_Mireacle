#include <iostream>
#include <vector>

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    long long abs_a = (a < 0) ? -a : a;
    long long abs_b = (b < 0) ? -b : b;
    return (abs_a / gcd(abs_a, abs_b)) * abs_b;
}

int main() {
    int n;
   
    if (std::cin >> n && n > 0) {
        long long current_lcm;
        std::cin >> current_lcm; 

        for (int i = 1; i < n; ++i) {
            long long next_val;
            std::cin >> next_val;
            current_lcm = lcm(current_lcm, next_val);
        }
        std::cout << "LCM: " << current_lcm << std::endl;
    }
    return 0;
}
