#include <iostream>
#include <string>


bool strnum(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}


float simplecalc(float a, float b, char d) {
    switch (d)
    {
    case '+':
        return (a + b);
        break;

    case '-' :
        return (a - b);
        break;

    case '/' :
        return (a / b);
        break;
    
    case '*' : 
        return (a * b);
        break;
    
    default:
        return 0;
        break;
    }


}

float simplecalc(float a, float b) { return (a * b); }

int platiti(float a, float b) {
    int time;
    for (time = 1; a < b; time++) { a = a * 1.1; }
    return time;

}

void tatyana(int a, int b) { // IS FINISHED
    do {
        switch (a % 2) {
        case 0:
            std::cout << ":2" << std::endl;
            a = a / 2;
            break;
        case 1:
            std::cout << "-1" << std::endl;
            a = a - 1;
            break;
        
        default:
            break;
        }

    } while ((a / 2) > b);
    while (a > b) { a--; std::cout << "-1" << std::endl;}

}

int main() {
    float a, b, ans = 10;
    int nd, st;
    std::string d;
    std::cin >> a >> d;
    if (!strnum(d)) { std::cin >> b; ans = simplecalc(a, b, d[0]);}
    else { ans = simplecalc(a, std::stoi(d)); }
    std::cout << ans << std::endl;
    // int c = platiti(a, b);
    // std::cout << c;
    // tatyana(a, b);
    return 0;
}