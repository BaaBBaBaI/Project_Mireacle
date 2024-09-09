#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <fstream>


float f(float x) {  
    float formula = 0.25 *pow( x, 3) + x - 2;
    return formula;
}

std::pair<int, float> chordMethod(float ast, float bnd) {
    // std::ofstream MyFile("info.txt");x
    static int time = 0;
    float xc = 10000;
    gay:
        xc = ast - (f(ast) * (bnd - ast) / (f(bnd) - f(ast)));
            // MyFile << xc << "\n";
        if (f(ast) * f(xc) > 0) {ast = xc;} else {bnd = xc;}
        time++;
        // MyFile << time << " " << ast << " " << bnd << " " << xc << std::endl;
    if ((std::abs(bnd - ast) / xc) > 0.0001) { goto gay; }
    return std::make_pair(time, xc);
}


std::pair<float, float> nonChordMethod(float ast, float bnd) {
    float xc = 0, fxc = 0;
    float fast = f(ast); float fbnd = f(bnd);
    do {
        xc = (ast + bnd) / 2;
        fxc = f(xc);
        if (fxc * fast > 0) { ast = xc; fast = fxc; } else { bnd = xc; fbnd = fxc; }
    } while (0.0000001 < std::abs((bnd - ast) / 2));
    return std::make_pair(xc, fxc);
}


int main() {

    float ast = 0; float bnd = 2;
    std::pair<int, float> chan;
    std::pair<float, float> opa;
    
    chan = chordMethod(ast, bnd);
    opa = nonChordMethod(ast, bnd);

    std::cout << "Non chord method answer: " << opa.first << " " << opa.second << std::endl;
    std::cout << "Chord method answer: " << chan.first << " " << chan.second << std::endl;

    return 0;
}