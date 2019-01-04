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
    connect(ui->row_reduction, SIGNAL(released()), this, SLOT(FindRowReduction()));
    connect(ui->add, SIGNAL(released()), this, SLOT(AddMatrices()));
    connect(ui->subtract, SIGNAL(released()), this, SLOT(SubtractMatrices()));
    connect(ui->mult, SIGNAL(released()), this, SLOT(MultipyMatrices()));
    connect(ui->clear, SIGNAL(released()), this, SLOT(ClearCalculator()));
}

Calculator::~Calculator()
{
    delete ui;
}

Matrix Calculator::ReadMatrix(){
    Matrix m1;
    QString text = ui->MatrixEntryWidget->toPlainText();
    m1.CreateMatrix(text);
    ui->interpretedInput->setText(DisplayMatrix(m1));
    return m1;
}

// Returns the matrix as a string
QString Calculator::DisplayMatrix(Matrix m){
    QString displayText = "";
    for(int i = 0; i < m.getRows(); i++){
        displayText += "| ";
        for(int j = 0; j < m.getCols(); j++){
            displayText += QString::number(m.at(i, j)) + " ";
        }
        displayText += "|\n";
    }
    return displayText;
}

void Calculator::AddMatrices(){
    Matrix m1 = ReadMatrix();
    if(calcVal_.getRows() == -1 &&  calcVal_.getCols() == -1){
        calcVal_ = m1;
        ui->output->setText(DisplayMatrix(calcVal_));
    }
    else if(calcVal_.getCols() == m1.getCols() && calcVal_.getRows() == m1.getRows()){
        calcVal_ += m1;
        ui->output->setText(DisplayMatrix(calcVal_));
    }
    else
        ui->output->setText("Matrices Must Be The Same Size");
}

void Calculator::SubtractMatrices(){
    Matrix m1 = ReadMatrix();
    if(calcVal_.getRows() == -1 &&  calcVal_.getCols() == -1){
        calcVal_ = m1;
        ui->output->setText(DisplayMatrix(calcVal_));
    }
    else if(calcVal_.getCols() == m1.getCols() && calcVal_.getRows() == m1.getRows()){
        calcVal_ -= m1;
        ui->output->setText(DisplayMatrix(calcVal_));
    }
    else
        ui->output->setText("Matrices Must Be The Same Size");
}

void Calculator::MultipyMatrices(){
    Matrix m1 = ReadMatrix();
    if(calcVal_.getRows() == -1 &&  calcVal_.getCols() == -1){
        calcVal_ = m1;
        ui->output->setText(DisplayMatrix(calcVal_));
    }
    else if(calcVal_.getRows() == m1.getCols()){
        calcVal_ *= m1;
        ui->output->setText(DisplayMatrix(calcVal_));
    }
    else
        ui->output->setText("# Columns In The First Matrix Must Equal # Rows in The Second");
}

void Calculator::FindRowReduction(){
    Matrix m1 = ReadMatrix();
    m1.RowReduction();
    ui->output->setText(DisplayMatrix(m1));
}

void Calculator::Solve(){
    Matrix m1 = ReadMatrix();
    int maxRow = m1.getRows(), maxCol = m1.getCols();
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
        double maxEl = m1.at(i,i);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (m1.at(k, i) > maxEl) {
                maxEl = m1.at(k,i);
                maxRow = k;
            }
        }
        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double tmp = m1.at(maxRow, k);
            m1.at(maxRow, k) = m1.at(i, k);
            m1.at(i, k) = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -m1.at(k, i) / m1.at(i, i);
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    m1.at(k, j) = 0;
                } else {
                    m1.at(k, j) += c * m1.at(i, j);
                }
            }
        }
    }
     // Solve equation Ax=b
     std::vector<double> x(maxRow);
     for (int i=maxRow-1; i>=0; i--) {
         x[i] = m1.at(i, maxRow) / m1.at(i, i);
         for (int k=i-1;k>=0; k--) {
             m1.at(k, maxRow) -= m1.at(k, i) * x[i];
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
    if(m1.getCols() != m1.getRows()){
        ui->output->setText("Matrix Must Be NxN");
        return;
    }
    //Test for 1 by 1 matrix
    else if(m1.getCols() == 1){
        ui->output->setText(QString::number(m1.at(0, 0)));
        return;
    }
    int result = Determinant(m1, m1.getCols());//m1.Determinant(m1.getRows());
    ui->output->setText(QString::number(result));
}

double Calculator::Determinant(Matrix x, int n){
    // Check if 2 by 2 matrix
    if(n == 2){
       return x.at(0,0) * x.at(1, 1) - x.at(1, 0) * x.at(0, 1);
    }
    double val = 0;
    Matrix submatrix(n, n);
    int sign = 1;

    for(int i = 0; i < n; i++){
        FindCofactor(x, submatrix, i, n);
        val += sign * x.at(0, i) * Determinant(submatrix, n-1);
        sign *= -1;
    }

    return val;
}

void Calculator::FindCofactor(Matrix x, Matrix &submatrix, int col, int n){
    for(int r = 1; r < n; r++){
        int y = 0;
        for(int c = 0; c < n; c++){
            if(c != col){
                submatrix.at(r - 1, y++) = x.at(r, c);
            }
        }
    }
}

void Calculator::ClearCalculator(){
    calcVal_.clear();
    ui->interpretedInput->setText("");
    ui->output->setText("");
    ui->MatrixEntryWidget->setText("");
}

