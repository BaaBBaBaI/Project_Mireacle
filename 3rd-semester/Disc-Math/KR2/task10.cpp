#include <iostream>

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long d = 77;
    long long n = 119;
    
    long long c;
    std::cout << "ENTER C (Cipher): ";
    
    if (std::cin >> c) {
        long long m = modExp(c, d, n);
        std::cout << "DECRYPTED M: " << m << std::endl;
    }
    return 0;
}
