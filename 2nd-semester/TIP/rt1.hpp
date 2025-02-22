
#ifndef TIPRT1
#define TIPRT1 

#include <cmath>
#include <iostream>

class triangle
{
private:
    double a, b, c;
public:
    triangle(double a1, double a2, double a3);
    bool exst_tr();
    void set(double a1, double b1, double c1);
    void show();
    double perimeter();
    double square();
    ~triangle();
};

triangle::triangle(double a1, double a2, double a3) { a = a1; b = a2; c = a3; }

bool triangle::exst_tr() { if (a + b > c && a + c > b && b + c > a) { return true; } else { return false; } }

void triangle::set(double a1, double b1, double c1) { a = a1; b = b1; c = c1; }

void triangle::show() { std::cout << "a = " << a << std::endl; std::cout << "b = " << b << std::endl; std::cout << "c = " << c << std::endl; }

double triangle::perimeter() { return a + b + c; }

double triangle::square() { double cc = (a + b + c) / 2; return sqrt(cc * (cc - a) * (cc - b) * (cc - c)); }

triangle::~triangle() {}

#endif