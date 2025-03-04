#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>

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

std::string popei(const std::string& a, const int& b) {
    std::string interchangable = "";
    std::string finish = a;
    for (int i = 0; i < b; i++) {
            char z = finish[0];
            int count = 1;
        for (int i = 1; i < finish.length(); i++) {
            if (finish[i] == z ) {
                count++;
            }
            else {
                interchangable = interchangable + std::to_string(count) + z;
                z = finish[i]; count = 1;
            }
        }
        interchangable = interchangable + std::to_string(count) + z;
        finish = interchangable; interchangable.clear();
    }
    return finish;

}

std::string aToBi(const std::string& a) {
    std::string interchangable = "0123456789";
    std::string finish, tempo = "", jkjk = "";
    char num;
    for (int i = 0; i < a.length(); i++) {
        if (interchangable.find(a[i]) != std::string::npos ) {
            tempo += a[i];
        }
        else {
            if (tempo != "") {
                int tt = std::stoi(tempo);
                while (tt > 0) {
                    jkjk += std::to_string(tt%2);
                    tt = tt/2;
                }
                std::string revjkjk(jkjk.rbegin(), jkjk.rend());
                finish += revjkjk;
                tempo = ""; jkjk = "";
                finish += a[i];
            } else {
                finish += a[i];
            }
        }
    }
    if (tempo != "") {
        int tt = std::stoi(tempo);
        while (tt > 0) {
            jkjk += std::to_string(tt%2);
            tt = tt/2;
        }
        std::string revjkjk(jkjk.rbegin(), jkjk.rend());
        finish += revjkjk; }
    return finish;
}

std::vector<float> noFriends(int a) {
    std::string familia[a], imya[a];
    float aa[a], ab[a], ac[a];
    float ares = 0, bres = 0, cres = 0;
    for (int i = 0 ; i < a; i ++) {
        std::cin >> familia[i] >> imya[i] >> aa[i] >> ab[i] >> ac[i];
    }
    for (int i = 0 ; i < a; i++) {
        ares += aa[i]; bres += ab[i]; cres += ac[i];
    }
    return {ares/a, bres/a ,cres/a};
}

void noFriendsAgain (int a) {
    std::map<std::pair<std::string,std::string>, float> pizo;
    std::multimap<float,std::pair<std::string,std::string>> piz;

    std::string s, b;
    float aa, bb, cc;
    for (int i = 0; i < a; i++) {
        std::cin >> s >> b >> aa >> bb >> cc;
        pizo[std::make_pair(s, b)] = (aa + bb + cc) / 3;
    }

    for ( const auto& pair : pizo) { 
        piz.insert({pair.second, pair.first});
    }

    for (auto it = piz.rbegin(); it != piz.rend(); ++it) {
        std::cout << it -> second.first << " " << it ->second.second << std::endl;
    }
    std::cout << std::endl;
}

int NeverEverBruh (const std::string& anal) {
    std::string b, c, d;
    b = {anal[0] , anal[1]};
    c = {anal[3] , anal[4]};
    d = {anal[6] , anal[7]};
    return std::stoi(d) * 360 + std::stoi(c) * 30 + std::stoi(b);

}

/* void NeverEverFriendsEver (int a) {
    std::multimap<std::string,std::multimap< std::string,std::string, DateComparator>> piz; std::multimap< std::string,std::string, DateComparator> pizo;
    std::string clas, name, surn, date; std::string fullname; int x, y, z, sumdate; std::pair<std::string, std::string> opop;
    for (int i = 0; i < a; i++) {
        std::cin >> surn >> name >> clas >> date;
        fullname = surn + " " + name; sumdate = NeverEverBruh(date);
        opop.first = date; opop.second = fullname;
        pizo.insert({date, fullname});
        piz.insert({clas, pizo});
        pizo.clear();       
    }
    for (const auto& pair : piz) {
        for (const auto& pairt : pair.second) {
            std::cout << pair.first << " " <<  pairt.first << " " << pairt.second << std::endl;
        }
    }


} */


void NeverEverFriendsEver(int a) {
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> piz;
    std::string clas, name, surn, date;
    std::string fullname;

    for (int i = 0; i < a; i++) {
        std::cin >> surn >> name >> clas >> date;
        fullname = surn + " " + name;
        piz[clas].push_back({date, fullname});
    }

    for (auto& [class_name, students] : piz) {
        std::sort(students.begin(), students.end(), 
            [](const auto& a, const auto& b) {
                return a.first < b.first;
            });
    }

    for (const auto& [class_name, students] : piz) {
        for (const auto& [date, fullname] : students) {
            std::cout << class_name << " " << fullname << " " << date << std::endl;
        }
    }
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

void T4d2() {
    int a, b;
    std::string prikoliks;
    std::cin >> prikoliks >> a;
    std::cout << popei(prikoliks, a-1) << std::endl;

}

void T4d3() {
    std::ifstream filein("input.txt");
    std::ofstream fileout("output.txt");
    std::string prikoliks;
    filein >> prikoliks;
    fileout << aToBi(prikoliks) << std::endl;
}

void T5d9() {
    int a;
    std::cin >> a;
    std::vector<float> b = noFriends(a);
    for (float c : b) {
        std::cout << std::fixed << std::setprecision(1) << c << " ";
    }
    std::cout << std::endl;
    
}

void T5d9two() {

    int a;
    std::cin >> a;
    noFriendsAgain(a);

}

void T5d9three() {

    int a;
    std::cin >> a;
    NeverEverFriendsEver(a);


}


int main() {

    T5d9three();

    return 0;
    
}