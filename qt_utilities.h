#ifndef QT_UTILITIES_H
#define QT_UTILITIES_H

#endif // QT_UTILITIES_H

#include <QtMath>
#include <QDebug>
#include <string>
#include <iostream>

/*
    Contains functions to:
    1. assist with interfacing with the ui
    2. convert between qt and c++ standard data types
*/

inline double ConvStringToDouble(QString text, int  &index, int k){ //should this be in this class?
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
