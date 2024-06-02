#include <iostream>
#include <vector>

using namespace std;

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

//TODO: unit test required for this method
int determinant(vector<vector<int>> a, int n, int p) {
    int det = 1;
    for (int i = 0; i < n; i++) {
        if (a[i][i] == 0) {
            int j = i + 1;
            while (j < n && a[j][i] == 0)
                j++;
            if (j == n) {
                det = 0;
                break;
            }
            swap(a[i], a[j]);
            det = (det * -1 + p) % p;
        }
        det = (det * a[i][i]) % p;
        int inv = modInverse(a[i][i], p);
        for (int j = i + 1; j < n; j++) {
            int factor = (a[j][i] * inv) % p;
            for (int k = i; k < n; k++) {
                a[j][k] = (a[j][k] - factor * a[i][k] % p + p) % p;
            }
        }
    }
    return det;
}

void printMatrix(const vector<vector<int>> &matrix, int n) {
    int mid = n; // Die Mitte der erweiterten Matrix, um die | zu setzen
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (j == mid) {
                cout << " | ";
            }
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

vector<vector<int>> inverse(vector<vector<int>> matrix, int n, int p) {
    vector<vector<int>> augmentedMatrix(n, vector<int>(2 * n));

    // Erstellt: (Originalmatrix | Einheitsmatrix)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = matrix[i][j];
            augmentedMatrix[i][j + n] = (i == j) ? 1 : 0;
        }
    }

    cout << "Erweiterte Matrix initial:\n";
    printMatrix(augmentedMatrix, n);

    // Gauss-Jordan-Elimination
    for (int i = 0; i < n; i++) {
        // Suche nach einer Nicht-Null-Leitungszahl in der Spalte i
        int pivotRow = i;
        while (pivotRow < n && augmentedMatrix[pivotRow][i] == 0) {
            pivotRow++;
        }
        if (pivotRow == n) {
            continue; // Keine Inverse möglich, wenn ganze Spalte Null ist
        }

        // Vertausche die aktuelle Zeile mit der Pivot-Zeile
        if (pivotRow != i) {
            swap(augmentedMatrix[i], augmentedMatrix[pivotRow]);
            cout << "Nach Vertauschung von Zeile " << i + 1 << " mit Zeile " << pivotRow + 1 << ":\n";
            printMatrix(augmentedMatrix, n);
        }

        int inv = modInverse(augmentedMatrix[i][i], p);
        // Skalieren der Pivot-Zeile
        for (int j = 0; j < 2 * n; j++) {
            augmentedMatrix[i][j] = (augmentedMatrix[i][j] * inv) % p;
        }
        cout << "Nach Skalierung der Zeile " << i + 1 << ":\n";
        printMatrix(augmentedMatrix, n);

        // Eliminiere die aktuelle Spalte in allen anderen Zeilen
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int factor = augmentedMatrix[j][i];
                for (int k = 0; k < 2 * n; k++) {
                    augmentedMatrix[j][k] = (augmentedMatrix[j][k] - factor * augmentedMatrix[i][k] % p + p) % p;
                }
                cout << "Nach Eliminierung von Zeile " << i + 1 << " in Zeile " << j + 1 << ":\n";
                printMatrix(augmentedMatrix, n);
            }
        }
    }

    // Extrahiere die Inverse aus der erweiterten Matrix
    vector<vector<int>> inverseMatrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverseMatrix[i][j] = augmentedMatrix[i][j + n];
        }
    }

    return inverseMatrix;
}

int main() {
    int N, p;
    cout << "Dimension der Matrix: ";
    cin >> N;
    cout << "Primzahl: ";
    cin >> p;

    vector<vector<int>> matrix(N, vector<int>(N));
    cout << "Elemente der Matrix:\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> matrix[i][j];
    vector<vector<int>> originalMatrix = matrix;

    //TODO: unchecked
    /*int det = determinant(matrix, N, p);
    if (det == 0) {
        cout << "Die Matrix ist nicht invertierbar.\n";
        getchar();
        return 0;
    }*/

    vector<vector<int>> invMatrix = inverse(matrix, N, p);
    cout << "Die eingegebene Matrix ist:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << originalMatrix[i][j] << " ";
        cout << "\n";
    }
    cout << "Die invertierte Matrix ist:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << invMatrix[i][j] << " ";
        cout << "\n";
    }
    system("pause");
    return 0;
}