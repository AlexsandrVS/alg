#include <iostream>
#include <cstdlib>
#include <ctime>

void displayMenu() {
    std::cout << "Choose the method of filling the sequence:\n";
    std::cout << "1. Enter numbers manually\n";
    std::cout << "2. Random generation\n";
    std::cout << "3. Use predefined numbers\n";
    std::cout << "Your choice: ";
}

void processChoice(double r[], int n, int choice) {
    switch (choice) {
        case 1:
            std::cout << "Enter " << n << " real numbers:\n";
            for (int i = 0; i < n; ++i) {
                std::cout << "r" << i + 1 << ": ";
                std::cin >> r[i];
            }
            break;
        case 2:
            // Random generation
            std::cout << "Generating random numbers...\n";
            srand(time(0)); // Initialize random number generator
            for (int i = 0; i < n; ++i) {
                r[i] = (rand() % 1000) / 100.0; // Generate a random number in the range [0, 10)
            }
            break;
        case 3:
            double predefined[] = {1.2, -3.5, 0.8, 2.1, 4.5, -0.6, 7.2, 8.3, -2.0, 1.9, 3.4, 5.6, -4.3, 6.7, 9.0, 10.1};
            for (int i = 0; i < n; ++i) {
                r[i] = predefined[i];
            }
            break;
    }
}

int main() {
    const int n = 16;
    double r[n];

    int choice;
    displayMenu();
    std::cin >> choice;

    processChoice(r, n, choice);

    int count = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (r[i] > 0 && r[i + 1] > 0)
            count++;
    }

    std::cout << "Number of adjacent positive numbers: " << count << std::endl;
    return 0;
}
