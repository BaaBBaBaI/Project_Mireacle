#include <iostream>
#include <string>
#include <vector>


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

int kulak(const int a) {
    int b, count = 0;
    std::vector<int> ab;
    for (int i = 0; i < a; i++) {
        std::cin >> b;
        ab.push_back(b);
    }
    if (ab.size() < 2) { return ab.size(); }
    if (ab[0] > ab[1]) {count++; /* std::cout << "Condition met on line: " << __LINE__ << " " << __FILE__ << ab[0] << " " << ab[1] << std::endl; */}
    if (ab[a-1] > ab[a-2]) {count++; /* std::cout << "Condition met on line: " << __LINE__ << " " << __FILE__ << ab[a-1] << " " << ab[a-2] << std::endl; */}
    for (int i = 1; i < a - 1; i++) {
        if (ab[i] > ab[i-1] && ab[i] > ab[i+1]) {
            // std::cout << "Condition met on line: " << __LINE__ << " " << __FILE__ << ab[i+1] << " " << ab[i-1] << " " << ab[i] << std::endl;
            count++;
        }
    }
    return count;

}

int kfc(int a) {
    int b, count = 0;
    std::vector<int> ab;
    for (int i = 0; i < a; i++) {
        std::cin >> b;
        ab.push_back(b);
    }
    ab.push_back(100);
    if (ab.size() < 2) { return 0; }
    while (ab.size() >= 2 ) {
        if ((ab.size() == 2) && (ab[0] == ab[1])) {return count + 2;} else if (ab.size() == 2) { return count;}
        bool flag = true;
        for (int i = 0; i < ab.size() - 1; i++) {
            if (ab[i] == ab[i+1]) {
                if (ab[i+2] == 100) {
                } else if (ab[i+1] == ab[i+2]) {
                    ab.erase(ab.begin() + i); ab.erase(ab.begin() + i); ab.erase(ab.begin() + i);
                    count = count + 3;
                    flag = false;
                }
                std::cout << "Condition met on line: " << __LINE__ << " " << __FILE__ << ab.size() << " " << ab[i+1] << " " << ab[i-1] << " " << ab[i] << std::endl;
                ab.erase(ab.begin() + i); ab.erase(ab.begin() + i);
                count = count + 2;
                flag = false;
                /* for (int g : ab) { std::cout << g << " ";} */

            }
        }
        if (flag) { return count; }
    }
    return count;
}


void T13d3() {
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

}


void T2d3() {
    int a;
    std::cin >> a;
    std::cout  << kulak(a) << std::endl;
}

/* Группа студентов, состоящая из N человек решает, после какой пары они хотели бы пойти в КФС. Если студенты, желающие уйти с одной и той же пары, стоят рядом, то они уходят, а остальные продвигаются друг к другу.

Например, 1 2 3 3 2 1 сначала превратится в последовательность 1 2 2 1, потом в 1 1, а потом не останется никого.

Спрашивается: сколько студентов всего найдут себе компанию и дойдут до КФС?

Например, для приведённой последовательности ответом будет число 6. */

void T3d1() {
    int a;
    std::cin >> a;
    std::cout << kfc(a) << std::endl;

}

int main() {

    T3d1();

    return 0;
    
}