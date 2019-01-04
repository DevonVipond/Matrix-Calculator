#include "matrix.h"
#include <QtMath>
#include <QDebug>
#include <string>
#include <iostream>
#include "qt_utilities.h"

// Creates an empty matrix of size r by c
Matrix::Matrix(int r, int c){
    this->setDimensions(r, c);
    x_ = new double*[r];
    for (int i = 0; i < r; i++) {
        x_[i] = new double[c];
        for (int j = 0; j < c; j++) {
            x_[i][j] = 0;
        }
    }
}

// Creates an empty matrix of size r by c initialized to val
Matrix::Matrix(int r, int c, int val){
    this->setDimensions(r, c);
    x_ = new double*[r];
    for (int i = 0; i < r; i++) {
        x_[i] = new double[c];
        for (int j = 0; j < c; j++) {
            x_[i][j] = val;
        }
    }
}

void Matrix::DivideRow(int row, double divider){
     if(row_ < 1 || col_ < 1 || row < 0){
         return;
     }
     if(divider == 0.0)
        return;
     for(int i = 0; i < col_; i++){
        x_[row][i] /= divider;
     }
}

void Matrix::SubtractRows(int row1, int row2, double mult){
    if(row_ < 1 || col_ < 1 || row1 < 0 || row2 < 0 || row1 > row_ || row2 > row_){
        return;
    }
    for(int i = row2; i < col_; i++){
        x_[row1][i] -= mult * x_[row2][i];

    }
}

void Matrix::RowReduction(){
    if(row_ < 1 || col_ < 1){
        return;
    }

    for(int r = 0; r < row_ && r < col_; r++){
        for(int c = 0; c < row_; c++){
            if(c != r){
                SubtractRows(c, r, x_[c][r] / x_[r][r]);
            }
        }
        DivideRow(r,x_[r][r]);
    }

    // Set all tiny elements to zero
    for(int i = 0; i < row_; i++){
        for(int j = 0; j < col_; j++){
            if(x_[i][j] < 0.1 && x_[i][j] > -0.1)
                x_[i][j] = 0;
        }
    }
}


void Matrix::clear(){
    if(this->row_ > -1 && this->col_ > -1){
        for(int i = 0; i < row_; i++) {
             delete[] this->x_[i];
         }
        delete[] this->x_;
    }
    row_ = -1;
    col_ = -1;
}

double& Matrix::at(int row, int col){
    if(row < row_ && col < col_)
        return x_[row][col];
    else
        throw std::out_of_range("invalid pos");
}

double& Matrix::at(int row, int col) const{
    if(row < row_ && col < col_)
        return x_[row][col];
    else
        throw std::out_of_range("invalid pos");
}

int Matrix::getRows() const{
    return row_;
}

int Matrix::getCols() const{
    return col_;
}

void Matrix::setDimensions(int row, int col){
    if(row > 0 && col > 0){
        this->row_ = row;
        this->col_ = col;
    }
    else
        throw std::out_of_range("invalid dimensions");
}

void Matrix::CreateMatrix(QString text){
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

void Matrix::printMatrix(){
    for(int row = 0; row < row_; row++){
        for(int col = 0; col < col_; col++){
            qDebug() << this->at(row, col);
        }
        qDebug() << "\n";
    }
}

Matrix& Matrix::operator+=(const Matrix& rhs){
    if(this->row_ != rhs.getRows() || this->col_ != rhs.getCols()){
        throw std::out_of_range("matrices must be same size to add");
    }
    for(int i = 0; i < rhs.getRows(); i++){
        for(int j = 0; j < rhs.getCols(); j++){
            this->x_[i][j] += rhs.at(i,j);
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs){
    if(this->row_ != rhs.getRows() || this->col_ != rhs.getCols()){
        throw std::out_of_range("matrices must be same size to subtract");
    }
    for(int i = 0; i < rhs.getRows(); i++){
        for(int j = 0; j < rhs.getCols(); j++){
            this->x_[i][j] -= rhs.at(i,j);
        }
    }

    return *this;
}

Matrix& Matrix::operator=(const Matrix& rhs){
    if(this->row_ > -1 && this->col_ > -1){

        for(int i = 0; i < row_; i++) {
             delete[] this->x_[i];
         }
        delete[] this->x_;
    }
    this->setDimensions(rhs.getRows(), rhs.getCols());
    x_ = new double*[row_];
    for(int i = 0; i < row_; i++) {
        x_[i] = new double[col_];
        for(int j = 0; j < col_; j++) {
             this->at(i,j) = rhs.at(i,j);
         }
     }

    return *this;
}

Matrix Matrix::operator*(const Matrix& rhs){
    //The number of col in the first matrix must be equal to the number of rows in the second matrix.
    if(this->getRows() != rhs.getCols()){
        throw std::out_of_range("incorrect dimensions");
    }
    Matrix result(rhs.getRows(), rhs.getCols());

    for (int i=0; i< row_; i++) {
      for (int j=0; j< col_; j++) {
        for (int k=0; k< row_; k++) {
          result.at(i,j) += this->x_[i][k] * rhs.at(k,j);
        }
      }
    }

    return result;
}

Matrix& Matrix::operator*=(const Matrix& rhs){
    Matrix result = (*this) * rhs;
    (*this) = result;

    return *this;
}
