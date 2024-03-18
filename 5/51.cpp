#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Функция для построения таблицы смещений
void buildOffsetTable(const std::string& pattern, std::vector<int>& offsetTable) {
    int m = pattern.size(); // Длина шаблона
    offsetTable.resize(256, m); // Инициализация таблицы смещений, заполняем ее значением длины шаблона

    // Заполнение таблицы смещений для символов в шаблоне
    for (int i = 0; i < m - 1; ++i) {
        offsetTable[static_cast<int>(pattern[i])] = m - 1 - i; // Заполнение таблицы смещений для каждого символа в шаблоне
    }
}

// Функция для поиска всех вхождений шаблона в тексте с использованием алгоритма Апостолико-Крокемора
void apostolicoCrochemore(const std::string& text, const std::string& pattern) {
    int n = text.size(); // Длина текста
    int m = pattern.size(); // Длина шаблона
    std::vector<int> offsetTable; // Таблица смещений
    buildOffsetTable(pattern, offsetTable); // Построение таблицы смещений

    int i = m - 1; // Индекс в тексте
    int j = m - 1; // Индекс в шаблоне

    // Поиск вхождений шаблона в текст
    while (i < n) {
        if (text[i] == pattern[j]) { // Если символы совпадают
            if (j == 0) { // Если мы дошли до начала шаблона, то мы нашли вхождение
                std::cout << "Pattern found at index " << i << std::endl; // Выводим индекс вхождения
                i += m; // Перемещаем индекс в тексте на длину шаблона
                j = m - 1; // Сбрасываем индекс в шаблоне
            } else {
                --i; // Перемещаемся к предыдущему символу в тексте
                --j; // Перемещаемся к предыдущему символу в шаблоне
            }
        } else {
            // Вычисляем смещение на основе таблицы смещений
            i += offsetTable[static_cast<int>(text[i])] < m - j ? m - j : offsetTable[static_cast<int>(text[i])];
            j = m - 1; // Сбрасываем индекс в шаблоне
        }
    }
}

int main() {
    std::ifstream file("hamlet.txt");
    if (!file.is_open()) { // Если файл не открылся, выводим сообщение об ошибке
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    std::string text;
    // Считываем содержимое файла в строку text
    while (std::getline(file, line)) {
        text += line + "\n";
    }
    file.close(); // Закрываем файл

    std::string pattern;
    std::cout << "Enter the pattern to search: ";
    std::cin >> pattern; // Запрашиваем у пользователя шаблон для поиска

    apostolicoCrochemore(text, pattern); // Вызываем функцию для поиска всех вхождений шаблона в текст

    return 0;
}
