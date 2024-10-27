#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <functional>

struct Datavector
{
    std::vector<int> Ya;
};


bool pushCommand(std::vector<int>& call, int tt) {
    std::cout << "ok" << std::endl;
    call.push_back(tt);
    return true;
}
bool sizeCommand(std::vector<int>& call, int tt) {
    std::cout << call.size() << std::endl;
    return true;
}
bool backCommand(std::vector<int>& call, int tt) {
    std::cout << call.back() << std::endl;
    return true;
}
bool popCommand(std::vector<int>& call, int tt) {
    std::cout << call.back() << std::endl;
    call.pop_back();
    return true;
}
bool clearCommand(std::vector<int>& call, int tt) {
    std::cout << "ok" << std::endl;
    call.clear();
    return true;
}
bool exitCommand(std::vector<int>& call, int tt) {
    std::cout << "bye" << std::endl;
    return false;
}

void stackr() {
    Datavector Datavector;
    std::unordered_map<std::string, std::function<bool(std::vector<int>&, int)>> commandMap = {
        {"push", pushCommand},
        {"size", sizeCommand},
        {"back", backCommand},
        {"pop", popCommand},
        {"clear", clearCommand},
        {"exit", exitCommand}

    };
    std::string temp; int tWork = 1;
    std::unordered_map<std::string, std::function<bool (std::vector<int>&, int)>>::iterator it;
    bool fili = true;
    while (fili == true) {
        std::cin >> temp;
        if (temp == "push") { std::cin >> tWork; }
        it = commandMap.find(temp);
        if (it != commandMap.end()) {
            fili = it->second(Datavector.Ya, tWork);
        } else {
            std::cout << "Command not recognized!" << std::endl;
        }
    }


}

int main() {

    stackr();
    return 0;
}


// https://site.ada.edu.az/~medv/acm/Docs%20e-olimp/Volume%2062/6122.htm temp delete soon.