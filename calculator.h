#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "matrix.h"

class CalculatorTools{
public:
    Matrix calcVal_;
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
    void ClearCalculator();
    void MultipyMatrices();
    void SubtractMatrices();
    void AddMatrices();
    void RowReduction();
    Matrix ReadMatrix();
    void Solve();
    double Determinant(Matrix m, int n);
    void FindDeterminant();
    void FindCofactor(Matrix x, Matrix &submatrix, int col, int n);
    QString DisplayMatrix(Matrix m);
};

#endif // CALCULATOR_H
