#include <iostream>
#include <cmath>
#include <vector>

std::pair<float,float> pipi(float a, float b, float c) {
    float ca = sqrt(pow(b, 2) - (4 * a * c));
    float ans1 = (-b + ca) / (2 * a);
    float ans2 = (-b - ca) / (2 * a);
    return std::make_pair(ans1, ans2);
}
int main() {
    float a, b, c; char as;
    std::cin >> a >> b >> c;
    std::cin >> as;
    switch (as)
    {
    case 'D':
        std::cout << "NAME: \nVenevtsev   Artem   Andreevych \nGROUP: \nEFBO-06-24 " << std::endl;
        break;
    case 'q': {
        std::pair<float, float> op = pipi(a, b, c);
        std::cout << "ANS: \n x1: " << op.first << "\t x2: " << op.second << std::endl;
        break;
    }
    case 'a':
        std::cin >> a >> b;
        std::cout << "ANS: \nS = " << a * b << std::endl;
        break;
    default:
        break;
    }

    return 0;
}