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

int main() {

    T10d2();

    return 0;
} 