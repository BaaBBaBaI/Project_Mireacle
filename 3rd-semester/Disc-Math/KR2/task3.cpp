#include <iostream>

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
    long long a, b;
    if (std::cin >> a >> b) {

        std::cout << lcm(a, b) << std::endl;
        
    }
    return 0;
}
