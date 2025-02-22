
#include "node.hpp"


void task1() {

    Node initial; Node initialloop;
    fillRandomWithPrikol(initial, 10); /* Here you can add true statement (initial, number, bool) to make it loop */
    fillRandomWithPrikol(initialloop, 10, true);
    std::cout << "\tWith no loop:  "; printNode(initial);
    warnIfLooping(initial) ? std::cout << "\tLoop found!!\n" : std::cout << "\tNo loop found!!\n";
    std::cout << std::endl;
    std::cout << "\tWith loop:  "; printNode(initialloop);
    warnIfLooping(initialloop) ? std::cout << "\tLoop found!!\n" : std::cout << "\tNo loop found!!\n";
    return;

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
void task3() { //also includes functions from task4

    Node initial;
    fillRandomWithPrikol(initial, 4, true);
    warnIfLooping(initial) ? std::cout << "Loop found!!\n" : std::cout << "No loop found!!\n"; // check if there is a loop
    printNode(initial);// prints the linkedlist
    std::cout << "\n\tSize of Node: { " << sizeNode(initial) << " }" << std::endl; // returns size of said Node
    nodeAppend(initial, 10); // Adds to the end of linkedlist (task3&4)
    nodeInsert(initial, 10, 5); // adds to the middle of linkedlist (task4)
    printNode(initial); // prints the linkedlist
    nodeDel(initial, 5); // delete a specific node on
    printNode(initial, "reverse"); // prints the linkedlist in reverse (task4)
    
}

void task5() {}

void task0() { //emty func


    return;
}


int main() {
    int tasks;
    std::cout << "\t which task? number: "; std::cin >> tasks; std::cout << std::endl;
    switch (tasks)
    {
    case 0: {task0(); break;}
    case 1: {task1(); break;}
    case 2: {task2(); break;}
    case 3: {task3(); break;}
    case 4: {task3(); break;}
    default:
        break;
    }

    return 0;

}