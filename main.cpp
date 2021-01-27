#include <iostream>
#include <string>
#include <QApplication>

#include "include/indicators_view.h"
#include "include/matrix_multiplication.h"


const int N = 10;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    std::vector<std::shared_ptr<IComputation>> computations(N);
    for (int i = 0; i < N; ++i) {
        computations[i] = std::make_shared<MatrixMultiplication>(
                "Matrix mult. " + std::to_string(i+1), 1000, 1000
        );
    }

    IndicatorsMenu view(std::move(computations));
    view.show();

    return app.exec();
}
