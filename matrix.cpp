#include "matrix.h"

//Matrix<T> operator+(const QSMatrix<T>& rhs);
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

/*Matrix operator*(const Matrix& rhs){

}*/

//Matrix& operator*=(const Matrix& rhs);
/*Matrix<T> operator-(const QSMatrix<T>& rhs);

Matrix<T> transpose();
*/
