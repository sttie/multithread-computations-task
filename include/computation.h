#pragma once

#include <QObject>
#include <string>


// Интерфейс объектов-вычислителей создан для того, чтобы можно было
// создать вычисления разного рода, не меняя изначальный код GUI
class IComputation : public QObject {
    Q_OBJECT

public:
    virtual void StartComputation() const = 0;

    std::string Id() const {
        return id;
    }

protected:
    IComputation(std::string id_) : id(std::move(id_)) { }

    mutable bool is_end = false;
    std::string id;


signals:
    // Сигнал, обновляющий QProgressBar
    void ComputationUpdate(int progress) const;
    /* Сигнал, оповещающий о завершении вычислений
       Можно было бы просто в конце дергать сигнал ComputationUpdate(100),
       но это недальновидно: GUI может потребоваться выполнять какие-то особые
       действия в ответ на заверешние вычислений, так что не будем обрекать себя на
       потенциальное изменение горы кода! */
    void ComputationFinished() const;

// Слот, введенный для того, чтобы исполняющий поток можно было в 
// любой момент отключить (т.к. потоки detach'атся)
public slots:
    void EndComputations() {
        is_end = true;
    }
};