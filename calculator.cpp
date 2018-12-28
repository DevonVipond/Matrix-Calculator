#include <QtMath>
#include <QDebug>
#include <string>
#include <vector>
#include <iostream>
#include "calculator.h"
#include "ui_calculator.h"
//TODO
// ensure all rows and cols same size
// determinant, row reduce, inverse

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
   /* QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++){
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }*/
    connect(ui->solve, SIGNAL(released()), this, SLOT(Solve()));
}

Calculator::~Calculator()
{
    delete ui;
}

QString DisplayMatrix(Matrix m1){
    qDebug() << "displaying matrix";
    QString displayText = "";
    for(int i = 0; i < m1.getRow(); i++){
        displayText += "|";
        for(int j = 0; j < m1.getCol(); j++){
            displayText += m1.getElement(i,j);
            displayText += " ";
        }
        displayText += "|\n";
    }
    return displayText;
}

QString DisplayMatrixFromDouble(Matrix m1, int maxRow, int maxCol){
    QString displayText = "";
    //qDebug() << m1.getRow() << endl << m1.getCol();
    for(int i = 0; i < maxRow; i++){
        displayText += "| ";
        for(int j = 0; j < maxCol; j++){
            //qDebug() << m1.getElement(i, j);
            displayText += QString::number(m1.getElement(i, j)) + " ";
        }
        displayText += "|\n";
    }
    return displayText;
}

Matrix Calculator::ReadMatrix(){
    Matrix m1;
    QString text = ui->MatrixEntryWidget->toPlainText();
    qDebug() << "setting matrix";
    //m1.createMatrix(text);
    m1.createMatrixAsDouble(text);
    ui->interpretedInput->setText(DisplayMatrixFromDouble(m1, m1.getRow(), m1.getCol()));
    return m1;
}
void printMatrix(Matrix m1, int maxRow, int maxCol){ //move into matrix class
    for(int row = 0; row < maxRow; row++){
        //QString temp = "";
        for(int col = 0; col < maxCol; col++){
            //temp += QChar(m1[row][col]);
            qDebug() << m1.getElement(row, col);
        }
        qDebug() << "\n";
    }
}
void swap_row(double **m1, int col, int maxElement, int maxRow, int maxCol){
    for (int k = col; k< maxCol; k++) {
        qDebug() << "begin";
        double tmp = m1[maxElement][k];
        qDebug() << "one";
        m1[maxElement][k] = m1[col][k];//m1[col][k];
        qDebug() << "two";
        m1[col][k] = tmp;
        qDebug() << "three";
    }
}

//TODO
// case if singular matrix
// make sure other operations test for square matrix
void Calculator::Solve(){
    qDebug() << "reading matrix in rowReduce";
    Matrix m1 = ReadMatrix();
    qDebug() << "in RowReduce";
   // double ** m1 = m.getMatrixAsInteger();
    int maxRow = m1.getRow(), maxCol = m1.getCol();
    qDebug() << "printing Matrix";
    printMatrix(m1, maxRow, maxCol);
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

            qDebug() << "matrix before swapping";
            printMatrix(m1, maxRow, maxCol);

            // Swap maximum row with current row (column by column)
            for (int k=i; k<n+1;k++) {
                double tmp = m1.getElement(maxRow, k);
                m1.getElement(maxRow, k) = m1.getElement(i, k);
                m1.getElement(i, k) = tmp;
            }

            qDebug() << "matrix before setting rows to 0";
            printMatrix(m1, maxRow, maxCol);

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
            qDebug() << "matrix before solving";
            printMatrix(m1, maxRow, maxCol);

            // Solve equation Ax=b for an upper triangular matrix A
            std::vector<double> x(maxRow);
            for (int i=maxRow-1; i>=0; i--) {
                x[i] = m1.getElement(i, maxRow) / m1.getElement(i, i);
                for (int k=i-1;k>=0; k--) {
                    m1.getElement(k, maxRow) -= m1.getElement(k, i) * x[i];
                }
            }
            qDebug() << "ANSWERS: ";
            QString answer = "";
            for(int i = 0; i < maxRow; i++)
                answer += "x" + QString::number(i) + " = " + QString::number(x[i]) + "\n";
            ui->output->setText(answer);




//1,2,3;4,5,6;7,8,9;

    /*for(int col = 0; col < maxRow; col++){ //less than maxCol also?
        qDebug() << "Fiding max in col";

        // Find maximum in this column
        int maxElement = 0;
        for(int row = col + 1; row < maxRow; row++){
            maxElement = m1[maxElement][col] > m1[row][col] ? maxElement : row;
        }
        qDebug() << "swapping rows";

        // Swap max row and current row
        qDebug() << maxElement;
        swap_row(m1, col, maxElement, maxRow, maxCol);
        qDebug() << "setting rows in col to 0";

        // Set all rows below max in current column to 0
        for (int row=col+1; row< maxRow; row++) {
             double temp = m1[row][col] / m1[col][col];
             m1[row][col] = 0;
             for(int col = col + 1; col < maxCol; col++){
                 m1[row][col] -= temp * m1[col][col];
             }
          }
        printMatrix(m1, maxRow, maxCol);
    }

    // Solve matrix
    //std::vector<int> x(maxRow - 1);
    double *x = new double[maxRow - 1];
    for (int row = maxRow - 1; row >= 0; row--) {
        double x1 = m1[row][maxRow - 1], x2 =  m1[row][row];
        x[row] = x1 / x2;
        qDebug() << "ans:";
        qDebug() << x[row];
        for (int k = row - 1; k >= 0; k--) {
            m1[k][maxRow - 1] -= m1[k][row] * x[row];
        }
    }*/
    //qDebug() << "printing matrix";
    //printMatrix(m1, maxRow, maxCol);

}

/*void Calculator::Determinant(){

}
*/
