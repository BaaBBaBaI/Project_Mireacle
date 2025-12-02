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
    int n;
    if (!(std::cin >> n) || n <= 0) return 0;

    long long current_gcd;
    std::cin >> current_gcd;

    for (int i = 1; i < n; ++i) {
        long long temp;
        std::cin >> temp;
        current_gcd = gcd(current_gcd, temp);
        
        if (current_gcd == 1) break; 
    }

    std::cout << current_gcd << std::endl;
    return 0;
}
