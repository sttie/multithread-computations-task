#include "../include/indicators_view.h"

#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <thread>


IndicatorsMenu::IndicatorsMenu(
    std::vector<ComputationPtr> computations_, QWidget* parent
) : QMainWindow(parent), computations(std::move(computations_)) {
    InitUI();
}

IndicatorsMenu::~IndicatorsMenu() {
    // Насильно завершаем потоки с вычислениями
    emit KillComputationThreads();
    delete start_button;
}

void IndicatorsMenu::InitUI() {
    auto table_layout = new QVBoxLayout;

    start_button = new QPushButton("Начать вычисления");
    connect(start_button, &QPushButton::clicked,
            this, &IndicatorsMenu::StartComputations);
    table_layout->addWidget(start_button);

    // Для каждого объекта-вычислителя создаем отдельный горизонтальный слой
    // и настраиваем его
    for (const auto& computation : computations) {
        auto horizontal = new QHBoxLayout;

        auto progress_bar = new QProgressBar;
        progress_bar->setRange(0, 100);
        connect(computation.get(), &IComputation::ComputationUpdate, 
                progress_bar, &QProgressBar::setValue);
        connect(computation.get(), &IComputation::ComputationFinished, 
                [progress_bar]() { progress_bar->setValue(100); });
        connect(this, &IndicatorsMenu::KillComputationThreads, 
                computation.get(), &IComputation::EndComputations);

        auto progress_id = new QLabel(QString::fromStdString(computation->Id()));
        progress_id->setAlignment(Qt::AlignLeft);
        progress_id->setFixedSize(120, 15);

        horizontal->addWidget(progress_bar);
        horizontal->addWidget(progress_id);
        horizontal->setContentsMargins(5, 5, 5, 0);
        horizontal->setSpacing(10);

        table_layout->addLayout(horizontal);
    }

    auto central_widget = new QWidget;
    central_widget->setLayout(table_layout);
    setCentralWidget(central_widget);
    setMinimumSize(600, 600);
}

// Функция создает для каждого объекта-вычислителя свой поток,
// запускает их и сразу же открепляет
void IndicatorsMenu::StartComputations() {
    for (auto& computation : computations) {
        std::thread t(std::thread(&IComputation::StartComputation, computation));
        t.detach();
    }

    // Кнопка "Начать вычисления" больше не может быть использована => отключаем сигнал
    disconnect(start_button, &QPushButton::clicked, nullptr, nullptr);
}