#include <QtMath>
#include <QDebug>
#include <string>
#include <iostream>
#include "matrix.h"
/*class Matrix{
private:
    int row_, col_; //size of matrix
    QChar **m_; //matrix
    void creatMatrix(){
        if(row_ > 0 && col_ > 0){

        }
    }
public:
    Matrix(){
        row_ = -1;
        col_ = -1;
    }
    void Matrix::createMatrix(QString text){
        qDebug() << "in createMatrix";
        QChar semicolon = ';';
        QChar comma = ',';

        int row = text.count(semicolon);// + 1;
        int col = 1;

        for(int i = 0 ; i < text.size() && text[i] != semicolon; ++i){
            if(text[i] == comma)
                col++;
        } //can do this by dividing row and comma count
        this->setDimensions(row,col);
        qDebug() << "row,col: " << row_ << col_;
        int r = 0, c = 0, i = 0;
        QString cleanedEntry = this->cleanStringInput(text);
        for(r = 0; r < row_; r++){
            for(c = 0; c < col_; c++){
                m_[r][c] =  cleanedEntry[i++];
            }
        }
    }
   QChar getElement(int row, int col){
        return m_[row][col];
    }
    void setDimensions(int row, int col){
        if(row > 0 && col > 0){
            this->row_ = row;
            this->col_ = col;
            m_ = new QChar*[row];
            for(int i = 0; i < row; ++i){
                m_[i] = new QChar[col];
            }

        }
        else
            //prob gonna need some error here
            qDebug() << "wrong!";
    }
    int getRow(){
        return row_;
    }
    int getCol(){
        return col_;
    }
    QString cleanStringInput(QString input){
        qDebug() << "in cleanStringInput";
        QChar semicolon = ';';
        QChar comma = ',';
        QString cleanedEntry = "";
        QString text = input;
        for(int i = 0, j = 0; i < text.size(); i++){
            //Check for invalid inputs
            if(text[i] < QChar('0') || text[i] > QChar('9')) // test for any non integer inputs excluding comma and semicolons
                if(text[i] != semicolon && text[i] != comma)
                    return "";
            if(text[i] != semicolon && text[i] != comma){
                    cleanedEntry[j++] =  text[i];
                }
        }
       qDebug() << "cleanedEntry: " << cleanedEntry;

        return cleanedEntry;
    }
    int** getMatrixAsInteger(){
        int **intMatrix = new int*[row_];
        if(row_ && col_){
            for(int i = 0; i < row_; i++){
                intMatrix[i] = new int[col_];
                for(int j = 0; j < col_; j++){
                    intMatrix[i][j] = m_[i][j].digitValue();
                }
            }
        }
        return intMatrix;
    }
};
*/
