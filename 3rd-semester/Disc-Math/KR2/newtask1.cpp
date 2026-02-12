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

int main() {
    
}