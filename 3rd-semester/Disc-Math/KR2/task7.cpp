#include <iostream>
#include <vector>

int main() {
    long long n;
    if (std::cin >> n && n > 1) {
        std::cout << n << " = ";
        
        bool first = true;
        
        while (n % 2 == 0) {
            if (!first) std::cout << " * ";
            std::cout << 2;
            n /= 2;
            first = false;
        }
        
        for (long long i = 3; i * i <= n; i += 2) {
            while (n % i == 0) {
                if (!first) std::cout << " * ";
                std::cout << i;
                n /= i;
                first = false;
            }
        }

        if (n > 2) {
            if (!first) std::cout << " * ";
            std::cout << n;
        }
        std::cout << std::endl;
    }
    return 0;
}
