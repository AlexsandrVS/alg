#include <iostream>
#include <vector>
#include <string>
#include <chrono>

class Matrix {
public:
    std::vector<std::vector<int>> data;
    std::string name;
    int rows;
    int cols;

    Matrix(int rows, int cols, std::string name) : rows(rows), cols(cols), name(name) {
        // Инициализация матрицы нулями
        data.resize(rows, std::vector<int>(cols, 0));
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), name(other.name) {
        // Копирование данных из другой матрицы
        data = other.data;
    }

    void printMatrix() const {
        std::cout << "Matrix " << name << ":\n";
        if ((rows < 15)&&(cols < 15)) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cout << data[i][j] << '\t';
                }
            std::cout << "\n";
            }
        } else {
            std::cout << "\nPrinting terminated! The matrix size is too large!\n";
        }
        
    }

    void randomizeMatrix() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = rand() % 201 - 100;
            }
        }
    }

    Matrix copyMatrix(std::string _name) const {
        // Создаем новый объект матрицы
        Matrix copiedMatrix(rows, cols, _name);

        // Копируем данные из текущей матрицы в новую
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                copiedMatrix.data[i][j] = data[i][j];
            }
        }

        return copiedMatrix;
    }

    // Метод сортировки выбором
    Matrix selectionSort() const {
        Matrix sortedMatrix(*this);

        for (int j = 0; j < sortedMatrix.cols; ++j) {
            if (j % 2 == 0) { // Четные столбцы: сортировка по убыванию
                for (int i = 0; i < sortedMatrix.rows - 1; ++i) {
                    int max_index = i;
                    for (int k = i + 1; k < sortedMatrix.rows; ++k) {
                        if (sortedMatrix.data[k][j] > sortedMatrix.data[max_index][j]) {
                            max_index = k;
                        }
                    }
                    if (max_index != i) {
                        int temp = sortedMatrix.data[i][j];
                        sortedMatrix.data[i][j] = sortedMatrix.data[max_index][j];
                        sortedMatrix.data[max_index][j] = temp;
                    }
                }
            } else { // Нечетные столбцы: сортировка по возрастанию
                for (int i = 0; i < sortedMatrix.rows - 1; ++i) {
                    int min_index = i;
                    for (int k = i + 1; k < sortedMatrix.rows; ++k) {
                        if (sortedMatrix.data[k][j] < sortedMatrix.data[min_index][j]) {
                            min_index = k;
                        }
                    }
                    if (min_index != i) {
                        int temp = sortedMatrix.data[i][j];
                        sortedMatrix.data[i][j] = sortedMatrix.data[min_index][j];
                        sortedMatrix.data[min_index][j] = temp;
                    }
                }
            }
        }
        return sortedMatrix;
    }

    // Метод сортировки LSD Radix
    Matrix lsdRadixSort() const {
        Matrix sortedMatrix(*this);

        // Для каждого столбца матрицы
        for (int j = 0; j < sortedMatrix.cols; ++j) {
            if (j % 2 == 0) { // Четные столбцы: сортировка по убыванию
                for (int i = 0; i < sortedMatrix.rows - 1; ++i) {
                    for (int k = 0; k < sortedMatrix.rows - i - 1; ++k) {
                        if (sortedMatrix.data[k][j] < sortedMatrix.data[k + 1][j]) {
                            // Обмен значениями
                            int temp = sortedMatrix.data[k][j];
                            sortedMatrix.data[k][j] = sortedMatrix.data[k + 1][j];
                            sortedMatrix.data[k + 1][j] = temp;
                        }
                    }
                }
            } else { // Нечетные столбцы: сортировка по возрастанию
                for (int i = 0; i < sortedMatrix.rows - 1; ++i) {
                    for (int k = 0; k < sortedMatrix.rows - i - 1; ++k) {
                        if (sortedMatrix.data[k][j] > sortedMatrix.data[k + 1][j]) {
                            // Обмен значениями
                            int temp = sortedMatrix.data[k][j];
                            sortedMatrix.data[k][j] = sortedMatrix.data[k + 1][j];
                            sortedMatrix.data[k + 1][j] = temp;
                        }
                    }
                }
            }
        }

        return sortedMatrix;
    }

    // Метод сортировки подсчетом
    Matrix countingSort() const {
        Matrix sortedMatrix(*this);

        for (int j = 0; j < sortedMatrix.cols; ++j) {
            // Создаем временный вектор для сортировки
            std::vector<int> count(201, 0);

            // Считаем количество элементов каждого значения
            for (int i = 0; i < sortedMatrix.rows; ++i) {
                count[sortedMatrix.data[i][j] + 100]++;
            }

            // Переписываем значения в исходный вектор
            int index = 0;
            if (j % 2 == 0) { // Четные столбцы: сортировка по убыванию
                for (int i = 200; i >= 0; --i) {
                    while (count[i] > 0) {
                        sortedMatrix.data[index][j] = i - 100;
                        ++index;
                        --count[i];
                    }
                }
            } else { // Нечетные столбцы: сортировка по возрастанию
                for (int i = 0; i <= 200; ++i) {
                    while (count[i] > 0) {
                        sortedMatrix.data[index][j] = i - 100;
                        ++index;
                        --count[i];
                    }
                }
            }
        }

        return sortedMatrix;
    }
};

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows and columns for the matrix: ";
        std::cin >> rows >> cols;

    // Создание матрицы с заданными размерами и инициализированной нулями
    Matrix originalMatrix(rows, cols, "originalMatrix");

    originalMatrix.randomizeMatrix();
    originalMatrix.printMatrix();

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Создание копии матрицы и сортировка копии с помощью LSD Radix
    std::cout << "\nSorted Matrix using LSD Radix Sort:\n";
    Matrix copiedMatrix = originalMatrix.copyMatrix("LSD Radix");
        auto start1 = std::chrono::high_resolution_clock::now();
    Matrix sortedLSDMatrix = copiedMatrix.lsdRadixSort();
        auto end1 = std::chrono::high_resolution_clock::now(); 
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1); 

    // Вывод отсортированной копии матрицы на экран
    sortedLSDMatrix.printMatrix();



    // Создание копии матрицы и сортировка копии с помощью Selection Sort
    std::cout << "\nSorted Matrix using Selection Sort:\n";
    copiedMatrix = originalMatrix.copyMatrix("Selection Sort");
        auto start2 = std::chrono::high_resolution_clock::now(); 
    Matrix sortedSelectionMatrix = copiedMatrix.selectionSort();
        auto end2 = std::chrono::high_resolution_clock::now(); 
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2); 

    // Вывод отсортированной копии матрицы на экран
    sortedSelectionMatrix.printMatrix();



    // Создание копии матрицы и сортировка копии с помощью Counting Sort
    std::cout << "\nSorted Matrix using Counting Sort:\n";
    copiedMatrix = originalMatrix.copyMatrix("Counting Sort");
        auto start3 = std::chrono::high_resolution_clock::now(); 
    Matrix sortedCountingMatrix = copiedMatrix.countingSort();
        auto end3 = std::chrono::high_resolution_clock::now(); 
        auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3); 

    // Вывод отсортированной копии матрицы на экран
    sortedCountingMatrix.printMatrix();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::cout << std::endl << std::endl;
        std::cout << "Selection sort took " << duration1.count() << " microseconds\n";
        std::cout << "LSD Radix sort took " << duration2.count() << " microseconds\n";
        std::cout << "Counting sort took  " << duration3.count() << " microseconds\n";

    return 0;
}
