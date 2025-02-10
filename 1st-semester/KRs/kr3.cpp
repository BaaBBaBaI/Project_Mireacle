#include <iostream>
#include <vector>
#include <fstream>

void main1() {
    std::ifstream file("input.txt");
    std::ofstream outer("output.txt");
    std::string name, surname; int b;
    while (file >> name >> surname >> b) {
        if (b == 5) {
            outer << name << " " << surname << " " << b << std::endl;
        }
    }
    file.close(); outer.close();
}

void main2() {
    std::ifstream file("input.txt");
    std::string stroka;
    while(std::getline(file, stroka)) {
        for (char &temp : stroka) {
            if (temp == ' ') {
                temp = '_';
            }
        }
        std::cout << stroka << std::endl;
    }
    file.close();
    
}

int main() {
    short a;
    std::cout << "Write a task number ( i did num 2 and 3) " << std::endl;
    std::cin >> a;
    switch (a)
    {
    case 2: {
        main1();
        break;
    }
    case 3: {
        main2();
        break;
    }
    default:
        break;
    }
    return 0;
}