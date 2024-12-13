#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>


float f(float x) {  
    float formula = 0.25 *pow( x, 3) + x - 2;
    return formula;
}

std::pair<float, float> nonChordMethod(float ast, float bnd, float fast, float fbnd) {
    float xc = (ast + bnd) / 2;
    float fxc = f(xc);
    if (0.0000001 < std::abs((bnd - ast) / 2)) {
        if (fxc * fast > 0) {
            return nonChordMethod(xc, bnd, fxc, fbnd);
        } else {
            return nonChordMethod(ast, xc, fast, fxc);
        }
    }
    return {xc, fxc};
}


int nod_recursive(int f_num, int s_num) {
    if (f_num == s_num) {
        return f_num;
    }
    if (f_num < s_num) {
        return nod_recursive((s_num - f_num), f_num);
    }
    if (f_num > s_num) {
        return nod_recursive(s_num, (f_num - s_num));
    }
    return -1;
} 

std::unordered_map<short, std::vector<int>> mapMergeTools (std::vector<int> io) {
    short temp; std::unordered_map<short, std::vector<int>> outp;
    for (int c : io) {
        temp = c % 7;
        outp[temp].push_back(c);
    }
    return outp;  
}

std::unordered_map<char, int> mapMergeTools (std::string& J) {
    std::unordered_map<char, int> po;
    for (char c : J) {
        po[c]++;
    }
    return po;  
}

int DoIt(int a) {
    if (a == 1) {
        return 1;
    }
    if (a == 0) {
        return 0;
    }
    return (DoIt(a - 1) + DoIt(a - 2));
}


int main1() {
    std::cout << nod_recursive(128, 96);
    return 1;
}

int main2() {
    std::cout << "Tell me your respected number, you bitch!";
    std::cout << std::endl;
    int a;
    std::cin >> a;
    std::cout << DoIt(a) << std::endl;
    return 1;
}


int main3() {
    float ast = 0; float bnd = 2;
    std::pair<float, float> opa;
    float fast = f(ast); float fbnd = f(bnd);

    opa = nonChordMethod(ast, bnd, fast, fbnd);
    std::cout << "Non chord method answer: " << opa.first << " " << opa.second << std::endl;

    return 1;
}

int main4() {
    std::unordered_map<short, std::vector<int>> op;
    int a; std::vector<int> oo;
    for (int i = 0; i < 6; i++) {
        std::cin >> a; std::cout << "\n";
        oo.push_back(a);
    }
    op = mapMergeTools(oo);
    for (const auto iter : op) {
        for (int cc: iter.second) {
            std::cout << iter.first << " = " << cc << std::endl;
        }
    }

    return 1;
}

int main5() {
    std::unordered_map<char, int> op;
    int a; std::string oo;
    getline(std::cin, oo);
    op = mapMergeTools(oo);
    for (const auto iter : op) {
        std::cout << iter.first << " used " << iter.second << " times. " << std::endl;
    }

    return 1;
}

int main() {
    main5();
    return 0;
}