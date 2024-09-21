#include <iostream>
#include <string>
#include <vector>
#include <utility>

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
            count++;
        }
    }
    return count;

}

std::vector<int> hui(std::vector<int> J) {
    std::vector<int> backy;
    for (int i = 0; i < J.size(); i++) {
        if (i == 0) { if (J[i] == J[i+1]) { } else { backy.push_back(J[i]); } }
        else if (i == J.size() - 1) { if (J[i] == J[i-1]) { } else { backy.push_back(J[i]); } }
        else { if (J[i] == J[i-1] || J[i] == J[i+1]) { } else { backy.push_back(J[i]); } }
    }
    return backy;
}

int kfc(int a) {
    int b;
    std::vector<int> ab, jb, jb1;
    for (int i = 0; i < a; i++) {
        std::cin >> b;
        ab.push_back(b);
    }
    jb1 = ab;
    jb = hui(jb1);
    while (jb != jb1)
    {
        jb1 = jb;
        jb = hui(jb);
    }
    return ab.size() - jb.size();
    


}

int rapu(int a) {
    std::vector<std::vector<int>> J(a, std::vector<int>(a));
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            if (i + j < a - 1) {
                J[i][j] = 0;
            }
            if (i + j == a - 1) {
                J[i][j] = 1;
            }
            if (i + j > a - 1) {
                J[i][j] = 2;
            }
        }
    }
    for (auto row : J ) {
        for (int elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    return 0;


}

bool strInStr(std::string a, std::string b) {
    if ( b.length() > a.length() ) {
        return false;
    }
    for (int i = 0; i <= a.length() - b.length(); i++) {

        if(a.substr(i, b.length()) == b) {  return true; }
    }
    return false;


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

void T3d2() {
    int a;
    std::cin >> a;
    rapu(a);

}

void T4d1() {
    std::string a, b;
    std::cin >> a >> b;
    if (strInStr(a, b)) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }

}

int main() {

    T4d1();

    return 0;
    
}