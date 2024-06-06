#include <iostream>
#include <iomanip> // для функции setw
#include <stdexcept> // для обработки исключений

using namespace std;

// Функция для вывода матрицы
void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для приведения матрицы к ступенчатому виду (метод Гаусса)
int gaussianElimination(double** matrix, int rows, int cols) {
    int rank = 0;

    for (int col = 0; col < cols; ++col) {
        int pivot = rank;
        while (pivot < rows && matrix[pivot][col] == 0) {
            ++pivot;
        }

        if (pivot == rows) {
            continue;
        }

        // Меняем местами строки
        if (pivot != rank) {
            swap(matrix[rank], matrix[pivot]);
        }

        double pivotValue = matrix[rank][col];
        if (pivotValue == 0) {
            throw runtime_error("Pivot element is zero during normalization.");
        }

        for (int j = col; j < cols; ++j) {
            matrix[rank][j] /= pivotValue;
        }

        for (int i = rank + 1; i < rows; ++i) {
            double factor = matrix[i][col];
            for (int j = col; j < cols; ++j) {
                matrix[i][j] -= factor * matrix[rank][j];
            }
        }

        ++rank;
    }

    return rank;
}

int main() {
    try {
        int rows, cols;
        cout << "Введите количество строк и столбцов матрицы: ";
        cin >> rows >> cols;

        if (rows <= 0 || cols <= 0) {
            throw invalid_argument("Количество строк и столбцов должно быть положительным.");
        }

        // Создаем динамический двумерный массив
        double** matrix = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new double[cols];
        }

        cout << "Введите элементы матрицы построчно:" << endl;
        for (int i = 0; i < rows; ++i) {
            cout << "Строка " << i + 1 << ":\n";
            for (int j = 0; j < cols; ++j) {
                cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
                if (!(cin >> matrix[i][j])) {
                    throw runtime_error("Ошибка ввода. Пожалуйста, вводите только числовые значения.");
                }
            }
        }

        cout << "Исходная матрица:" << endl;
        printMatrix(matrix, rows, cols);

        int rank = gaussianElimination(matrix, rows, cols);

        cout << "Матрица после приведения к ступенчатому виду:" << endl;
        printMatrix(matrix, rows, cols);

        cout << "Ранг матрицы: " << rank << endl;

        // Освобождаем память
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
