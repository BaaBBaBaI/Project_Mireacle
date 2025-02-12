#include <iostream>
#include <string>

struct Node /* node itself */
{
    int data;
    Node* next;
    Node* prev;

};

void printNode(Node work) { /* Prints da note! */

    Node* printed = &work;
    Node* noloop = printed;

    if (printed->next == nullptr) {
        std::cout << std::endl << "\tNode: [ nothing ]\n\n";
        return;
    }

    std::cout << std::endl << "\tNode: [";
    do {
        std::cout << " " << printed->data << " ";
        printed = printed->next;
    } while (printed != nullptr && printed->next != noloop->next);
    std::cout << "]" << std::endl;

}

void printNode(Node* work) { /* Prints da note! Unefficient But you know it works and I'm I'm not gonna change every single line of code*/

    Node* printed = work;
    Node* noloop = printed;

    if (printed->next == nullptr) {
        std::cout << std::endl << "\tNode: [ nothing ]\n\n";
        return;
    }

    std::cout << std::endl << "\tNode: [";
    do {
        std::cout << " " << printed->data << " ";
        printed = printed->next;
    } while (printed != nullptr && printed->next != noloop->next);
    std::cout << "]" << std::endl;

}

void fillRandomWithPrikol(Node& hun, int length) { /* Creates random nubers between 0 and 100 */
    srand(time(0));
    Node* prikol = &hun;
    prikol->data = rand() % 100;
    for (int i = 1; i < length; ++i) {
        prikol->next = new Node();
        prikol->next->data = rand() % 100;
        prikol = prikol->next;
    }
    prikol->next = nullptr;
}

void nodeAppend(Node** curr, int workint) {
    Node* newNode = new Node();
    newNode->data = workint;

    if (*curr == nullptr) {
        *curr = newNode;
        return;
    }

    Node* temp = *curr;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void fillRandomWithPrikol(Node& hun, int length, bool ifloop) { /* Creates random nubers between 0 and 100 or an infinite loop */
    srand(time(0));
    Node* prikol = &hun;
    Node* loopprikol;
    prikol->data = 10;
    loopprikol = prikol;
    for (int i = 0; i < length; ++i) {
        prikol->next = new Node();
        prikol->next->data = rand() % 100;
        prikol = prikol->next;
    }
    ifloop ? prikol->next = loopprikol->next : prikol->next = nullptr;
}

bool warnIfLooping (Node &worknode)  { /* this function tests, if any of nodes loop into eachother. it returns TRUE if it does loop */
    bool isloop = false;
    Node* slow = &worknode;
    Node* fast = &worknode;
    if (slow == nullptr || fast == nullptr || fast->next == nullptr || fast->next->next == nullptr) {
        std::cout << "Node too smol" << std::endl; }
    do {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            isloop = true;
            break;
        }
    } while (slow->next && fast->next && fast->next->next);
    return isloop;
}

std::pair<Node*,Node*> splitBS (Node head, int number) { /* splits the list into 2 based on parameters */
    Node* curr = &head;
    Node bihg, mak;
    Node *bigg = &bihg, *smal = &mak;
    while (curr != nullptr) {
        if (curr->data >= number) {
            bigg->next = new Node();
            bigg = bigg->next;
            bigg->data = curr->data;
        } else {
            smal->next = new Node();
            smal = smal->next;
            smal->data = curr->data;
        }
        curr = curr->next;
    }
    bigg->next = nullptr; smal->next = nullptr;
    return std::make_pair(bihg.next, mak.next);

}

void workNode(Node &obj, std::string oper, int workint) { /* This will work with our node */

    Node* curr = &obj;
    if (oper == "show") { printNode(obj); }
    else if (oper == "add") { nodeAppend(&curr, workint); }


    
}

void task3() {

    Node initial;
    initial.data = 10;
    fillRandomWithPrikol(initial, 5);
    warnIfLooping(initial) ? std::cout << "Loop found!!\n" : std::cout << "No loop found!!\n";
    workNode(initial, "show", 1);
    workNode(initial, "add", 10);
    printNode(initial);

}

void task2() {

    Node initial;
    fillRandomWithPrikol(initial, 10);
    warnIfLooping(initial) ? std::cout << "Loop found!!\n" : std::cout << "No loop found!!\n";
    std::cout << std::endl << "Unsorted:\n";
    printNode(initial);
    std::pair<Node*,Node*> wow;
    int seppoint;
    std::cout << std::endl << "Separation point: ";
    std::cin >> seppoint;
    wow = splitBS(initial, seppoint);
    std::cout << std::endl << "Sorted via separation point:\n";
    printNode(wow.first);
    printNode(wow.second);
    std::cout << std::endl;

}



// void main1() {
    

//     Node initial;
//     fillRandomWithPrikol(initial, 6);
//     warnIfLooping(initial) ? std::cout << "Loop found!!\n" : std::cout << "No loop found!!\n";
//     printNode(initial);
//     std::pair<Node,Node> wow;
//     wow = splitBS(initial, 50);
//     printNode(wow.first);
//     printNode(wow.second);
//     std::cout << std::endl;
    
// }

int main() {

    task2();


    return 0;

}

