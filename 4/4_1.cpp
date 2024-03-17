#include <iostream>
#include <vector>
#include <chrono>

// Функция для сортировки выбором
void selectionSort(std::vector<int>& arr, int n, bool ascending) {
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
    // Вывод текущего состояния массива
        std::cout << "Selection Sort Step: ";
        for (int value : arr) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    // Если нужна обратная сортировка, разворачиваем массив
    if (!ascending) {
        for (int i = 0; i < n / 2; ++i) {
            std::swap(arr[i], arr[n - 1 - i]);
        }
    }
}

// Функция для сортировки подсчетом
void countSort(std::vector<int>& arr, int n, bool ascending) {
    // Находим максимальное и минимальное значения в массиве
    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }
    int range = maxVal - minVal + 1;

    // Инициализируем массивы подсчета и вывода
    std::vector<int> count(range), output(n);

    // Считаем количество каждого элемента в массиве
    for (int i = 0; i < n; ++i)
        ++count[arr[i] - minVal];

    // Рассчитываем накопленные суммы
    for (int i = 1; i < range; ++i)
        count[i] += count[i - 1];

    // Расставляем элементы в правильном порядке
    for (int i = n - 1; i >= 0; --i) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        --count[arr[i] - minVal];
        // Вывод текущего состояния массива
        std::cout << "Counting Sort Step: ";
        for (int j = 0; j < n; ++j) {
            std::cout << output[j] << " ";
        }
        std::cout << std::endl;
    }

    // Если нужна обратная сортировка, разворачиваем массив
    if (!ascending) {
        for (int i = 0; i < n / 2; ++i) {
            std::swap(output[i], output[n - 1 - i]);
        }
        for (int i = 0; i < n; ++i) arr[i] = output[i];
    } else {
        for (int i = 0; i < n; ++i) arr[n - 1 - i] = output[i];
    }
}


// Функция поразрядной сортировки
void radixSort(std::vector<std::vector<int>>& arr, int rows, int cols) {
    std::cout << "Поразрядная сортировка: " << std::endl;

    int maxVal = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maxVal = std::max(maxVal, arr[i][j]);
        }
    }

    int digitPosition = 1;
    while (maxVal / digitPosition > 0) {
        int digitCount[10] = {0};

        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows; ++i) {
                int digit = (arr[i][j] / digitPosition) % 10;
                ++digitCount[digit];
            }
        }

        for (int i = 1; i < 10; ++i)
            digitCount[i] += digitCount[i - 1];

        std::vector<int> output(rows * cols);

        for (int j = cols - 1; j >= 0; --j) {
            for (int i = rows - 1; i >= 0; --i) {
                int digit = (arr[i][j] / digitPosition) % 10;
                output[--digitCount[digit]] = arr[i][j];
            }
        }

        int index = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                arr[i][j] = output[index++];
            }
        }

        std::cout << "Сортировка по разряду " << digitPosition << ": ";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << arr[i][j] << " ";
            }
        }
        std::cout << std::endl;

        digitPosition *= 10;
    }
}

// Функция для вывода матрицы
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

    // Создаем исходный массив
    std::vector<std::vector<int>> originalArr(rows, std::vector<int>(cols));
    int count = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            originalArr[i][j] = rand() % 201 - 100;
        }
    }

    std::cout << "Original array: " << std::endl;
    printMatrix(originalArr);

    // Создаем буферный массив для сортировки подсчетом
    std::vector<std::vector<int>> countSortBuffer(cols, std::vector<int>(rows));
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            countSortBuffer[i][j] = originalArr[j][i];
        }
        countSort(countSortBuffer[i], rows, i % 2 == 0 ? false : true);
    }

    // Создаем буферный массив для поразрядной сортировки
    std::vector<std::vector<int>> radixSortBuffer(originalArr);

    // Создаем буферный массив для сортировки выбором
    std::vector<int> selectionSortBuffer(rows * cols);
    int index = 0;
    for (const auto& row : originalArr) {
        for (int value : row) {
            selectionSortBuffer[index++] = value;
        }
    }

    // Измеряем время сортировки подсчетом
    auto startCount = std::chrono::steady_clock::now();
    for (int i = 0; i < cols; ++i) {
        countSort(countSortBuffer[i], rows, i % 2 == 0 ? false : true);
    }
    auto endCount = std::chrono::steady_clock::now();

    // Измеряем время поразрядной сортировки
    auto startRadix = std::chrono::steady_clock::now();
    radixSort(radixSortBuffer, rows, cols);
    auto endRadix = std::chrono::steady_clock::now();

    // Измеряем время сортировки выбором
    auto startSelection = std::chrono::steady_clock::now();
    selectionSort(selectionSortBuffer, rows * cols, true);
    auto endSelection = std::chrono::steady_clock::now();

    // Выводим отсортированные массивы
    std::cout << "Array sorted by counting sort: " << std::endl;
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            std::cout << countSortBuffer[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Array sorted by radix sort: " << std::endl;
    printMatrix(radixSortBuffer);

    std::cout << "Array sorted by selection sort: " << std::endl;
    for (int value : selectionSortBuffer) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Выводим время выполнения сортировок
    std::cout << "Time taken by counting sort: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(endCount - startCount).count()
         << " milliseconds" << std::endl;
    std::cout << "Time taken by radix sort: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(endRadix - startRadix).count()
         << " milliseconds" << std::endl;
    std::cout << "Time taken by selection sort: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(endSelection - startSelection).count()
         << " milliseconds" << std::endl;

    return 0;
}
