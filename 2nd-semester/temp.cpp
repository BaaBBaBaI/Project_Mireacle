#include <iostream>
#include <utility> // For std::pair

struct Node {
    int data;
    Node* next;

    // Constructor for convenience
    Node(int val = 0, Node* nxt = nullptr) : data(val), next(nxt) {}
};

std::pair<Node*, Node*> splitBS(Node* head, int number) {
    Node dummyBig(0), dummySmall(0); // Dummy nodes to simplify list management
    Node* bigg = &dummyBig;          // Pointer to the last node in the "big" list
    Node* smal = &dummySmall;        // Pointer to the last node in the "small" list

    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data >= number) {
            bigg->next = new Node(curr->data); // Create a new node with the current data
            bigg = bigg->next;                 // Move the pointer to the new node
        } else {
            smal->next = new Node(curr->data); // Create a new node with the current data
            smal = smal->next;                 // Move the pointer to the new node
        }
        curr = curr->next; // Move to the next node in the original list
    }

    // Return the heads of the two lists (skip the dummy nodes)
    return std::make_pair(dummyBig.next, dummySmall.next);
}

// Helper function to print a linked list
void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

// Example usage
int main() {
    // Create a sample linked list: 5 -> 1 -> 8 -> 3 -> 7
    Node* head = new Node(5, new Node(1, new Node(8, new Node(3, new Node(7)))));

    // Split the list into two based on the number 5
    auto result = splitBS(head, 5);

    // Print the two resulting lists
    std::cout << "Big List: ";
    printList(result.first);

    std::cout << "Small List: ";
    printList(result.second);

    return 0;
}