#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Функция для вывода матрицы
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double elem : row) {
            cout << setw(10) << elem << " ";
        }
        cout << endl;
    }
}



int main() {
    setlocale(LC_ALL, "");
    int rows, cols;
    cout << "Введите количество строк и столбцов матрицы: ";
    cin >> rows >> cols;

    vector<vector<double>> matrix(rows, vector<double>(cols));
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix);

    int rank = gaussianElimination(matrix);

    cout << "Матрица после приведения к ступенчатому виду:" << endl;
    printMatrix(matrix);

    cout << "Ранг матрицы: " << rank << endl;

    return 0;
}