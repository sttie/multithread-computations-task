#pragma once

#include <vector>
#include <string>

#include "computation.h"


class MatrixMultiplication : public IComputation {
private:
    std::vector<std::vector<int>> matrix1, matrix2;
    int n, m;

public:
    MatrixMultiplication(std::string id, int n_, int m_);
    void StartComputation() const override;
};
