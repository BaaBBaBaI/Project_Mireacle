
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
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


struct book
{
    std::pair<std::string, std::vector<std::string>> value;
    int count; //Количество экземпляров узла с данным значением (в дереве)
    book* left; 
    book* right;
};

book* findMin(book* node) {
    book* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


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
    if (value.first == root->value.first) {
        for (const std::string& phone : value.second ) {
             if (std::find(root->value.second.begin(), root->value.second.end(), phone) == root->value.second.end()) {
                root->value.second.push_back(phone);
            }
        }
        return root;
    }
    if (value.first < root->value.first) { root->left = insert(root->left, value); }
    else if (value.first > root->value.first) { root->right = insert(root->right, value); }
    return root;

}

book* del(book* root, std::pair<std::string, std::vector<std::string>> value) {
    if (!root) { 
        return root; 
    }
    
    if (value.first < root->value.first) { 
        root->left = del(root->left, value); 
    }
    else if (value.first > root->value.first) { 
        root->right = del(root->right, value); 
    }
    else { 

        if (!value.second.empty()) {
            bool deleted = false;
            for (const std::string& phone : value.second) {
                auto& numbers = root->value.second;
                auto it = std::find(numbers.begin(), numbers.end(), phone);
                if (it != numbers.end()) {
                    numbers.erase(it);
                    deleted = true;
                }
            }
            
            if (root->value.second.empty()) {
            } else {
                return root;
            }
        }
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        else if (root->left == NULL) {
            book* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            book* temp = root->left;
            delete root;
            return temp;
        }
        book* temp = findMin(root->right);
        root->value = temp->value;
        root->right = del(root->right, std::make_pair(temp->value.first, std::vector<std::string>()));
    }
    
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
    
        for (size_t i = 0; i < node->value.second.size(); ++i) {
            os << node->value.second[i];
            if (i < node->value.second.size() - 1) {
                os << ", ";
            }
        }
        os << ") \n";
        
        preorder(node->left, level + 1, os);
        preorder(node->right, level + 1, os);
    }
}

std::ostream& operator<<(std::ostream& os, book* root) {
    preorder(root, 0, os);
    return os;
}

struct treesec // struct for Дерево отрезков
{
    int keyMin;
    int keyMax;
    treesec* left;
    treesec* right;
};

treesec* createTreeSec(int keyMin, int keyMax) {
    treesec* tree = new treesec;
    tree->keyMin = keyMin;
    tree->keyMax = keyMax;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

treesec* setTreeSec(treesec* root, int keyMin, int keyMax) {
    if (keyMin == keyMax) {
        return createTreeSec(keyMin, keyMax);
        
    } else {
        int mid = (keyMin + keyMax) / 2;
        root = createTreeSec(keyMin, keyMax);
        root->left = setTreeSec(root->left, keyMin, mid);
        root->right = setTreeSec(root->right, mid+1, keyMax);
        return root;
    }

    

}

void xcount(treesec* node, int &countx, const int x) {

    if (!node) return;

    if (x <= node->keyMax && x >= node->keyMin) {
        countx++;
    }

    xcount(node->left, countx, x);
    xcount(node->right, countx, x);

    return;
}

int xcount(treesec* node, const int x) {
    int countx = 0;
    xcount(node, countx, x);
    return countx;
}

void preorder(treesec* node, int level, std::ostream& os) {
    if (!node) return ;

    os << level << ": " << "[" << node->keyMin << ", " << node->keyMax << "] ";

    preorder(node->left, level + 1, os);
    preorder(node->right, level + 1, os);
}



std::ostream& operator<<(std::ostream& os, treesec* root) {
    preorder(root, 0, os);
    return os;
}




#endif
