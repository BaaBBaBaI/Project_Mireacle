#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <functional>
#include "BaBDataStack.h"


bool pushCommand(BBStack& call, int tt) {
    std::cout << "ok" << std::endl;
    call.push(tt);
    return true;
}
bool sizeCommand(BBStack& call, int tt) {
    std::cout << call.size() << std::endl;
    return true;
}
bool backCommand(BBStack& call, int tt) {
    std::cout << call.back() << std::endl;
    return true;
}
bool popCommand( BBStack& call, int tt) {
    std::cout << call.back() << std::endl;
    call.pop();
    return true;
}
bool clearCommand(BBStack& call, int tt) {
    std::cout << "ok" << std::endl;
    call.clear();
    return true;
}
bool exitCommand(BBStack& call, int tt) {
    std::cout << "bye" << std::endl;
    return false;
}

void stackr() {
    std::unordered_map<std::string, std::function<bool(BBStack&,  int)>> commandMap = {
        {"push", pushCommand},
        {"size", sizeCommand},
        {"back", backCommand},
        {"pop", popCommand},
        {"clear", clearCommand},
        {"exit", exitCommand}

    };
    BBStack steck;
    std::string temp; int tWork = 1;
    std::unordered_map<std::string, std::function<bool (BBStack&,  int)>>::iterator it;
    bool fili = true;
    while (fili == true) {
        std::cin >> temp;
        if (temp == "push") { std::cin >> tWork; }
        it = commandMap.find(temp);
        if (it != commandMap.end()) {
            fili = it->second(steck, tWork);
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