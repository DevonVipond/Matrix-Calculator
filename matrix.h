#ifndef MATRIX_H
#define MATRIX_H

#endif // MATRIX_H

#include <QtMath>
#include <QDebug>
#include <string>
#include <iostream>
#include "qt_utilities.h"

class Matrix{
private:
    int row_, col_;
    double** x_;
public:
    Matrix(){
        row_ = -1;
        col_ = -1;
    }

    Matrix(QString text){
        CreateMatrix(text);
    }

    // Creates an empty matrix of size r by c
    Matrix(int r, int c){
        x_ = new double*[r];
        for (int i = 0; i < r; i++) {
            x_[i] = new double[c];
            for (int j = 0; j < c; j++) {
                x_[i][j] = 0;
            }
        }
    }

    ~Matrix(){
        for (int i = 0; i < row_; i++) {
                delete[] x_[i];
        }
        delete[] x_;
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
                qDebug() << this->getElement(row, col);
            }
            qDebug() << "\n";
        }
    }

    double& getElement(int row, int col){
        if(row < row_ && col < col_)
            return x_[row][col];
        else
            throw std::out_of_range("invalid pos");
    }

    int getRow(){
        return row_;
    }

    int getCol(){
        return col_;
    }

    void setDimensions(int row, int col){
        if(row > 0 && col > 0){
            this->row_ = row;
            this->col_ = col;
        }
        else
            throw std::out_of_range("invalid pos");
    }
};
