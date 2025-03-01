
#include "node.hpp"
#include "tree.hpp"


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
    fillRandomWithPrikol(initial, 10); // random filling
    warnIfLooping(initial) ? std::cout << "Loop found!!\n" : std::cout << "No loop found!!\n"; // loop check
    std::cout << std::endl << "Unsorted:\n";
    printNode(initial);
    std::pair<Node ,Node> wow;
    int seppoint;
    std::cout << std::endl << "Separation point: ";
    std::cin >> seppoint;
    wow = splitBS(initial, seppoint); // split the Node
    std::cout << std::endl << "Sorted via separation point:\n";
    printNode(wow.first);
    printNode(wow.second);
    std::cout << std::endl;

}
void task3() { //also includes functions from task4

    Node initial; // initialization of node
    fillRandomWithPrikol(initial, 4, true); //4 nodes, loop
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

void task6() {
    tree* root = NULL; int fin;
    root = createFillTree(10); // Random filling (10 elements)
    std::cout << root << std::endl; // cout function for tree prints with levels of the tree
    std::cout << depth(root) << std::endl; // prints the depth of the tree
    std::cin >> fin; std::cout << std::endl; // input for the next task
    tree* newroot = find(root, fin); // finds a specific node in the tree
    std::cout << newroot; // cout function for tree
}

void task7() {
    book * root = NULL;
    root = insert(root, {"John", {"123", "456"}}); // insert a bunch of books new book
    root = insert(root, {"Alice", {"789", "012"}}); 
    root = insert(root, {"Bob", {"345", "678"}});
    root = insert(root, {"Charlie", {"901", "234"}});
    root = insert(root, {"David", {"567", "890"}});
    root = insert(root, {"Eve", {"321", "456"}});
    root = insert(root, {"John", {"345", "567"}});
    root = del(root, {"Charlie", {"234"}}); // delete function (charlies number)
    root = del(root, {"Bob",{}}); // delete function (Bob)
    book* findd = find(root, "Charlie"); // find function (charlie)
    std::cout << root << std::endl; // preorder
    std::cout << findd << std::endl;

    
}

void task8() {
    treesec* root = NULL;
    int min, max;
    std::cout << "\n\n\tinput numbers: ";
    std::cin >> min >> max;
    root = setTreeSec(root, min, max); // create an section tree
    std::cout << xcount(root, 3) << "\n"; // counts x within
    std::cout << root; // output (obhod dereva)
}

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
    case 6: {task6(); break;}
    case 7: {task7(); break;}
    case 8: {task8(); break;}
    default:
        break;
    }

    return 0;

}