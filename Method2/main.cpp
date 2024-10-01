#include <vector>
#include <iostream>
#include <string>
#include <cmath>

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

std::pair<int, int> ferm(int number) {
    if (number - 2 % 4 == 0) { return std::make_pair(1, number);}  
    int koren=sqrt(number); int x=1; int q=0; int delit1,delit2; int koren_iz_q=0;
    while(true){
        q=(koren+x)*(koren+x)-number;
        koren_iz_q=sqrt(q);
        if (koren_iz_q*koren_iz_q==q){ break; } else{ x++; }
    }
    delit1=(koren+x)-koren_iz_q;
    delit2=(koren+x)+koren_iz_q;
    return std::make_pair(delit1, delit2);
}


std::vector<int> fermresh(int a) {
    std::pair<int, int> k;
    std::vector<int> Z, V;
    Z.push_back(a);
    bool flag = true;
    while (flag == true) {
        V.clear();
        for (int i = 0; i < Z.size(); i++) { k = ferm(Z[i]); V.push_back(k.first); V.push_back(k.second);}
        Z.clear();
        for (int i = 0; i < V.size(); i++) { if (V[i] != 1) {Z.push_back(V[i]);}}
        if (V.size() - Z.size() == Z.size()) { flag = false; }
    }
    return Z;

}

int poslm(int j) {
    int curr = 4;

    return curr;
}

bool mersenmersen(int a) {
    if (a == 1) { return true;}
    int curr = 4;
    int f = pow(2, a) - 1;
    for (int k = 1; k != a - 1; k++) {
        curr = pow(curr, 2) - 2;
        curr = curr % f;
    }
    if (curr == 0) {
        return true;
    }
    return false;

}

long long noom(long long a) {
    a = pow(a, 2);
    std::string z = std::to_string(a);
    long long start = (z.length()-5) / 2;
    long long end = start + 5;
    std::string bb;
    for (int i = start; i < end; i++) {
        bb += z[i];
    }
    return std::stoi(bb);

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

int main2() {
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

int main3() {
    int a;
    std::cin >> a;
    std::vector<int> L;
    L = fermresh(a);
    for (int c : L) {
        std::cout << c << " ";
    }
    std::cout << std::endl;


    return 0;
    
}

int main4() {
    int a;
    std::cin >> a;
    if (mersenmersen(a) == true) {
        std::cout << "Prime" << std::endl;
    } else { std::cout << "Composite" << std::endl; }

    return 0;

}

int main5() {
    long long a;
    std::cin >> a;
    for (int j = 0; j < 10; j++) {
        a = noom(a);
        std::cout << a << std::endl;
    }
    return 0;

}

int main() {
    main4();
    return 0;
}