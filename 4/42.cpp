#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void generateRandomMatrix(std::vector<std::vector<int>>& arr, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = rand() % 201 - 100; // Генерация случайного числа от -100 до 100
        }
    }
}

void customSort(std::vector<int>& arr, bool ascending) {
    if (ascending)
        std::sort(arr.begin(), arr.end());
    else
        std::sort(arr.rbegin(), arr.rend());
}

void selectionSort(std::vector<int>& arr, bool ascending) {
    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t index = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if ((arr[j] < arr[index]) == ascending)
                index = j;
        }
        std::swap(arr[i], arr[index]);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Selection sort took " << elapsed_seconds.count() << " seconds." << std::endl;
}

void countSort(std::vector<int>& arr, bool ascending) {
    auto start = std::chrono::steady_clock::now();
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int minVal = *std::min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    std::vector<int> count(range), output(arr.size());

    for (int i = 0; i < arr.size(); ++i)
        ++count[arr[i] - minVal];

    for (int i = 1; i < range; ++i)
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        --count[arr[i] - minVal];
    }

    if (!ascending) {
        for (size_t i = 0; i < arr.size(); ++i)
            arr[i] = output[i];
    } else {
        for (size_t i = 0; i < arr.size(); ++i)
            arr[arr.size() - 1 - i] = output[i];
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Count sort took " << elapsed_seconds.count() << " seconds." << std::endl;
}

void radixSort(std::vector<std::vector<int>>& arr, int rows, int cols) {
    auto start = std::chrono::steady_clock::now();
    int maxVal = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            maxVal = std::max(maxVal, arr[i][j]);

    int digitPosition = 1;
    while (maxVal / digitPosition > 0) {
        int digitCount[10] = {0};

        for (int j = 0; j < cols; ++j)
            for (int i = 0; i < rows; ++i)
                ++digitCount[(arr[i][j] / digitPosition) % 10];

        for (int i = 1; i < 10; ++i)
            digitCount[i] += digitCount[i - 1];

        std::vector<std::vector<int>> output(rows, std::vector<int>(cols));

        for (int j = cols - 1; j >= 0; --j)
            for (int i = rows - 1; i >= 0; --i)
                output[--digitCount[(arr[i][j] / digitPosition) % 10]][j] = arr[i][j];

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                arr[i][j] = output[i][j];

        digitPosition *= 10;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Radix sort took " << elapsed_seconds.count() << " seconds." << std::endl;
}

void printMatrix(const std::vector<std::vector<int>>& arr) {
    for (const auto& row : arr) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;

    std::vector<std::vector<int>> originalArr(rows, std::vector<int>(cols));

    generateRandomMatrix(originalArr, rows, cols);

    std::cout << "Original array: " << std::endl;
    printMatrix(originalArr);

    std::vector<std::vector<int>> countSortBuffer(cols, std::vector<int>(rows));
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            countSortBuffer[i][j] = originalArr[j][i];
        }
        countSort(countSortBuffer[i], i % 2 == 0);
    }

    std::vector<std::vector<int>> radixSortBuffer(originalArr);
    radixSort(radixSortBuffer, rows, cols);

    std::vector<int> selectionSortBuffer(rows * cols);
    size_t index = 0;
    for (const auto& row : originalArr) {
        for (int value : row) {
            selectionSortBuffer[index++] = value;
        }
    }
    selectionSort(selectionSortBuffer, true);

    return 0;
}
