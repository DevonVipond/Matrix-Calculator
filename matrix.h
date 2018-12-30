#ifndef MATRIX_H
#define MATRIX_H

#endif // MATRIX_H

#include <QtMath>
#include <QDebug>
#include <string>
#include <iostream>
#include "qt_utilities.h"
//template <typename T>
class Matrix{
private:
    int row_, col_;
    double** x_;
public:
    Matrix(){
        row_ = -1;
        col_ = -1;
    }

    // Creates an empty matrix of size r by c
    Matrix(int r, int c){
        this->setDimensions(r, c);
        x_ = new double*[r];
        for (int i = 0; i < r; i++) {
            x_[i] = new double[c];
            for (int j = 0; j < c; j++) {
                x_[i][j] = 0;
            }
        }
    }

    Matrix(int r, int c, int val){
        this->setDimensions(r, c);
        x_ = new double*[r];
        for (int i = 0; i < r; i++) {
            x_[i] = new double[c];
            for (int j = 0; j < c; j++) {
                x_[i][j] = val;
            }
        }
    }


    //Matrix< operator+(const QSMatrix<T>& rhs{}
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator=(const Matrix& rhs);
    //Matrix<T> operator-(const QSMatrix<T>& rhs);
    //Matrix<T>& operator-=(const QSMatrix<T>& rhs);
    Matrix operator*(const Matrix& rhs);
    Matrix& operator*=(const Matrix& rhs);
    /*Matrix<T> transpose();
    */

     void DivideRow(int row, double divider){
        //error check
         if(row_ < 1 || col_ < 1 || row < 0){
             return;
         }
        for(int i = 0; i < col_; i++){
            x_[row][i] /= divider;
        }
    }

    void SubtractRows(int row1, int row2, double mult){
        if(row_ < 1 || col_ < 1 || row1 < 0 || row2 < 0 || row1 > row_ || row2 > row_){
            return;
        }
        for(int i = row2; i < col_; i++){
            x_[row1][i] -= mult * x_[row2][i];
        }
    }

    void RowReduction(){
        if(row_ < 1 || col_ < 1){
            return;
        }
        for(int r = 0; r < row_ && r < col_; r++){
            for(int c = 0; c < row_; c++){
                if(c != r){
                    qDebug() << "subtract_rows called";
                    SubtractRows(c, r, x_[c][r] / x_[r][r]);
                }
            }
            DivideRow(r,x_[r][r]);
        }
        qDebug() << "end rowreduction";
    }

    /*double Determinant(Matrix x, int n){
        qDebug() << "Inside Determinant";
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

    void FindCofactor(Matrix x, Matrix &submatrix, int col, int n){
        qDebug() << "Inside FindCofactor";
        for(int r = 1; r < n; r++){
            int y = 0;
            for(int c = 0; c < n; c++){
                if(c != col){
                submatrix.at(r - 1, y++) = x.at(r, c);
                }
            }
        }
    }*/

    void clear(){
        if(this->row_ > -1 && this->col_ > -1){
            for(int i = 0; i < row_; i++) {
                 delete[] this->x_[i];
             }
            delete[] this->x_;
        }
        row_ = -1;
        col_ = -1;
    }

    double& at(int row, int col){
        if(row < row_ && col < col_)
            return x_[row][col];
        else
            throw std::out_of_range("invalid pos");
    }

    double& at(int row, int col) const{
        if(row < row_ && col < col_)
            return x_[row][col];
        else
            throw std::out_of_range("invalid pos");
    }

    int getRows() const{
        return row_;
    }

    int getCols() const{
        return col_;
    }

    void setDimensions(int row, int col){
        if(row > 0 && col > 0){
            this->row_ = row;
            this->col_ = col;
        }
        else
            throw std::out_of_range("invalid dimensions");
    }


    //Functions to interface with QT's UI
    Matrix(QString text){
        CreateMatrix(text);
    }

    void CreateMatrix(QString text){
        QChar semicolon = ';';
        QChar comma = ',';
        int row = text.count(semicolon);

        // Find number of columns
        int col = 1;
        for(int i = 0 ; i < text.size() && text[i] != semicolon; ++i){
            if(text[i] == comma)
                col++;
        }

        this->setDimensions(row, col);

        // Populate matrix from string
        x_ = new double*[row_];
        int index = 0; int i = 0;
        if(row_ && col_){
            for( i = 0; i < row_; i++){
                x_[i] = new double[col_];
                for(int j = 0; j < col_; j++){
                    int k = 0;
                    for(k = index; k < text.size() && text[k] != comma && text[k] != semicolon; k++){

                    }
                    x_[i][j] = ConvStringToDouble(text, index, k);
                    index++;
                    if(text[k] == semicolon){
                        break;
                    }
                }
            }
        }
    }

    void printMatrix(){
        for(int row = 0; row < row_; row++){
            for(int col = 0; col < col_; col++){
                qDebug() << this->at(row, col);
            }
            qDebug() << "\n";
        }
    }

};


