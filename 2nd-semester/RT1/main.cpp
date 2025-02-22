
#include "node.hpp"


void task3() {

    Node initial;
    fillRandomWithPrikol(initial, 4, true);
    warnIfLooping(initial) ? std::cout << "Loop found!!\n" : std::cout << "No loop found!!\n";
    printNode(initial);
    std::cout << "SENOM VEX\n";
    nodeAppend(initial, 10);
    nodeInsert(initial, 10, 5);
    printNode(initial);
    nodeDel(initial, 5);
    printNode(initial, "reverse");
    
}

void task2() {

    Node initial;
    fillRandomWithPrikol(initial, 10);
    warnIfLooping(initial) ? std::cout << "Loop found!!\n" : std::cout << "No loop found!!\n";
    std::cout << std::endl << "Unsorted:\n";
    printNode(initial);
    std::pair<Node ,Node> wow;
    int seppoint;
    std::cout << std::endl << "Separation point: ";
    std::cin >> seppoint;
    wow = splitBS(initial, seppoint);
    std::cout << std::endl << "Sorted via separation point:\n";
    printNode(wow.first);
    printNode(wow.second);
    std::cout << std::endl;

}

int main() {

    task3();


    return 0;

}

