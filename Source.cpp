#include <iostream>
#include <iomanip> // ��� ������� setw
#include <stdexcept> // ��� ��������� ����������

using namespace std;

// ������� ��� ������ �������
void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// ������� ��� ���������� ������� � ������������ ���� (����� ������)
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

        // ������ ������� ������
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
        cout << "������� ���������� ����� � �������� �������: ";
        cin >> rows >> cols;

        if (rows <= 0 || cols <= 0) {
            throw invalid_argument("���������� ����� � �������� ������ ���� �������������.");
        }

        // ������� ������������ ��������� ������
        double** matrix = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new double[cols];
        }

        cout << "������� �������� ������� ���������:" << endl;
        for (int i = 0; i < rows; ++i) {
            cout << "������ " << i + 1 << ":\n";
            for (int j = 0; j < cols; ++j) {
                cout << "������� [" << i + 1 << "][" << j + 1 << "]: ";
                if (!(cin >> matrix[i][j])) {
                    throw runtime_error("������ �����. ����������, ������� ������ �������� ��������.");
                }
            }
        }

        cout << "�������� �������:" << endl;
        printMatrix(matrix, rows, cols);

        int rank = gaussianElimination(matrix, rows, cols);

        cout << "������� ����� ���������� � ������������ ����:" << endl;
        printMatrix(matrix, rows, cols);

        cout << "���� �������: " << rank << endl;

        // ����������� ������
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    catch (const exception& e) {
        cerr << "������: " << e.what() << endl;
        return 1;
    }

    return 0;
}
