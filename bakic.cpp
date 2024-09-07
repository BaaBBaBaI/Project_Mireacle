#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <iomanip>

int vtzad(int v, int t) {
    int l = 109;
    int s = v * t;
    int a = s % 109;
    return a;
}

float pzad() {
    int a = 10, b = 10;
    float c = sqrt(pow(a, 2) + pow(b, 2));


    return c;
}

std::pair<int, std::pair<int, int>> chtoeto(int sec) {
    int min, hrs;
    hrs = floor((sec / 3600) % 24);
    sec = sec - hrs * 3600;
    min = floor(sec / 60);
    sec = sec - min * 60;
    
    return std::make_pair(hrs, std::make_pair(min, sec));

}


int main() {
    int a, b, c;
    std::pair<int, std::pair<int, int>> pizd;
    a = 55472;
    // int d = vtzad(a, b);
    // std::cout << d << "\n";
    pizd = chtoeto(a);
    std::cout << pizd.first << " : " << std::setw(2) << std::setfill('0') << pizd.second.first << " : " << std::setw(2) << std::setfill('0') << pizd.second.second << "\n";
    return 0;
}



