#include "calculator.h"

#include <QDebug>
#include <QLinkedList>
#include <QLocale>
#include <QString>

//----------------------------
Calculator::Calculator()
{
    // this regexp matches either a float number or 'x' and captures it
    QString sOp("^\\s*(\\-?[0-9]*[\\.,]?[0-9]+|[xX])\\s*");
    _regOp.setPattern(sOp);

    // this regexp matches an operator and captures it
    QString sOper("^\\s*([\\+\\-\\*/])\\s*");
    _regOper.setPattern(sOper);
}
//----------------------------
// returns true on success
bool Calculator::parseFuncString(const QString& func)
{
    _parsedList.clear();
    int pos = 0;
    bool success = false;

    while ( 1 )
    {

      pos = _regOp.indexIn(func, pos, QRegExp::CaretAtOffset);
      if(pos == -1)
          break;

      pos += _regOp.matchedLength();
      _parsedList << _regOp.cap(1);

      if( pos == func.length() ) // correct eol
          success = true;

      pos = _regOper.indexIn(func, pos, QRegExp::CaretAtOffset);
      if(pos == -1)
          break;

      pos += _regOper.matchedLength();
      _parsedList << _regOper.cap(1);
    }

    return success;
}
//----------------------------
// call this after 'parseFuncString()' succeeded
double Calculator::evaluateFunc(double x)
{
    // 0. parse floats, substitute 'x' and alias operators
    QLinkedList<double> ops;
    makeFloatOpsList(ops, x);

    /*for(auto op : ops)
        qDebug() << op;
    qDebug() << endl;*/

    // 1. * and /
    auto i = ops.begin()+1;
    while( i != ops.end()-1 && i != ops.end() )
    {
      if(*i == 3)
      {
          *i = *(i-1) * *(i+1);
          ops.erase(i-1);
          ops.erase(i+1);
          ++i;
      }
      else if(*i == 4)
      {
          *i = *(i-1) / *(i+1);
          ops.erase(i-1);
          ops.erase(i+1);
          ++i;
      }
      else
          i += 2;
    }

    /*for(auto op : ops)
        qDebug() << op;
    qDebug() << endl;*/

    // 2. + and -
    double result = ops.front();
    i = ops.begin()+2;
    while(1)
    {
        if(*(i-1) == 1)
            result += *i;
        else if(*(i-1) == 2)
            result -= *i;

        if( i == ops.end()-1 )
            break;
        i += 2;
    }

    return result;
}
//----------------------------
void Calculator::makeFloatOpsList(QLinkedList<double>& ops, double x)
{
     for(int i= 0; i< _parsedList.size(); ++i)
     {
         const QString str = _parsedList.at(i);
         if(i % 2 == 0)  // operand
             if(str == "x" || str == "X")
                 ops << x;
             else
                 ops << str2dbl(str);
         else            // operator
                if(str == "+") ops << 1;
           else if(str == "-") ops << 2;
           else if(str == "*") ops << 3;
           else if(str == "/") ops << 4;
     }
}
//----------------------------
double Calculator::str2dbl(const QString& str)
{
    static QLocale locale;

    bool ok = false;
    double result =  str.toDouble(&ok);
    if( !ok ) // then try using QLocale::toDouble()
        result = locale.toDouble(str, &ok);
    if( !ok )
        return 0;

    return result;
}
