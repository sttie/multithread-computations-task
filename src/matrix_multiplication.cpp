#include <random>
#include <vector>
#include <string>

#include "../include/matrix_multiplication.h"


// В конструкторе генерируем 2 матрицы n x m
MatrixMultiplication::MatrixMultiplication(
        std::string id, int n_, int m_
) : IComputation(std::move(id)), n(n_), m(m_) {
    matrix1.resize(n);
    
    // Заполнение матриц рандомными числами
    // rand() - это, скорее, С, а не С++, но здесь я не хотел
    // загрязнять код созданием объектов-генераторов, да и "хорошая"
    // рандомность здесь совсем не нужна
    for (int i = 0; i < n; ++i) {
        matrix1[i].resize(m);
        for (int j = 0; j < m; ++j) {
            matrix1[i][j] = rand() % 100;
        }
    }
    matrix2.resize(m);
    for (int i = 0; i < m; ++i) {
        matrix2[i].resize(n);
        for (int j = 0; j < n; ++j) {
            matrix2[i][j] = rand() % 100;
        }
    }
}

// Непосредственно вычисление произведения двух матриц
void MatrixMultiplication::StartComputation() const  {
    std::vector<std::vector<int>> result(n);
    for (int i = 0; i < n; ++i) {
        result[i].resize(n);
    }

    float progress = 100.0f / n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                if (is_end) return;
                result[i][j] = matrix1[i][k] * matrix2[k][j];
            }
        }

        progress += 100.0f / n;
        emit ComputationUpdate(static_cast<int>(progress));
    }

    is_end = true;
    emit ComputationFinished();
}