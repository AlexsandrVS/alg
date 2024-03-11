#pragma region MAIN
#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>
#include <thread>
#include <mutex>
#include <iomanip>
#include <stdexcept>
#include <stack>
#include <queue>

#pragma region LinkedList

struct Node {
    int data;
    std::shared_ptr<Node> next;
};

class LinkedList {
private:
    std::shared_ptr<Node> head;
    std::ofstream logfile;
    std::mutex mtx;

public:

    LinkedList() : head(nullptr) {
        logfile.open("log.txt", std::ios::out | std::ios::app);
        if (!logfile.is_open()) {
            std::cerr << "Failed to open the log file\n";
        } else {
            // Определение времени начала сессии
            std::time_t startSessionTime = std::time(nullptr);
            std::string startTimeStamp = std::asctime(std::localtime(&startSessionTime));
            startTimeStamp.pop_back();
            logfile << "=== SRT session - (" + startTimeStamp + ") ===\n";
        }
        log("Program started", true);
    }

    ~LinkedList() {
        log("Program ended", true);
            std::time_t startSessionTime = std::time(nullptr);
            std::string startTimeStamp = std::asctime(std::localtime(&startSessionTime));
            startTimeStamp.pop_back();
            logfile << "=== END session - (" + startTimeStamp + ") ===\n";
        logfile.close();
        clear();
    }

    void prepend(int value) {
        std::thread t([&] {
            std::lock_guard<std::mutex> lock(mtx);
            std::shared_ptr<Node> newNode = std::make_shared<Node>();
            newNode->data = value;
            newNode->next = head;
            head = newNode;
            log("Added to the beginning", true);
        });
        t.detach();
    }

    void append(int value) {
        std::thread t([&] {
            std::lock_guard<std::mutex> lock(mtx);
            std::shared_ptr<Node> newNode = std::make_shared<Node>();

            newNode->data = value;
            newNode->next = nullptr;

            if (!head) {
                head = newNode;
            } else {
                std::shared_ptr<Node> temp = head;

                while (temp->next) {
                    temp = temp->next;
                }

                temp->next = newNode;
            }
            log("Added to the end", true);
        });
        t.detach();
    }

    void removeFirst() {
        std::thread t([&] {
            std::lock_guard<std::mutex> lock(mtx);
            if (head) {
                head = head->next;
                log("Removed from the beginning", true);
            } else {
                log("Rm from stp failed: List is empty", false);
            }
        });
        t.detach();
    }

    void removeLast() {
        std::thread t([&] {
            std::lock_guard<std::mutex> lock(mtx);
            if (head) {
                if (!head->next) {
                    head = nullptr;
                } else {
                    std::shared_ptr<Node> temp = head;
                    while (temp->next->next) {
                        temp = temp->next;
                    }
                    temp->next = nullptr;
                }
                log("Removed from the end", true);
            } else {
                log("Rm from end failed: List is empty", false);
            }
        });
        t.detach();
    }

    void printPosNegReverse() {
        try {
            std::stack<int> positiveStack;
            std::stack<int> negativeStack;

            std::shared_ptr<Node> temp = head;
            while (temp) {
                if (temp->data > 0) {
                    positiveStack.push(temp->data);
                } else if (temp->data < 0) {
                    negativeStack.push(temp->data);
                }
                temp = temp->next;
            }

            std::cout << "Positive numbers in reverse order: ";
            while (!positiveStack.empty()) {
                std::cout << positiveStack.top() << " ";
                positiveStack.pop();
            }

            std::cout << "\nNegative numbers in reverse order: ";
            while (!negativeStack.empty()) {
                std::cout << negativeStack.top() << " ";
                negativeStack.pop();
            }
            std::cout << std::endl;
            log("Print list with stack", true);

        } catch (const std::exception& e) {
            log("Print list with stack", false);
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
    }

    void clear() {
        std::thread t([&] {
            std::lock_guard<std::mutex> lock(mtx);
            head = nullptr;
            log("List cleared", true);
        });
        t.detach();
    }

    void reverse() {
        std::thread t([&] {
            std::lock_guard<std::mutex> lock(mtx);
            std::shared_ptr<Node> prev = nullptr;
            std::shared_ptr<Node> current = head;
            std::shared_ptr<Node> next = nullptr;

            while (current) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }

            head = prev;
            log("List reversed", true);
        });
        t.detach();
    }

