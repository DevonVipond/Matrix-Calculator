#ifndef MATRIX_H
#define MATRIX_H

#endif // MATRIX_H

#include "QString"

class Matrix{
private:
    int row_, col_;
    double** x_;
public:
    Matrix():row_(-1),col_(-1){}
    Matrix(int r, int c);
    Matrix(int r, int c, int val);

    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator=(const Matrix& rhs);
    Matrix  operator*(const Matrix& rhs);
    Matrix& operator*=(const Matrix& rhs);

    double& at(int row, int col);
    double& at(int row, int col) const;

    int getRows() const;
    int getCols() const;

    void setDimensions(int row, int col);

    void DivideRow(int row, double divider);
    void SubtractRows(int row1, int row2, double mult);
    void RowReduction();

    void clear();

    /*
        The following functions are designed to
        1. assist with interfacing with the ui
        2. convert between qt and c++ standard data types
    */
    void CreateMatrix(QString text);
    void printMatrix();
    Matrix(QString text){
        CreateMatrix(text);
    }

};
