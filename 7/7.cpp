
#include <iostream>
#include <fstream>

using namespace std;

/*   
    * На основе процедуры обхода дерева снизу вверх реализовать операцию поиска узла
    * с заданным значением в дереве, не являющемся деревом поиска. Из двух
    * последовательностей символов построить два бинарных дерева минимальной высоты.
    * В первом дереве найти элемент с заданным значением и подключить второе дерево в
    * качестве его левого поддерева, если оно пусто, или левого поддерева первого из его
    * крайних левых потомков, имеющих пустое левое поддерево. 
*/

// Класс для узла бинарного дерева
class BinaryTreeNode {
public:
    int data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode* parent;

    // Конструктор
    BinaryTreeNode(int value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Класс для бинарного дерева
class BinaryTree {
private:
    BinaryTreeNode* root;

    // Приватные вспомогательные методы для рекурсивных операций
    BinaryTreeNode* addrRecursive(BinaryTreeNode* node, int value);
    BinaryTreeNode* fatherRecursive(BinaryTreeNode* node, BinaryTreeNode* child);
    void writeToRecursive(ofstream& file, BinaryTreeNode* node, int level);
    int nodesQuantityRecursive(BinaryTreeNode* node);

public:
    // Конструктор
    BinaryTree() : root(nullptr) {}

    // Деструктор
    ~BinaryTree() {
        clear();
    }

    // Операции над узлами дерева
    BinaryTreeNode* addr(int value);
    int value(BinaryTreeNode* node);
    BinaryTreeNode* left(BinaryTreeNode* node);
    BinaryTreeNode* right(BinaryTreeNode* node);
    BinaryTreeNode* father(BinaryTreeNode* node);
    BinaryTreeNode* brother(BinaryTreeNode* node);
    bool isLeft(BinaryTreeNode* node);
    bool isRight(BinaryTreeNode* node);

    // Дополнительные операции
    BinaryTree* create();
    void clear();
    void writeTo(const char* filename);
    int nodesQuantity(BinaryTreeNode* node);
};

// Методы для операций над узлами дерева
BinaryTreeNode* BinaryTree::addr(int value) {
    return addrRecursive(root, value);
}

int BinaryTree::value(BinaryTreeNode* node) {
    return (node != nullptr) ? node->data : -1; // Вернуть -1 в случае отсутствия узла
}

BinaryTreeNode* BinaryTree::left(BinaryTreeNode* node) {
    return (node != nullptr) ? node->left : nullptr;
}

BinaryTreeNode* BinaryTree::right(BinaryTreeNode* node) {
    return (node != nullptr) ? node->right : nullptr;
}

BinaryTreeNode* BinaryTree::father(BinaryTreeNode* node) {
    return (node != nullptr) ? node->parent : nullptr;
}

BinaryTreeNode* BinaryTree::brother(BinaryTreeNode* node) {
    BinaryTreeNode* parent = father(node);
    if (parent == nullptr)
        return nullptr;
    return (node == parent->left) ? parent->right : parent->left;
}

bool BinaryTree::isLeft(BinaryTreeNode* node) {
    BinaryTreeNode* parent = father(node);
    return (parent != nullptr && parent->left == node);
}

bool BinaryTree::isRight(BinaryTreeNode* node) {
    BinaryTreeNode* parent = father(node);
    return (parent != nullptr && parent->right == node);
}

// Методы для дополнительных операций
BinaryTree* BinaryTree::create() {
    return new BinaryTree();
}

void BinaryTree::clear() {
    // Реализация удаления всех узлов дерева (может быть с использованием рекурсии)
}

void BinaryTree::writeTo(const char* filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }
    writeToRecursive(file, root, 0);
    file.close();
}

int BinaryTree::nodesQuantity(BinaryTreeNode* node) {
    return nodesQuantityRecursive(node);
}

// Рекурсивная реализация операций
BinaryTreeNode* BinaryTree::addrRecursive(BinaryTreeNode* node, int value) {
    // Реализация поиска узла с заданным значением в дереве
}

BinaryTreeNode* BinaryTree::fatherRecursive(BinaryTreeNode* node, BinaryTreeNode* child) {
    // Реализация поиска родителя узла в дереве
}

void BinaryTree::writeToRecursive(ofstream& file, BinaryTreeNode* node, int level) {
    // Реализация вывода дерева в файл с отступами
}

int BinaryTree::nodesQuantityRecursive(BinaryTreeNode* node) {
    // Реализация определения числа узлов поддерева с корнем node
}

// Пример использования
int main() {
    // Пример использования
    BinaryTree tree;

    // Допустим, что дерево уже создано и заполнено данными

    // Пример использования операций
    BinaryTreeNode* node = tree.addr(5);
    cout << "Value of node with data 5: " << tree.value(node) << endl;

    BinaryTreeNode* leftChild = tree.left(node);
    cout << "Left child of node with data 5: " << tree.value(leftChild) << endl;

    // и т.д.

    return 0;
}
