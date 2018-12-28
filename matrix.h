#ifndef MATRIX_H
#define MATRIX_H

#endif // MATRIX_H

#include <QtMath>
#include <QDebug>
#include <string>
#include <iostream>

class Matrix{
private:
    // Dimensions
    int row_, col_;
    QChar **m_;
    // Matrix
    double** x_;
public:
    Matrix(){
        row_ = -1;
        col_ = -1;
    }

    Matrix(QString text){
        createMatrix(text);
    }

    // Creates empty matrix of size r by c
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

    double convStringToDouble(QString text, int  &index, int k){ //should this be in this class?
        int negative = 1;
        if(text[index] == QChar('-')){
            negative *= -1;
            index++;
        }
        double factor =  pow(10,(k - index - 1));
        double returnVal = 0;
        while(factor >= 1){
                returnVal += (text[index++].digitValue()) * factor;
                factor /= 10;
        }
        return returnVal * negative;
    }

    void createMatrix(QString text){
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

        // Populating x[][] from string
        x_ = new double*[row_];
               int index = 0; int i = 0;
               if(row_ && col_){
                   for( i = 0; i < row_; i++){
                       x_[i] = new double[col_];
                       for(int j = 0; j < col_; j++){
                           int k = 0;
                           for(k = index; k < text.size() && text[k] != comma && text[k] != semicolon; k++){

                           }
                           x_[i][j] = convStringToDouble(text, index, k);
                           index++;
                           if(text[k] == semicolon){
                               break;
                           }
                       }
                   }
               }
    }

    double& getElement(int row, int col){
        return x_[row][col];
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
        QChar semicolon = ';', comma = ',', newLine = '\n';
        QString cleanedEntry = "";
        QString text = input;
        for(int i = 0, j = 0; i < text.size(); i++){
            // Check for invalid inputs
            if(text[i] < QChar('0') || text[i] > QChar('9'))
                if(text[i] != semicolon && text[i] != comma && text != newLine)
                    return "";
            // Write data to matrix
            if(text[i] != semicolon && text[i] != comma && text[i] != newLine){
                    cleanedEntry[j++] =  text[i];
                }
        }
        return cleanedEntry;
    }

    double** getMatrixAsDouble(){
        double **intMatrix = new double*[row_];
        if(row_ && col_){
            for(int i = 0; i < row_; i++){
                intMatrix[i] = new double[col_];
                for(int j = 0; j < col_; j++){
                    int x = m_[i][j].digitValue();
                    intMatrix[i][j] = (double) x;
                }
            }
        }
        return intMatrix;
    }

    QString DisplayMatrix(){
        QString displayText = "";
        //qDebug() << m1.getRow() << endl << m1.getCol();
        for(int i = 0; i < row_; i++){
            displayText += "| ";
            for(int j = 0; j < col_; j++){
                //qDebug() << m1.getElement(i, j);
                displayText += QString::number(this->getElement(i, j)) + " ";
            }
            displayText += "|\n";
        }
        return displayText;
    }

    void printMatrix(){
        for(int row = 0; row < row_; row++){
            for(int col = 0; col < col_; col++){
                qDebug() << this->getElement(row, col);
            }
            qDebug() << "\n";
        }
    }
};
