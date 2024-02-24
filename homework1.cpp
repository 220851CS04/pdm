#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 1e-10;

void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

bool isSingular(const vector<vector<double>>& matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size() - 1;

    for (int i = 0; i < numRows; i++) {
        if (abs(matrix[i][i]) < EPSILON) {
            return true;
        }
    }
    return false;
}

void gaussianElimination(vector<vector<double>>& matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size() - 1;

    for (int i = 0; i < numRows; i++) {
        int pivotRow = i;
        for (int k = i + 1; k < numRows; k++) {
            if (abs(matrix[k][i]) > abs(matrix[pivotRow][i])) {
                pivotRow = k;
            }
        }
        swap(matrix[i], matrix[pivotRow]);

        double pivotElement = matrix[i][i];
        if (abs(pivotElement) < EPSILON) {
       
            cerr << "Error: Singular matrix encountered. Gaussian elimination is not applicable." << endl;
            exit(EXIT_FAILURE);
        }

        for (int j = i; j <= numCols; j++) {
            matrix[i][j] /= pivotElement;
        }

        for (int k = 0; k < numRows; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = i; j <= numCols; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }
}

int main() {
    int numRows, numCols;

    cout << "Enter the number of rows and columns: ";
    cin >> numRows >> numCols;

    vector<vector<double>> matrix(numRows, vector<double>(numCols + 1));

    cout << "Enter the augmented matrix:" << endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j <= numCols; j++) {
            cin >> matrix[i][j];
        }
    }

    cout << "Original Matrix:" << endl;
    printMatrix(matrix);

    if (isSingular(matrix)) {
        cerr << "Error: Singular matrix encountered. Gaussian elimination is not applicable." << endl;
        return EXIT_FAILURE;
    }

    gaussianElimination(matrix);

    cout << "\nMatrix after Gaussian Elimination:" << endl;
    printMatrix(matrix);

    cout << "\nSolution:" << endl;
    for (int i = 0; i < numRows; i++) {
        cout << "x" << i + 1 << " = " << matrix[i][numCols] << endl;
    }

    return 0;
}
