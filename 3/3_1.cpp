#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <string>
#include <fstream>
#include <chrono>
#include <memory>

// Определение структуры узла списка
struct Node {
    int data;
    std::unique_ptr<Node> next;

    // Конструктор узла списка
    Node(int value) : data(value), next(nullptr) {}
};

// Определение класса односвязного списка
class LinkedList {
private:
    std::unique_ptr<Node> head; // Умный указатель на начало списка
    std::mutex mtx; // Мьютекс для обеспечения потокобезопасности

public:
    LinkedList() : head(nullptr) {}

    // Метод для добавления элемента в конец списка
    void append(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (head == nullptr) {
            head = std::make_unique<Node>(value);
        } else {
            Node* current = head.get();
            while (current->next != nullptr) {
                current = current->next.get();
            }
            current->next = std::make_unique<Node>(value);
        }
    }

    // Метод для удаления элемента из списка
    void remove(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (head == nullptr)
            return;

        if (head->data == value) {
            head = std::move(head->next);
            return;
        }

        Node* current = head.get();
        while (current->next != nullptr) {
            if (current->next->data == value) {
                current->next = std::move(current->next->next);
                return;
            }
            current = current->next.get();
        }
    }

    // Метод для добавления элемента в конец списка
    void appendBack(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (head == nullptr) {
            head = std::make_unique<Node>(value);
        } else {
            Node* current = head.get();
            while (current->next != nullptr) {
                current = current->next.get();
            }
            current->next = std::make_unique<Node>(value);
        }
    }

    // Метод для удаления последнего элемента из списка
    void removeBack() {
        std::lock_guard<std::mutex> lock(mtx);
        if (head == nullptr)
            return;

        if (head->next == nullptr) {
            head.reset();
            return;
        }

        Node* current = head.get();
        while (current->next->next != nullptr) {
            current = current->next.get();
        }
        current->next.reset();
    }

    // Метод для удаления всех элементов из списка
    void removeAll() {
        std::lock_guard<std::mutex> lock(mtx);
        head.reset();
    }

    // Метод для изменения порядка узлов в списке на обратный
    void reverseList() {
        std::lock_guard<std::mutex> lock(mtx);
        Node* prev = nullptr;
        Node* current = head.get();
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next.release();
            current->next.reset(prev);
            prev = current;
            current = next;
        }
        head.reset(prev);
    }

    // Метод для вывода содержимого списка в консоль
    void print() {
        std::lock_guard<std::mutex> lock(mtx);
        Node* current = head.get();
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }

    // Метод для вывода меню операций в консоль
    void printMenu() {
        system("cls || clear"); // Очистка консоли
        std::cout << "1. Add an element" << std::endl;
        std::cout << "2. Remove an element" << std::endl;
        std::cout << "3. Add an element to the end" << std::endl;
        std::cout << "4. Remove an element from the end" << std::endl;
        std::cout << "5. Remove all elements" << std::endl;
        std::cout << "6. Reverse the list" << std::endl;
        std::cout << "7. Print the list" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Select an operation: ";
    }
};

// Функция для записи логов в файл
void writeLogs(const std::vector<std::string>& logs) {
    std::ofstream logfile("logs.txt", std::ios::app);
    if (logfile.is_open()) {
        for (const std::string& log : logs) {
            logfile << log << std::endl;
        }
        logfile.close();
    } else {
        std::cerr << "Unable to open the log file." << std::endl;
    }
}

int main() {
    LinkedList list;
    std::vector<std::thread> threads;
    std::vector<std::string> logs; // Перенесли объявление переменной logs вне блока switch

    while (true) {
        list.printMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter a value to add: ";
                int value;
                std::cin >> value;
                threads.push_back(std::thread([&list, value]() { list.append(value); }));
                break;
            }
            case 2: {
                std::cout << "Enter a value to remove: ";
                int value;
                std::cin >> value;
                threads.push_back(std::thread([&list, value]() { list.remove(value); }));
                break;
            }
            case 3: {
                std::cout << "Enter a value to append to the end: ";
                int value;
                std::cin >> value;
                threads.push_back(std::thread([&list, value]() { list.appendBack(value); }));
                break;
            }
            case 4:
                threads.push_back(std::thread([&list]() { list.removeBack(); }));
                break;
            case 5:
                threads.push_back(std::thread([&list]() { list.removeAll(); }));
                break;
            case 6:
                threads.push_back(std::thread([&list]() { list.reverseList(); }));
                break;
            case 7:
                threads.push_back(std::thread([&list]() { list.print(); }));
                break;
            case 8:
                for (auto& th : threads) {
                    if (th.joinable())
                        th.join();
                }
                logs.push_back("Program finished successfully.");
                writeLogs(logs);
                return 0;
            default:
                std::cout << "Invalid operation. Please try again." << std::endl;
        }
    }

    return 0;
}
