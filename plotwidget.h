#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QPainter>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
//#include <qwt_scale_draw.h>
//#include <qwt_plot_canvas.h>
//#include <qwt_plot_panner.h>
//#include <qwt_plot_magnifier.h>
//#include <qwt_plot_zoomer.h>

class MyPlotWidget : public QwtPlot
{
public:
    MyPlotWidget(QWidget* parent);

    void setAxesSteps(double stepX, double stepY);

    QwtPlotCurve* curve(){return _curve;}

private:
    /*
    class MyScaleDraw : public QwtScaleDraw
    {
    protected:
        virtual void drawBackbone( QPainter *painter ) const;
    };*/

    QwtPlotCurve* _curve;
};

#endif // PLOTWIDGET_H
