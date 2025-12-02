#include <iostream>


long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) { 
            result = (result * base) % mod;
        }
        base = (base * base) % mod; 
        exp /= 2;
    }
    return result;
}

int main() {
    
    long long e = 5;
    long long n = 119;
    
    long long m; 
    std::cout << "Enter message m int: ";
    
    if (std::cin >> m) {
        
        if (m >= n) {
            std::cout << "ERROR message must be smaller: (" << n << ")" << std::endl;
        } else {
            long long c = modExp(m, e, n);
            std::cout << "ENCRYPTED C: " << c << std::endl;
        }
    }
    return 0;
}
