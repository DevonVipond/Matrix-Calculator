#ifndef MATRIX_H
#define MATRIX_H

#endif // MATRIX_H

#include <QtMath>
#include <QDebug>
#include <string>
#include <iostream>

class Matrix{
private:
    int row_, col_; //size of matrix
    QChar **m_;
    double** x_;
public:
    Matrix(){
        row_ = -1;
        col_ = -1;
    }
    double convToDouble(QString text, int  &index, int k){
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

    void createMatrixAsDouble(QString text){
        QChar semicolon = ';';
        QChar comma = ',';

        int row = text.count(semicolon);

        qDebug() << "finding cols";
        // Find number of columns
        int col = 1;
        for(int i = 0 ; i < text.size() && text[i] != semicolon; ++i){
            if(text[i] == comma)
                col++;
        } //can do this by dividing row and comma count

        qDebug() << "setting dimensions";
        this->setDimensions(row, col); //size matrix??
        //this->CheckUserInputForErrors();

        x_ = new double*[row_];
               int index = 0; int i = 0;
                   if(row_ && col_){
                       for( i = 0; i < row_; i++){
                           x_[i] = new double[col_];
                           for(int j = 0; j < col_; j++){
                               int k = 0;
                               for(k = index; k < text.size() && text[k] != comma && text[k] != semicolon; k++){

                               }
                               x_[i][j] = convToDouble(text, index, k);
                               qDebug() << "x[i][j]: "  << x_[i][j] << endl;
                               index++;
                               if(text[k] == semicolon){
                                   break;

                               }
                           }
                       }
                   }


    }
    void createMatrix(QString text){
        qDebug() << "creating matrix";
        QChar semicolon = ';';
        QChar comma = ',';

        int row = text.count(semicolon);

        qDebug() << "finding cols";
        // Find number of columns
        int col = 1;
        for(int i = 0 ; i < text.size() && text[i] != semicolon; ++i){
            if(text[i] == comma)
                col++;
        } //can do this by dividing row and comma count

        qDebug() << "setting dimensions";
        this->setDimensions(row, col);

        /*        double **intMatrix = new double*[row_];
        if(row_ && col_){
            for(int i = 0; i < row_; i++){
                intMatrix[i] = new double[col_];
                for(int j = 0; j < col_; j++){
                    int x = m_[i][j].digitValue();
                    intMatrix[i][j] = (double) x;
                }
            }
        }
        return intMatrix;*/

        qDebug() << "copying over data";
        int r = 0, c = 0, i = 0;
        QString cleanedEntry = this->cleanStringInput(text);
        for(r = 0; r < row_; r++){
            for(c = 0; c < col_; c++){
                m_[r][c] =  cleanedEntry[i++];
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





};
