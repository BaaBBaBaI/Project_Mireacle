#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <fstream>
// #include "BaBDataStack.h"
#include <vector>

std::vector<std::vector<int>> generateSpiralMatrix(int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    int num = 1;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;


    while (num <= n * n) {
        for (int i = left; i <= right; i++)
            matrix[top][i] = num++;
        top++;
        for (int i = top; i <= bottom; i++)
            matrix[i][right] = num++;
        right--;
        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                matrix[bottom][i] = num++;
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                matrix[i][left] = num++;
            left++;
        }
    }
    return matrix;
}

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

std::string noua(const std::string& dd) {
//useragreement
    char tempo; std::size_t it; char oo;
    std::string Upper = "useragmntUSERAGMNT"; std::string outp;
    for (int i = 0; i < dd.length(); i++) {
        tempo = dd[i];
        it = Upper.find(tempo);
        if (it != std::string::npos) {
        } else { outp += dd[i]; }
    }
    return outp;
}

std::string tolow(const std::string& dd) {
    char tempo; std::size_t it; char oo;
    std::string Upper = "QWERTYUIOPASDFGHJKLZXCVBNM"; std::string Lower = "qwertyuiopasdfghjklzxcvbnm"; std::string outp = dd;
    for (int i = 0; i < dd.length(); i++) {
        tempo = dd[i];
        it = Upper.find(tempo);
        if (it != std::string::npos) {
            outp[i] = Lower[it];
            oo = Lower[it];
        }
    }
    return outp;
}

void subway(int n, int start, int swic, int target, std::vector<std::string>& op) {
    if (n > 0) {
        subway(n - 1, start, target, swic, op);
        op.push_back("Ingredient " + std::to_string(n) + " move from " + std::to_string(start) + " to " + std::to_string(target));
        subway(n - 1, swic, start, target, op);
    }
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

void T13d2() {
    std::string o;
    std::getline(std::cin, o);
    std::cout << tolow(o);
}
void T13d1() {
    std::fstream inf ("input.txt");
    std::ofstream outf ("output.txt");
    if (inf.is_open()) {
        std::string line;
        while (std::getline(inf, line)) {
            outf << noua(line) << std::endl;
        }
        inf.close();
    }

}

void T13d1d2() {
    FILE *F;
    F=fopen("input.txt","r");
    char stroka[10001]; std::string stroka1; std::string otvet;
    fscanf(F,"%s\n",stroka);
    stroka1=stroka;
    otvet = noua(stroka1);
    fflush(F); fclose(F);
    FILE *r;
    r=fopen("output.txt","w");
    fprintf(r,"%s",otvet.c_str());
    fflush(r); fclose(r);

}

/* void T12d1() {
    BBStack h;
    int a; int temp;
    std::cin >> a;
    for (int i = 0; i < a; i++) {
        std::cin >> temp;
        h.push(temp);
    }
} */

void T11d3() {
    FILE *F; FILE *R;
    F = fopen("input.txt", "r");
    R = fopen("output.txt", "w");
    int a;
    fscanf(F,"%d\n",&a);
    std::vector<std::vector<int>> J;
    J = generateSpiralMatrix(a);

    for (std::vector<int> c : J) {
        for (int cc : c) {
            fprintf(R, "%d", cc);
        }
         fprintf(R, "%s", "\n");
    }
    fflush(F); fclose(F);
    fflush(R); fclose(R);
}

void T12d2s3() {
    FILE *F; FILE *R;
    F = fopen("input.txt", "r");
    R = fopen("output.txt", "w");
    int a; std::vector<std::string> sa;  
    fscanf(F, "%d\n", &a);
    subway(a, 1, 2 ,3, sa);
    for (std::string c : sa) {
        fprintf(R, "%s" ,c.c_str());
        fprintf(R, "%s" , "\n");
    }
    fflush(F); fclose(F);
    fflush(R); fclose(R);
        
}

int main() {

    T12d2s3();

    return 0;
} 