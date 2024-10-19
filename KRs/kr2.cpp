// Venevtsev Artem EFBO-06-24
#include <iostream>
#include <vector>

std::vector<int> noNegativity (std::vector<int> Pe) {
    /* No negativity guys. Think about all the positive things! */
    std::vector<int> out;
    for (int i = 0 ; i < Pe.size() ; i++) {
        if (Pe[i] >= 0) {
            out.push_back(Pe[i]);
        }
    }
    return out;

}


int main () {
    int a, temp; std::vector<int> J;
    std::cin >> a;
    for (int i = 0; i < a; i++) {
        std::cin >> temp;
        J.push_back(temp);
    }
    
    J = noNegativity(J);
    std::cout << "No negativity guys. ♥😘♥😘♥\n ";

    for (int c : J) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}