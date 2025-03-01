
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct book
{
    std::pair<std::string, std::vector<std::string>> value;
    int count; //Количество экземпляров узла с данным значением (в дереве)
    book* left; 
    book* right;
};


int depth(book* root) {
    if (!root) {
        return 0;
    }
    
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);

    return 1 + std::max(leftDepth, rightDepth);
}


book* createbook( std::pair<std::string, std::vector<std::string>> value) { //Создание дерева
    book* newbook = new book;
    newbook -> value = value;
    newbook -> left = NULL;
    newbook -> right = NULL;
    return newbook; 
}

book* insert(book* root, std::pair<std::string, std::vector<std::string>> value) { //Вставка значения в дерево
    
    if (!root) { return createbook(value); }
    if (value.first < root->value.first) { root->left = insert(root->left, value); }
    else if (value.first > root->value.first) { root->right = insert(root->right, value); }
    return root;

}

book* find(book* root, std::string search) {
    if (!root) { return NULL; }
    if (root->value.first == search) { 
        return root;
    }
    book* left = find(root->left, search);
    book* right = find(root->right, search);
    if (left) { return left; }
    if (right) { return right; }
    return NULL;
}


void preorder(book* node, int level, std::ostream& os) {
    if (node) {
        os << "{User: " << node->value.first << " } (Phone Numbers: ";
        
        // Print the authors (second element - vector of strings)
        for (size_t i = 0; i < node->value.second.size(); ++i) {
            os << node->value.second[i];
            if (i < node->value.second.size() - 1) {
                os << ", ";
            }
        }
        os << ") \n";
        
        // Recursively print left and right subtrees
        preorder(node->left, level + 1, os);
        preorder(node->right, level + 1, os);
    }
}

std::ostream& operator<<(std::ostream& os, book* root) {
    preorder(root, 0, os);
    return os;
}

int main() {
    book * root = NULL;
    root = insert(root, {"John", {"123", "456"}});
    root = insert(root, {"Alice", {"789", "012"}});
    root = insert(root, {"Bob", {"345", "678"}});
    root = insert(root, {"Charlie", {"901", "234"}});
    root = insert(root, {"David", {"567", "890"}});
    root = insert(root, {"Eve", {"321", "456"}});
    
    book* findd = find(root, "Alice");

    std::cout << findd << std::endl;

    return 0;
}

