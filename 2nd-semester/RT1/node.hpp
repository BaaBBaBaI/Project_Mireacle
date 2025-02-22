
#ifndef NODE_HPP
#define NODE_HPP

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

int sizeNode(Node &linkedlist) {
    int sizeNod = 0;
    Node* printed = &linkedlist;
    Node* noloop = printed;

    if (printed->next == nullptr) {
        return 0;
    }

    do {
        sizeNod++;
        printed = printed->next;
    } while (printed != nullptr && printed->next != noloop->next);

    return sizeNod;
}

void printNode(Node work, std::string o) { /* Prints da note! But also in reverse*/
    if (o == "reversed" || o == "r" || o == "reverse") {
        Node* printed = &work;
        Node* noloop = printed;
        if (printed->prev == nullptr) {
            std::cout << std::endl << "\tNode: [ nothing ]\n\n";
            std::cout << std::endl << "\tNode: [";
            do {
                std::cout << " " << printed->data << " ";
                printed = printed->prev;
            } while (printed != nullptr && printed->prev != noloop->prev);
            std::cout << "]" << std::endl;
            return;
    }

    }
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

/* void printNode(Node* work) { 

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

} */

void fillRandomWithPrikol(Node& hun, int length) { /* fill Node woth random numbero between 0 and 100 */
    srand(time(0));
    Node* prikol = &hun;
    Node* loopprikol; Node* pr;
    prikol->data = rand() % 100;
    loopprikol = prikol;
    for (int i = 1; i < length; ++i) {
        pr = prikol;
        prikol->next = new Node();
        prikol->next->data = rand() % 100;
        prikol = prikol->next;
        prikol->prev = pr;
    }
    loopprikol->prev = nullptr;
    prikol->next = nullptr;
}

void fillRandomWithPrikol(Node& hun, int length, bool ifloop) { /* fill Node woth random numbero between 0 and 100 or an infinite loop */
    srand(time(0));
    Node* prikol = &hun;
    Node* loopprikol; Node* pr;
    prikol->data = rand() % 100;
    loopprikol = prikol;
    for (int i = 0; i < length-1; ++i) {
        pr = prikol;
        prikol->next = new Node();
        prikol->next->data = rand() % 100;
        prikol = prikol->next;
        prikol->prev = pr;
    }
    ifloop ? prikol->next = loopprikol : prikol->next = nullptr;
    ifloop ? loopprikol->prev = prikol : loopprikol->prev = nullptr;
}

void nodeAppend(Node &mass, int workint) {
    Node tempo = mass;
    Node* newNode = new Node();
    newNode->data = workint;
    Node* last = &mass;

    if (last == nullptr) {
        last = newNode;
        return;
    }

    Node* temp = last;
    Node* first = last;
    while (temp->next != first && temp->next != nullptr) {
        temp = temp->next;
    }
    
    if (temp->next == first) {
        newNode->next = first;
    }

    temp->next = newNode;
    newNode->prev = temp;
}


void nodeInsert(Node &mass, int workwith, int workint) {
    Node* curr = &mass;
    while (curr->next != nullptr && curr->next->data != workwith) {
        curr = curr->next;
    } if (curr->next->data == workwith) {
        Node* newNode = new Node();
        newNode->data = workint;
        newNode->next = curr->next;
        newNode->prev = curr;
        curr->next->prev = newNode;
        curr->next = newNode;
        return;
    }
    return;

}

void nodeDel(Node &mass, int workwith) {
    Node* curr = &mass;
    while (curr->next != nullptr && curr->data != workwith) {
        curr = curr->next;
    } if (curr->data == workwith) {
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        delete curr;
        return;
    }
    return;

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

std::pair<Node, Node> splitBS (Node head, int number) { /* splits the list into 2 based on parameters */
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
    return std::make_pair(*bihg.next, *mak.next);

}

#endif