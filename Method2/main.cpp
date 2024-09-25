#include <vector>
#include <iostream>
#include <string>

std::pair<int, int> maxmin(const std::vector<int>& a, std::string b) {
    int maxi = a[0];
    int mini = a[0];
    int index = 0;
    if (b == "min") {
        for (int i =0; i < a.size(); i++) {
            if (a[i] < mini) { mini = a[i]; index = i; }
        }
        return std::make_pair(mini, index);
    } if (b == "max") {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] > maxi) { maxi = a[i]; index = i; }
        }
        return std::make_pair(maxi, index);
    }
    else { return std::make_pair(0, 0); }

}

std::vector<int> reshala(std::vector<int> a) {
    while (a[0] != a[1] || a[1] != a[2] || a[2] != a[3]) {
        std::pair<int, int> info1, info2;
        info1 = maxmin(a, "max");
        info2 = maxmin(a, "min");
        a[info1.second] = info1.first - info2.first;
    }
    return a;
    
}
std::vector<std::string> reshi(int a) {
    std::vector<std::string> J;
    while (a > 1) {
        for (int i = 2; i <= a; i++) {
            if (a % i == 0) { 
                J.push_back("*" + std::to_string(i) );
                a = a / i;
                break;
            }
        }
    }
    return J;
}

int main1() {
    int f1, f2, f3, f4;
    std::cin >> f1 >> f2 >> f3 >> f4;
    std::vector<int> vect = {f1, f2, f3, f4};
    vect = reshala(vect);
    for (int c : vect) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    return 0;
}

int main() {
    std::vector<std::string> j;
    int a;
    std::cin >> a;
    j = reshi(a);
    for (std::string c : j) {
        std::cout << c << " ";
    }
    std::cout << std::endl;


    return 0;
}