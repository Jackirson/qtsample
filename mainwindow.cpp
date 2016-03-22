#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QToolTip>

#include "calculator.h"
//----------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto numValidator = new QRegExpValidator(QRegExp(QString(
                    "^\\-?[0-9]*[\\.,]?[0-9]+$")));
    /* this validator allows any floating-point
       with delimiter . or , (not in sci-notation)*/

    ui->lineEditX->setValidator(numValidator);
    ui->lineEditY->setValidator(numValidator);
    ui->lineEditDx->setValidator(numValidator);
    ui->lineEditXmin->setValidator(numValidator);
    ui->lineEditXmax->setValidator(numValidator);

    QObject::connect(ui->pushButtonClose, SIGNAL(clicked(bool)), SLOT(close()));
    QObject::connect(ui->pushButtonRefresh, SIGNAL(clicked(bool)), SLOT(refreshPlot()));
}
//----------------------------
MainWindow::~MainWindow()
{
    delete ui;
}


//----------------------------
void MainWindow::refreshPlot()
{
    static Calculator calc;

    double xmin = Calculator::str2dbl(ui->lineEditXmin->text());
    double xmax = Calculator::str2dbl(ui->lineEditXmax->text());
    double dx   = Calculator::str2dbl(ui->lineEditDx->text());

    if( xmax < xmin+dx || dx <= 0  )
    {
        QToolTip::showText(pos() +
                           ui->groupBoxData->pos() +
                           ui->labelXmin->pos(),
                           "Incorrect Xmin, Xmax or Dx.");

        return;
    }

    QString func = ui->textEditFunc->toPlainText();
    if( ! calc.parseFuncString(func) )
    {
        QToolTip::showText(pos() +
                           ui->groupBoxData->pos() +
                           ui->textEditFunc->pos(),
                           "Incorrect y=f(x) string.");

        return;
    }

    // set step sizes
    double stepX = Calculator::str2dbl(ui->lineEditX->text());
    double stepY = Calculator::str2dbl(ui->lineEditY->text());

    ui->plot->setAxesSteps(stepX, stepY);

    // make plot data
    QPolygonF points;
    for(double x=xmin; x<= xmax; x+=dx)
        points << QPointF(x, calc.evaluateFunc(x));

    ui->plot->curve()->setSamples( points );
    ui->plot->replot();
}




