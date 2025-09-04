#include <iostream>
#include <algorithm> // Для std::max
#include <climits> // Для LLONG_MIN и LLONG_MAX

// Определение структуры узла бинарного дерева
struct Node {
    int data;
    Node* left;
    Node* right;

    // Конструктор для удобства
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Функция для подсчета высоты бинарного дерева
int treeHeight(Node* root) {
    // Базовый случай: если дерево пустое (корень nullptr), его высота -1
    if (root == nullptr) {
        return -1;
    }

    // Рекурсивно вычисляем высоту левого и правого поддеревьев
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    // Высота текущего узла - это 1 (сам узел) плюс максимальная высота из его поддеревьев
    return 1 + std::max(leftHeight, rightHeight);
}

// Вспомогательная функция для проверки, является ли дерево BST
// Она проверяет, находится ли значение каждого узла в допустимом диапазоне (min, max)
bool isBSTUtil(Node* node, long long min, long long max) {
    // Пустое дерево является BST
    if (node == nullptr) {
        return true;
    }

    // Если данные этого узла нарушают ограничения min/max, это не BST
    if (node->data <= min || node->data >= max) {
        return false;
    }

    // Рекурсивно проверяем левое и правое поддеревья
    // Для левого поддерева мы сужаем верхнюю границу до значения текущего узла
    // Для правого поддерева мы сужаем нижнюю границу до значения текущего узла
    return
        isBSTUtil(node->left, min, node->data) &&  // Все значения в левом поддереве должны быть < node->data
        isBSTUtil(node->right, node->data, max); // Все значения в правом поддереве должны быть > node->data
}

// Основная функция для проверки, является ли бинарное дерево деревом двоичного поиска (BST)
bool isBST(Node* root) {
    // Начинаем с самого широкого диапазона (LLONG_MIN, LLONG_MAX)
    return isBSTUtil(root, LLONG_MIN, LLONG_MAX);
}

int main() {
    // Создаем пример бинарного дерева
    //         1
    //        / \
    //       2   3
    //      / \
    //     4   5
    //        /
    //       6

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->left = new Node(6);

    // Вычисляем и выводим высоту дерева
    std::cout << "Высота бинарного дерева: " << treeHeight(root) << std::endl; // Ожидаемый вывод: 3

    // Пример пустого дерева
    Node* emptyRoot = nullptr;
    std::cout << "Высота пустого бинарного дерева: " << treeHeight(emptyRoot) << std::endl; // Ожидаемый вывод: -1

    // Пример дерева с одним узлом
    Node* singleNodeRoot = new Node(10);
    std::cout << "Высота бинарного дерева с одним узлом: " << treeHeight(singleNodeRoot) << std::endl; // Ожидаемый вывод: 0

    std::cout << "\n--- Проверка на BST ---\n";
    // Проверяем исходное дерево (не является BST)
    std::cout << "Является ли исходное дерево BST? " << (isBST(root) ? "Да" : "Нет") << std::endl; // Ожидаемый вывод: Нет

    // Создаем пример корректного BST
    //        4
    //       / \
    //      2   5
    //     / \
    //    1   3
    Node* bstRoot = new Node(4);
    bstRoot->left = new Node(2);
    bstRoot->right = new Node(5);
    bstRoot->left->left = new Node(1);
    bstRoot->left->right = new Node(3);

    std::cout << "Является ли новое дерево BST? " << (isBST(bstRoot) ? "Да" : "Нет") << std::endl; // Ожидаемый вывод: Да

    // Очистка памяти (важно для предотвращения утечек памяти в реальных приложениях)
    // В данном простом примере мы не реализуем полную функцию удаления дерева,
    // но в реальных проектах это было бы необходимо.
    delete root->left->right->left;
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;
    delete singleNodeRoot;

    // Очистка памяти для нового BST
    delete bstRoot->left->left;
    delete bstRoot->left->right;
    delete bstRoot->left;
    delete bstRoot->right;
    delete bstRoot;


    return 0;
}