#include <iostream>

void simplecalc(float a, float b, char d) {
    switch (d)
    {
    case '+' :
        std::cout << (a + b);
        // return (a + b);
        break;

    case '-' :
        std::cout << (a - b);
        break;

    case '/' :
        std::cout << (a / b);
        break;
    
    case '*' : 
        std::cout << (a * b);
    
    default:
        break;
    }


}

int platiti(float a, float b) {
    int time;
    for (time = 1; a < b; time++) { a = a * 1.1; }
    return time;

}

void tatyana(int a, int b) { // ISNT FINISHED
    do {
        switch (a % 2) {
        case 0:
            std::cout << ":2" << std::endl;
            a = a / 2;
            break;
        case 1:
            std::cout << "-1" << std::endl;
        
        default:
            break;
        }

    } while (true);

}

int main() {
    float a, b;
    int nd, st;
    char d;
    std::cin >> a >> b;
    // simplecalc(a, b, d);
    int c = platiti(a, b);
    std::cout << c;
    return 0;
}