#include <iostream>

long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0; 
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

int main() {
    long long a, b, n;

    if (std::cin >> a >> b >> n) {
        long long x, y;
        long long g = extended_gcd(b, n, x, y);

        if (g != 1) {
            std::cout << "ERROR_IMPOSSIBLE" << std::endl;
        } else {

            long long b_inv = (x % n + n) % n;
            
            long long result = ( (a % n) * b_inv ) % n;
            std::cout << result << std::endl;
        }
    }
    return 0;
}
