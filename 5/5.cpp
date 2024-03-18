#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

/*
    int findMax() {
    int num;
    cin >> num;
    
    if (num == 0) {
        return 0;
    } else {
        int max_rest = findMax();
        return (num > max_rest) ? num : max_rest;
    }
}
*/

void generateSequence(std::vector<int>& sequence, int length) {
    srand(time(NULL));
    for (int i = 0; i < length - 1; ++i) {
        int num = rand() % 100;  // Генерация чисел в диапазоне от 0 до 99
        sequence.push_back(num);
        std::cout << num << std::endl;
    }
    std::cout << "0" << std::endl;  // Завершающий 0
}

int findMax(const std::vector<int>& sequence, int index) {
    if (index == sequence.size()) {
        return 0;
    } else {
        int num = sequence[index];
        int max_rest = findMax(sequence, index + 1);
        return (num > max_rest) ? num : max_rest;
    }
}

int main() {
    std::cout << "Enter the length of the sequence of natural numbers (ending with zero): ";
    int length;
    std::cin >> length;

    std::vector<int> sequence;
    generateSequence(sequence, length);

    int max_num = findMax(sequence, 0);
    std::cout << "The maximum value in the sequence: " << max_num << std::endl;
    
    return 0;
}
