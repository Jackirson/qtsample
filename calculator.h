#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QLinkedList>
#include <QRegExp>
#include <QString>
#include <QStringList>

class Calculator
{
    QRegExp         _regOp;
    QRegExp         _regOper;
    QStringList     _parsedList;

    void makeFloatOpsList(QLinkedList<double>& ops, double x);

public:
    Calculator();

    static  double str2dbl(const QString&);
    bool    parseFuncString(const QString&);
    double  evaluateFunc(double x);
};

#endif // CALCULATOR_H
