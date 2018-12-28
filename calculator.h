#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "matrix.h"

class CalculatorTools{
public:
    double calcVal = 0.0; // TODO put in abstract class
    int currentOperation = -1;
};

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow, public CalculatorTools
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    Matrix ReadMatrix();
    void Solve();
};

#endif // CALCULATOR_H
