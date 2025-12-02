#include <iostream>

int main() {
    long long m = 6075;
    long long a = 106;
    long long c = 1283;
    long long x = 0; 

    std::cout << "Enter x0: ";
    if (std::cin >> x) {
        for (int i = 0; i < 3; ++i) {
            x = (a * x + c) % m;
            std::cout << "x" << (i + 1) << " = " << x << std::endl;
        }
    }
    return 0;
}
