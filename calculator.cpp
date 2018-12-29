#include <QtMath>
#include <QDebug>
#include <string>
#include <vector>
#include <iostream>
#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    connect(ui->solve, SIGNAL(released()), this, SLOT(Solve()));
    connect(ui->determinant, SIGNAL(released()), this, SLOT(FindDeterminant()));
}

Calculator::~Calculator()
{
    delete ui;
}

Matrix Calculator::ReadMatrix(){
    Matrix m1;
    QString text = ui->MatrixEntryWidget->toPlainText();
    qDebug() << "setting matrix";
    m1.CreateMatrix(text);
    ui->interpretedInput->setText(DisplayMatrix(m1));
    return m1;
}

// Returns the matrix as a string
QString Calculator::DisplayMatrix(Matrix m){
    QString displayText = "";
    for(int i = 0; i < m.getRow(); i++){
        displayText += "| ";
        for(int j = 0; j < m.getCol(); j++){
            displayText += QString::number(m.getElement(i, j)) + " ";
        }
        displayText += "|\n";
    }
    return displayText;
}

void Calculator::Solve(){
    qDebug() << "reading matrix in rowReduce";
    Matrix m1 = ReadMatrix();
    int maxRow = m1.getRow(), maxCol = m1.getCol();
    m1.printMatrix();
    int n = maxRow;

    // Check for correct matrix dimensions
    if(maxRow <= 1 || maxCol <= 1){
        ui->output->setText("Invalid Dimensions");
        return;
    }

    if(maxRow + 1 != maxCol){
        ui->output->setText("Matrix Must Be Size: N,N+1");
        return;
    }

        for (int i=0; i<n; i++) {

            // Search for maximum in this column
            double maxEl = m1.getElement(i,i);
            int maxRow = i;
            for (int k=i+1; k<n; k++) {
                if (m1.getElement(k, i) > maxEl) {
                    maxEl = m1.getElement(k,i);
                    maxRow = k;
                }
            }

            // Swap maximum row with current row (column by column)
            for (int k=i; k<n+1;k++) {
                double tmp = m1.getElement(maxRow, k);
                m1.getElement(maxRow, k) = m1.getElement(i, k);
                m1.getElement(i, k) = tmp;
            }

            // Make all rows below this one 0 in current column
            for (int k=i+1; k<n; k++) {
                double c = -m1.getElement(k, i) / m1.getElement(i, i);
                for (int j=i; j<n+1; j++) {
                    if (i==j) {
                        m1.getElement(k, j) = 0;
                    } else {
                        m1.getElement(k, j) += c * m1.getElement(i, j);
                    }
                }
            }
        }

            // Solve equation Ax=b
            std::vector<double> x(maxRow);
            for (int i=maxRow-1; i>=0; i--) {
                x[i] = m1.getElement(i, maxRow) / m1.getElement(i, i);
                for (int k=i-1;k>=0; k--) {
                    m1.getElement(k, maxRow) -= m1.getElement(k, i) * x[i];
                }
            }
            QString answer = "";
            for(int i = 0; i < maxRow; i++)
                answer += "x" + QString::number(i) + " = " + QString::number(x[i]) + "\n";
            ui->output->setText(answer);
}

void Calculator::FindDeterminant(){
    Matrix m1 = ReadMatrix();
    //Test for non square matrix
    if(m1.getCol() != m1.getRow()){
        ui->output->setText("Matrix Must Be NxN");
        return;
    }
    //Test for 1 by 1 matrix
    else if(m1.getCol() == 1){
        ui->output->setText(QString::number(m1.getElement(0, 0)));
        return;
    }
    qDebug() << "Inside FindDeterminant";
    int result = Determinant(m1, m1.getCol());
    ui->output->setText(QString::number(result));
}

double Calculator::Determinant(Matrix x, int n){
    qDebug() << "Inside Determinant";
    // Check if 2 by 2 matrix
    if(n == 2){
       return x.getElement(0,0) * x.getElement(1, 1) - x.getElement(1, 0) * x.getElement(0, 1);
    }
    double val = 0;
    Matrix submatrix(n, n);
    int sign = 1;

    for(int i = 0; i < n; i++){
        FindCofactor(x, submatrix, i, n);
        val += sign * x.getElement(0, i) * Determinant(submatrix, n-1);
        sign *= -1;
    }

    return val;
}

void Calculator::FindCofactor(Matrix x, Matrix &submatrix, int col, int n){
    qDebug() << "Inside FindCofactor";
    for(int r = 1; r < n; r++){
        int y = 0;
        for(int c = 0; c < n; c++){
            if(c != col){
            submatrix.getElement(r - 1, y++) = x.getElement(r, c);
            }
        }
    }
}

