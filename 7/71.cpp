#include <iostream>
#include <queue>

using namespace std;

// Структура для узла бинарного дерева
struct Node {
    int data;
    Node* left;
    Node* right;

    // Конструктор для узла
    Node(int value) : data(value), left(nullptr), right(nullptr) {}

    // Метод для вывода дерева с отступами
    void printIndented(int indent = 0) {

        /*
        Сначала функция проверяет, существует ли правый потомок текущего узла (right != nullptr). 
        ! Если да, она вызывает себя рекурсивно для правого потомка с увеличением отступа на 4 пробела (right->printIndented(indent + 4)). 
        ! Это позволяет спуститься на один уровень ниже в правое поддерево и продолжить вывод оттуда.

        Затем функция выводит значение текущего узла (data), 
        добавляя отступ из пробелов в соответствии с текущим уровнем вложенности узла. 
        Количество пробелов определяется параметром indent.

        После вывода значения текущего узла функция проверяет, существует ли левый потомок (left != nullptr). 
        ! Если да, она вызывает себя рекурсивно для левого потомка с увеличением отступа на 4 пробела (left->printIndented(indent + 4)).
        ! Это позволяет спуститься на один уровень ниже в левое поддерево и продолжить вывод оттуда.

        */
        if (right != nullptr) {
            right->printIndented(indent + 4);
        }
        cout << string(indent, ' ') << data << endl;
        if (left != nullptr) {
            left->printIndented(indent + 4);
        }
    }
};

void findAndAttach(Node* root, int value, Node* tree) {

    /*
        ! 1. Создается очередь `q` для обхода дерева в ширину, начиная с корня `root`. Корневой узел добавляется в очередь.
        ! 2. Запускается цикл `while`, который будет выполняться до тех пор, пока очередь не станет пустой.
        ! 3. На каждой итерации извлекается узел из начала очереди при помощи `q.front()`, после чего этот узел удаляется из очереди (`q.pop()`).
        ! 4. Проверяется значение данных текущего узла. Если оно совпадает с искомым значением (`value`), то этот узел записывается в переменную `targetNode`, и цикл прерывается при помощи `break`.
        ! 5. Если значение текущего узла не совпадает с искомым значением, то, если у текущего узла есть левый и/или правый потомок, эти потомки добавляются в очередь для дальнейшей обработки.
        ! 6. После завершения цикла проверяется, был ли найден узел с искомым значением (`targetNode`). Если нет, то выводится сообщение об ошибке, и функция завершает свою работу.
        ! 7. Если узел с искомым значением был найден, то второе дерево `tree` подключается к нему:
        !   - Если у найденного узла нет левого поддерева, то второе дерево становится его левым поддеревом (`targetNode->left = tree`).
        !   - Если у найденного узла уже есть левое поддерево, то второе дерево добавляется к крайнему левому узлу этого поддерева. Для этого находим крайний левый узел текущего левого поддерева и присоединяем к нему второе дерево.
    */

    // Создаем очередь для обхода дерева снизу вверх
    queue<Node*> q;
    q.push(root);
    Node* targetNode = nullptr;

    // Ищем узел с заданным значением
    while (!q.empty()) {
        // Извлекаем узел из очереди для проверки
        Node* current = q.front();
        q.pop();

        // Проверяем, содержит ли текущий узел искомое значение
        if (current->data == value) {
            // Если да, сохраняем указатель на этот узел в targetNode и прекращаем поиск
            targetNode = current;
            break;
        }

        // Если искомый узел еще не найден, добавляем его потомков в очередь для дальнейшего исследования
        if (current->left) q.push(current->left); // Добавляем левого потомка, если он существует
        if (current->right) q.push(current->right); // Добавляем правого потомка, если он существует
    }


    // Если узел не найден, выводим сообщение об ошибке
    if (!targetNode) {
        cout << "Node with the given value is not found in the tree." << endl;
        return;
    }

    // Подключаем второе дерево
    if (!targetNode->left) {
        targetNode->left = tree;
    } else {
        Node* current = targetNode->left;
        while (current->left) {
            current = current->left;
        }
        current->left = tree;
    }
}

int main() {
    Node* firstTree = new Node(5);
    firstTree->left = new Node(6);
    firstTree->right = new Node(7);
    firstTree->right->right = new Node(3);
    firstTree->right->right->right = new Node(9);
    firstTree->left->right = new Node(0);
    firstTree->left->left = new Node(3);

    Node* secondTree = new Node(1);
    secondTree->left = new Node(6);

    findAndAttach(firstTree, 3, secondTree);

    cout << "The first tree after attaching the second tree:" << endl;
    firstTree->printIndented();

    return 0;
}
