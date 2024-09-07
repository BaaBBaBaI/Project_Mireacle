#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <fstream>


float f(float x) {
    float formula = pow(0.25 * x, 3) + x - 2;
    return formula;
}

std::pair<int, float> chordMethod(float ast, float bnd) {
    std::ofstream MyFile("info.txt");
    int time = 0;
    float xc;
    while (bnd - ast > 0.0001) {
        xc = ast - f(ast) * ((bnd - ast) / (f(bnd) - f(ast)));
        MyFile << xc << "\n";
        if (pow(xc, 2) > bnd) { bnd = xc; }
        else { ast = xc; }
        time++;
        MyFile << time << " " << ast << " " << bnd << " " << xc << std::endl;
    }
    return std::make_pair(time, xc);
}

int main() {

    double ast = 0; double bnd = 20;
    std::pair<int, double> chan;
    
    chan = chordMethod(ast, bnd);

    std::cout << "answer: " << chan.first << " " << chan.second;

    return 0;
}


std::pair<int, float> nonChordMethod(float ast, float bnd) {
    std::ofstream MyFile("info_non_chord.txt");
    int time = 0;
    float xc = 1;
while (fabs((bnd - ast)/xc) > 0.0001) {
    xc = (ast + bnd)/2;
    if (f(xc) * f(ast) > 0) {
        ast = xc;
        f(ast);
    }






}


}
