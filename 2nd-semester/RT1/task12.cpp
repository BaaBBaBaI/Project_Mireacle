#include <iostream>
#include <string>

struct Node /* node itself */
{
    int data;
    Node* next;
    // Node* prev;

};
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


void fillRandomWithPrikol(Node& hun, int length, bool ifloop) { /* Creates random nubers between 0 and 100 or an infinite loop */
    srand(time(0));
    Node* prikol = &hun;
    Node* loopprikol;
    prikol->data = rand() % 100;
    loopprikol = prikol;
    for (int i = 0; i < length; ++i) {
        prikol->next = new Node();
        prikol->next->data = rand() % 100;
        prikol = prikol->next;
    }
    ifloop ? prikol->next = loopprikol : prikol->next = nullptr;
}

int main() {
    return 0;
}