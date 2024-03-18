#include <iostream>
#include <string>
#include <vector>

// Простая реализация хеш-таблицы с использованием вектора и цепочек для разрешения коллизий
class HashTable {
private:
    // Структура узла списка для цепочек
    struct Node {
        std::string key; // Ключ
        std::string value; // Значение
        Node* next; // Указатель на следующий узел
        Node(const std::string& k, const std::string& v) : key(k), value(v), next(nullptr) {} // Конструктор узла
    };

    std::vector<Node*> table; // Вектор, представляющий хеш-таблицу
    int size; // Количество элементов в таблице

    // Функция хеширования
    int hash(const std::string& key) {
        int hashValue = 0;
        for (char ch : key) {
            hashValue = (hashValue * 31 + ch) % table.size(); // Простая функция хеширования
        }
        return hashValue;
    }

public:
    // Конструктор, инициализирующий таблицу с начальным размером 20
    HashTable(int initialSize = 20) : size(0) {
        table.resize(initialSize, nullptr); // Инициализация вектора указателей на узлы
    }

    // Вставка элемента в хеш-таблицу
    void insert(const std::string& key, const std::string& value) {
        int index = hash(key); // Получаем хеш-код ключа
        Node* newNode = new Node(key, value); // Создаем новый узел
        newNode->next = table[index]; // Устанавливаем новый узел в начало цепочки
        table[index] = newNode;
        size++; // Увеличиваем размер таблицы
    }

    // Получение значения по ключу
    std::string get(const std::string& key) {
        int index = hash(key); // Получаем хеш-код ключа
        Node* current = table[index]; // Начинаем поиск с начала цепочки
        while (current != nullptr) {
            if (current->key == key) { // Если ключ найден, возвращаем значение
                return current->value;
            }
            current = current->next; // Переходим к следующему узлу в цепочке
        }
        return "Key not found"; // Если ключ не найден, возвращаем сообщение об ошибке
    }

    // Реструктуризация таблицы (рехеширование)
    void rehash() {
        std::vector<Node*> oldTable = table; // Сохраняем старую таблицу
        table.clear(); // Очищаем текущую таблицу
        table.resize(oldTable.size() * 2, nullptr); // Увеличиваем размер таблицы вдвое
        size = 0; // Сбрасываем размер таблицы

        // Перебираем все цепочки в старой таблице и переносим их в новую таблицу
        for (Node* head : oldTable) {
            Node* current = head; // Начинаем с начала цепочки
            while (current != nullptr) {
                insert(current->key, current->value); // Вставляем элемент из старой таблицы в новую
                Node* temp = current;
                current = current->next; // Переходим к следующему узлу в цепочке
                delete temp; // Удаляем текущий узел, чтобы избежать утечек памяти
            }
        }
    }

    // Вывод содержимого таблицы
    void display() {
        for (int i = 0; i < table.size(); ++i) {
            std::cout << i << ": "; // Выводим индекс
            Node* current = table[i]; // Начинаем с начала цепочки
            while (current != nullptr) {
                std::cout << "[" << current->key << ", " << current->value << "] "; // Выводим пару ключ-значение
                current = current->next; // Переходим к следующему узлу в цепочке
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

        if (input == "EXIT") { // Если пользователь ввел 'EXIT', выходим из цикла
            break;
        }

        std::string help = reservedWords.get(input); // Получаем справку для введенного слова
        if (help == "Key not found") { // Если слово не найдено в таблице
            std::cout << "Word not found in the reserved words list. Adding it to the table." << std::endl;
            reservedWords.insert(input, "No help available for this word yet."); // Добавляем его в таблицу
            reservedWords.rehash(); // Перестраиваем таблицу
        } else {
            std::cout << "Help: " << help << std::endl; // Выводим справку для слова
        }
    }

    std::cout << "Final state of the hash table:" << std::endl;
    reservedWords.display(); // Выводим конечное состояние таблицы

    return 0;
}
