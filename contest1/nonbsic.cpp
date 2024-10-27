#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void fillArrayRandomly(double* arr, int size) {
    int* temp = new int[size];
    for (int i = 0; i < size; ++i) {
        temp[i] = i + 1;
    }

    std::srand(std::time(nullptr));
    for (int i = size - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(temp[i], temp[j]);
    }

    for (int i = 0; i < size; ++i) {
        arr[i] = static_cast<double>(temp[i]);
    }

    delete[] temp;
}

int myPow( const int& a, const int& b) {
    int res = 1;


}

long fastPow (float a, unsigned int b) {

    


}


/* include <cstdint>

uint64_t fast_exponentiation(uint64_t base, uint64_t exponent) {
    uint64_t result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        exponent >>= 1;
        base *= base;
    }
    return result;
} */

void T10d1() {
    double **p = NULL;
    int n;
    std::cin >> n;
    p = new double*;
    *p = new double;
    **p = n;
    std::cout << **p << std::endl;
    delete *p; delete p;
    p = NULL;
}

void T10d2() {
    int size; double *a = nullptr; int sum = 0;
    std::cin >> size;
    a = new double[size];
    fillArrayRandomly(a, size);
    for (int c = 0; c < size ; c++) {
        sum += a[c];
    }
    std::cout << sum;
    delete[] a;

}

void T10d3() {
    int a, b;

    std::cin >> a >> b;
    std::cout << myPow(a, b);

}

void T11d1() {
    float a; unsigned int b;

    std::cin >> a >> b;
    std::cout << fastPow(a, b);
}

int main() {

    T10d2();

    return 0;
} 