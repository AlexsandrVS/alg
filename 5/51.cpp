#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void buildOffsetTable(const std::string& pattern, std::vector<int>& offsetTable) {
    int m = pattern.size();
    offsetTable.resize(256, m);

    for (int i = 0; i < m - 1; ++i) {
        offsetTable[static_cast<int>(pattern[i])] = m - 1 - i;
    }
}

void apostolicoCrochemore(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> offsetTable;
    buildOffsetTable(pattern, offsetTable);
    
    int i = m - 1;
    int j = m - 1;

    while (i < n) {
        if (text[i] == pattern[j]) {
            if (j == 0) {
                std::cout << "Pattern found at index " << i << std::endl;
                i += m;
                j = m - 1;
            } else {
                --i;
                --j;
            }
        } else {
            i += offsetTable[static_cast<int>(text[i])] < m - j ? m - j : offsetTable[static_cast<int>(text[i])];
            j = m - 1;
        }
    }
}

int main() {
    std::ifstream file("hamlet.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    std::string text;
    while (std::getline(file, line)) {
        text += line + "\n";
    }
    file.close();

    std::string pattern;
    std::cout << "Enter the pattern to search: ";
    std::cin >> pattern;

    apostolicoCrochemore(text, pattern);

    return 0;
}
