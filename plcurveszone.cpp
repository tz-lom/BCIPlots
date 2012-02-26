#include "plcurveszone.h"
#include <QTimer>

PlCurvesZone::PlCurvesZone(QWidget *parent) :
    QWidget(parent)
{
    reconfigure(1,1);
}


void PlCurvesZone::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    qreal curveHeight = this->height()/mCurves.size();

    for(int t=mCurves.size()-1; t>=0; --t)
    {
        QMatrix matrix;

        matrix.translate(0, curveHeight*(0.5+t));
        painter.setMatrix(matrix);

        painter.setPen(QColor("black"));
        mCurves[t].draw(painter);
    }
    painter.setMatrixEnabled(false);
    painter.setPen(QPen(QBrush(QColor(255,128,0)),3));
    int front = mCurves[0].frontInPixels();
    painter.drawLine(front,0,front,this->height());

    painter.end();
}

void PlCurvesZone::resizeEvent(QResizeEvent *)
{
    QTimer::singleShot(500, this, SLOT(scalePlots()));
}

void PlCurvesZone::scalePlots()
{
    for(int t=mCurves.size()-1; t>=0; --t)
    {
        mCurves[t].setWidth(this->width());
    }
    update();
}

void PlCurvesZone::addData(qreal *data, int size)
{
    int length = size/mCurves.size();

    for(int t=mCurves.size()-1; t>=0; --t)
    {
        mCurves[t].addDataRow(data+t, length, mCurves.size());
    }

    QRect rect = mCurves[0].updateRect();
    rect.setTop(0);
    rect.setBottom(height());
    update(rect);
}

void PlCurvesZone::reconfigure(int curves,int size)
{
    if(curves<1) return;
    if(size<1) return;
    mCurves.resize(curves);
    for(int t=mCurves.size()-1; t>=0; --t)
    {
        mCurves[t].setSize(size);
        mCurves[t].setWidth(this->width());
    }
    update();
}

