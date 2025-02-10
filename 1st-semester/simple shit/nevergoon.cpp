#include <iostream>
#include <vector>
#include <string>

int ouno (char z) {
            switch (z)
        {
        case 'I': { return 1; break; }
        case 'V': { return 5; break; }
        case 'X': { return 10; break; }
        case 'L': { return 50; break; }
        case 'C': { return 100; break; }
        case 'M': { return 500;break; }
        case 'D': { return 1000;break; }
        default: { return -1; }
        }
}

int goon (const std::string& never) {
    int i = 0; int gio = 0; 
    for (int i = 0 ; i < never.length(); i++ ) {
        if (ouno(never[i]) < ouno(never[i+1])) { gio += (ouno(never[i+1]) - ouno(never[i])); i++; } 
        else { gio += ouno(never[i]); }
    }
    return gio;

}



int main() {
    std::string J;
    std::cin >> J;
    int jojo = goon(J);
    std::cout << jojo;

}