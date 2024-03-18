#include <iostream>
#include <string>
#include <vector>

// Простая реализация хеш-таблицы с использованием вектора и цепочек для разрешения коллизий
class HashTable {
private:
    struct Node {
        std::string key;
        std::string value;
        Node* next;
        Node(const std::string& k, const std::string& v) : key(k), value(v), next(nullptr) {}
    };

    std::vector<Node*> table;
    int size;

    // Функция хеширования
    int hash(const std::string& key) {
        int hashValue = 0;
        for (char ch : key) {
            hashValue = (hashValue * 31 + ch) % table.size();
        }
        return hashValue;
    }

public:
    HashTable(int initialSize = 20) : size(0) {
        table.resize(initialSize, nullptr);
    }

    // Вставка элемента в хеш-таблицу
    void insert(const std::string& key, const std::string& value) {
        int index = hash(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    // Получение значения по ключу
    std::string get(const std::string& key) {
        int index = hash(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return "Key not found";
    }

    // Реструктуризация таблицы (рехеширование)
    void rehash() {
        std::vector<Node*> oldTable = table;
        table.clear();
        table.resize(oldTable.size() * 2, nullptr);
        size = 0;

        for (Node* head : oldTable) {
            Node* current = head;
            while (current != nullptr) {
                insert(current->key, current->value);
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    // Вывод содержимого таблицы
    void display() {
        for (int i = 0; i < table.size(); ++i) {
            std::cout << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                std::cout << "[" << current->key << ", " << current->value << "] ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // Создаем хеш-таблицу и добавляем зарезервированные слова
    HashTable reservedWords;
    reservedWords.insert("if", "HELP for 'if' statement");
    reservedWords.insert("else", "HELP for 'else' statement");
    reservedWords.insert("while", "HELP for 'while' loop");
    reservedWords.insert("for", "HELP for 'for' loop");
    reservedWords.insert("int", "HELP for integer data type");
    reservedWords.insert("float", "HELP for float data type");
    reservedWords.insert("void", "HELP for void data type");
    reservedWords.insert("return", "HELP for 'return' statement");
    reservedWords.insert("include", "HELP for include directive");
    reservedWords.insert("using", "HELP for using directive");
    reservedWords.insert("class", "HELP for defining classes");
    reservedWords.insert("public", "HELP for public access specifier");
    reservedWords.insert("private", "HELP for private access specifier");
    reservedWords.insert("protected", "HELP for protected access specifier");
    reservedWords.insert("namespace", "HELP for defining namespaces");
    reservedWords.insert("const", "HELP for defining constant values");
    reservedWords.insert("new", "HELP for dynamic memory allocation");
    reservedWords.insert("delete", "HELP for deallocating memory");
    reservedWords.insert("struct", "HELP for defining structures");
    reservedWords.insert("typedef", "HELP for defining type aliases");

    std::string input;
    while (true) {
        std::cout << "Enter a reserved word (or 'EXIT' to quit): ";
        std::cin >> input;

        if ((input == "EXIT")||(input == "0")) {
            break;
        }

        std::string help = reservedWords.get(input);
        if (help == "Key not found") {
            std::cout << "Word not found in the reserved words list. Adding it to the table." << std::endl;
            reservedWords.insert(input, "No help available for this word yet.");
            reservedWords.rehash();
        } else {
            std::cout << "Help: " << help << std::endl;
        }
    }

    std::cout << "Final state of the hash table:" << std::endl;
    reservedWords.display();

    return 0;
}
