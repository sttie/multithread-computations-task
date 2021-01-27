#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <memory>

#include "computation.h"


class IndicatorsMenu : public QMainWindow {
    Q_OBJECT

    using ComputationPtr = std::shared_ptr<IComputation>;

public:
    IndicatorsMenu(std::vector<ComputationPtr> computations, QWidget* parent = nullptr);
    ~IndicatorsMenu();

private:
    void InitUI();
    void StartComputations();

    QPushButton* start_button;
    std::vector<ComputationPtr> computations;

signals:
    void KillComputationThreads();
};