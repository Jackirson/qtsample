//#include <qwt_painter.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_canvas.h>
#include "plotwidget.h"

MyPlotWidget::MyPlotWidget(QWidget *parent) : QwtPlot(parent)
{
    setCanvasBackground( Qt::white );
    setAxisScale(QwtPlot::xBottom, 0, 10);
    setAxisScale(QwtPlot::yLeft, 0, 10);

    _curve = new QwtPlotCurve;
    _curve->attach( this );
    _curve->setPen( Qt::red, 3 );
    _curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    auto grid = new QwtPlotGrid();
    grid->setPen( Qt::black, 0, Qt::DashDotLine );
    grid->attach( this );

    reinterpret_cast<QwtPlotCanvas*>(canvas())->
            setFrameStyle( QFrame::NoFrame );

    // setup custom axis rendering routines
    //setAxisScaleDraw(QwtPlot::xBottom, new MyScaleDraw);
    //setAxisScaleDraw(QwtPlot::yLeft, new MyScaleDraw);
}

//----------------------------
void MyPlotWidget::setAxesSteps(double stepX, double stepY)
{
    QwtInterval range;
    range = axisInterval(QwtPlot::xBottom);
    if( stepX != 0)
         setAxisScale(QwtPlot::xBottom, range.minValue(), range.maxValue(), stepX);
    else
         setAxisAutoScale(QwtPlot::xBottom);

    range = axisInterval(QwtPlot::yLeft);
    if( stepY != 0)
         setAxisScale(QwtPlot::yLeft, range.minValue(), range.maxValue(), stepY);
    else
         setAxisAutoScale(QwtPlot::yLeft);
}

/*
//----------------------------
void MyPlotWidget::MyScaleDraw::drawBackbone(QPainter *painter) const
{
    QwtScaleDraw::drawBackbone(painter);

    int w = penWidth()+2;
    QPolygon arrow;
    switch ( alignment() )
    {
        case LeftScale:
        {
            arrow << QPoint(pos().x()-w*4, pos().y());
            arrow << QPoint(pos().x(), pos().y()-w*4);
            arrow << QPoint(pos().x()+w*4, pos().y());
            //arrow << QPoint(pos().x()-w*2, pos().y());
            break;
        }
        case BottomScale:
        {
            arrow << QPoint(pos().x()+length(), pos().y()-w*4);
            arrow << QPoint(pos().x()+length()+w*4, pos().y());
            arrow << QPoint(pos().x()+length(), pos().y()+w*4);
            break;
        }
    }

    QBrush brush(Qt::black);
    painter->setBrush(brush);
    QwtPainter::drawPolygon(painter, arrow);
}*/