    void display() {
        std::thread t([&] {
            std::lock_guard<std::mutex> lock(mtx);
            std::shared_ptr<Node> temp = head;
            while (temp) {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
            log("Displayed list", true);
        });
        t.detach();
    }

    bool isSymmetric() {
        try {
            std::stack<int> stack;
            std::queue<int> queue;

            std::shared_ptr<Node> temp = head;
            while (temp) {
                stack.push(temp->data);
                queue.push(temp->data);
                temp = temp->next;
            }

            while (!stack.empty() && !queue.empty()) {
                if (stack.top() != queue.front()) {
                    log("check a symmetric", true);
                    return false;
                }
                stack.pop();
                queue.pop();
            }

            log("Сheck a symmetric", true);
            return stack.empty() && queue.empty();

        } catch (const std::exception& e) {
            log("Сheck a symmetric", false);
            std::cerr << "Exception caught: " << e.what() << std::endl;
            return false;
        }
    }

    void log(const std::string& command, bool success) {
        std::thread::id threadId = std::this_thread::get_id();
        std::time_t currentTime = std::time(nullptr);
        std::string timestamp = std::asctime(std::localtime(&currentTime));
        timestamp.pop_back();

        // Определяем фиксированную ширину для каждого столбца
        const int timestampWidth = 25;
        const int threadIdWidth = 20;
        const int commandWidth = 35;
        const int statusWidth = 20;

        // Форматируем строки для каждого столбца
        std::stringstream ss;
        ss << "[" << std::left << std::setw(timestampWidth) << timestamp << "] ";
        ss << "Thread ID: " << std::setw(threadIdWidth) << threadId << " | ";
        ss << "Command: " << std::setw(commandWidth) << command << " | ";
        ss << "Status: " << std::setw(statusWidth) << (success ? "Success" : "Failure") << std::endl;

        logfile << ss.str();
    }

};

#pragma endregion
#pragma endregion

int main() {
    LinkedList list;
    int choice;
    int value;

    do {
        std::cout << "\nOperations:\n";
        std::cout << "1. Add to beginning\n";
        std::cout << "2. Add to end\n";
        std::cout << "3. Remove from beginning\n";
        std::cout << "4. Remove from end\n";
        std::cout << "5. Clear list\n";
        std::cout << "6. Reverse list\n";
        std::cout << "7. Display list\n";
        std::cout << "8. Function to print with stack\n";
        std::cout << "9. Function to check a symmetric\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        try {
            std::thread t;
            switch (choice) {
                case 1:
                    std::cout << "Enter value to add to the beginning: ";
                    std::cin >> value;
                    if (std::cin.fail()) {
                        throw std::invalid_argument("Invalid input");
                    }
                    t = std::thread([&] { list.prepend(value); });
                    break;
                case 2:
                    std::cout << "Enter value to add to the end: ";
                    std::cin >> value;
                    if (std::cin.fail()) {
                        throw std::invalid_argument("Invalid input");
                    }
                    t = std::thread([&] { list.append(value); });
                    break;
                case 3:
                    t = std::thread([&] { list.removeFirst(); });
                    break;
                case 4:
                    t = std::thread([&] { list.removeLast(); });
                    break;
                case 5:
                    t = std::thread([&] { list.clear(); });
                    break;
                case 6:
                    t = std::thread([&] { list.reverse(); });
                    break;
                case 7:
                    t = std::thread([&] { list.display(); });
                    break;
                case 8:
                    t = std::thread([&] { list.printPosNegReverse(); });
                    break;
                case 9:
                    t = std::thread([&] { std::cout << (list.isSymmetric() ? "is symmetric" : "is not symmetric"); });
                    break;
                case 0:
                    std::cout << "Exiting\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
            if (t.joinable()) {
                t.join();
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << ". Please enter a valid number.\n";
            list.log("Invalid input", false);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);

    return 0;
}