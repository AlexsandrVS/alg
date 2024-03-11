#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Matrix {
private:
    std::string name;
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

public:
    // Constructor to initialize the matrix with given dimensions
    Matrix(std::string _name, int _rows, int _cols) 
    : name(_name), rows(_rows), cols(_cols), 
    data(_rows, std::vector<double>(_cols, 0.0)) {}

    // Function to create a matrix based on the given formula
    void createMatrix() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = ((i + j) * sin(i)) / cos(j);
            }
        }
    }

    // Function to create a matrix where each row contains a sequence from 1 to n
    void createMatrixWhereEachRowInSimpleSequence1toN() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = j + 1; // Adding 1 to the index to start numbers from 1 instead of 0
            }
        }
    }

    // Function to swap specified elements in the matrix
    void swapElements(int row1, int col1, int row2, int col2) {
        std::swap(data[row1][col1], data[row2][col2]);
    }

    // Function to sort elements in each row of the matrix in descending order
    void sortRowsDescending() {
        for (auto& row : data) {
            std::sort(row.begin(), row.end(), std::greater<double>()); // Sort the row in descending order
        }
    }

    // Function to check if two matrices can be multiplied
    bool canMultiply(const Matrix& other) const {
        return cols == other.rows;
    }

    // Function to multiply two matrixes
    Matrix multiply(const Matrix& other , std::string _name) const {
        if (!canMultiply(other)) {
            std::cerr << "Error: Matrices cannot be multiplied. Number of columns in first matrix must be equal to number of rows in second matrix." << std::endl;
            return Matrix("Error", 0, 0);
        }

        Matrix result(_name, rows, other.cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    // Function to copy the matrix
    Matrix copy(std::string _name) const {
        Matrix copyMatrix(_name, rows, cols);
        copyMatrix.data = data;
        return copyMatrix;
    }

    // Function to swap specified elements in matrix E
    void swapElementsInMatrixE(Matrix& E, int m, int n) {

        for (int i = 0; i < (int)(m / 3); i++)
        {
            for (int j = 0; j < (int)(n / 3); j++)
            {
                E.swapElements(i, (int)(n-(j+1)), (int)(n-(j+1)), i);
            }
        }
        
        // E.swapElements(0, 5, 5, 0); // Swap elements (1, 6) and (6, 1)
        // E.swapElements(0, 4, 4, 0); // Swap elements (1, 5) and (5, 1)
        // E.swapElements(1, 4, 4, 1); // Swap elements (2, 5) and (5, 2)
        // E.swapElements(1, 5, 5, 1); // Swap elements (2, 6) and (6, 2)
    }

    // Function to count positive elements on the main diagonal and print matrix info
    void countPositiveDiagonalElements() const {
        std::cout << "\nMatrix " << name << " (" << rows << "x" << cols << "):" << std::endl;
        std::cout << "Elements on the main diagonal:" << std::endl;
        int count = 0;
        for (int i = 0; i < std::min(rows, cols); ++i) {
            std::cout << data[i][i] << " ";
            if (data[i][i] >= 0) {
                ++count;
            }
        }
        std::cout << std::endl;
        std::cout << "Number of positive elements on the main diagonal: " << count << std::endl;
    }


    // Function to print the matrix
    void printMatrix() const {
        std::cout << "\nMatrix " << name << " (" << rows << "x" << cols << "):" << std::endl;
        for (const auto& row : data) {
            for (double element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    const int m = 6; const int n = m;

    // Create matrix A with user input
    Matrix A("A", m, n);
    A.createMatrix(); // Fill matrix A with values based on the formula

    // Print matrix A
    A.printMatrix();

    // Copy matrix A to matrix B
    Matrix B = A.copy("B");

    // Sort elements in each row of matrix B in descending order
    B.sortRowsDescending();
    // Print matrix B with sorted rows
    B.printMatrix();

    Matrix C("C", m, n);
    C.createMatrixWhereEachRowInSimpleSequence1toN();

    // Print matrix C
    C.printMatrix();

    // Multiply matrices B and C if possible
    // if (B.canMultiply(C)) {
    //     Matrix D = B.multiply(C, "D");
    //     // Print matrix D
    //     D.printMatrix();
    // }

    Matrix D = B.multiply(C, "D");
    // Print matrix D
    D.printMatrix();

    // Create matrix E as a copy of matrix B
    Matrix E = D.copy("E");

    // Swap [2*2] elements in diagonal matrix E
    E.swapElementsInMatrixE(E, m, n);

    // Print matrix E with swapped elements
    E.printMatrix();

    // Count positive elements on the main diagonal of matrix E and print matrix info
    E.countPositiveDiagonalElements();

    return 0;
}
