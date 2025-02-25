#include <iostream>
#include <string>
#include <algorithm>

struct tree
{
    int value; //Значение узла (ключ), данные любого типа
    int count; //Количество экземпляров узла с данным значением (в дереве)
    tree* left; 
    tree* right;
};


int depth(tree* root) {
    if (!root) {
        return 0;
    }
    
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);

    return 1 + std::max(leftDepth, rightDepth);
}


tree* createTree(int value) { //Создание дерева
    tree* newtree = new tree;
    newtree -> value = value;
    newtree -> left = NULL;
    newtree -> right = NULL;
    return newtree; 
}

tree* insert(tree* root, int value) { //Вставка значения в дерево
    
    if (!root) { return createTree(value); }
    if (value < root->value) { root->left = insert(root->left, value); }
    else if (value > root->value) { root->right = insert(root->right, value); }
    return root;

}

tree* createFillTree(int value) { //Создание дерева с заполнением
    srand(time(0));
    tree* newtree = nullptr;
    for (int i = 0; i < value; i++) { // ILLEGAL INSTUCTION ERROR
        int in = rand() % 100;
        newtree = insert(newtree, in);
    }
    return newtree;
}

tree* find(tree* root, int search) {
    if (!root) { return NULL; }
    if (root->value == search) { 
        return root;
    }
    tree* left = find(root->left, search);
    tree* right = find(root->right, search);
    if (left) { return left; }
    if (right) { return right; }
    return NULL;
}


void preorder(tree* node, int level, std::ostream& os) {
    if (node) {
        os << level << ": " << node->value << " | ";
        preorder(node->left, level + 1, os);
        preorder(node->right, level + 1, os);
    }
}


std::ostream& operator<<(std::ostream& os, tree* root) {
    static int level = 0;
    preorder(root, 0, os);
    return os;
}

int main() {
    tree* root = NULL; int fin;
    root = createFillTree(10);
    std::cout << root << std::endl;
    std::cout << depth(root) << std::endl;
    std::cin >> fin; std::cout << std::endl;
    tree* newroot = find(root, fin);
    std::cout << newroot;

    return 0;
}