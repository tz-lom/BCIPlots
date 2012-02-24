#include "plcurveszone.h"

PlCurvesZone::PlCurvesZone(QWidget *parent) :
    QWidget(parent)
{
}


void PlCurvesZone::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    //painter.fillRect(this->rect(),QColor("white"));

    QMatrix matrix;
    matrix.translate(0, height()/2);

    painter.setMatrix(matrix);
    painter.setPen(QColor("black"));
    curve.draw(painter);

    painter.end();
}

void PlCurvesZone::resizeEvent(QResizeEvent *)
{
    curve.resize(this->width(), curve.count());
    update();
}

void PlCurvesZone::addData(qreal *data, int size)
{
    int length = size/4;
    /*for(int t=0; t<length; ++t)
    {
        curve.addData(data[t*4]);
    }*/
    curve.addDataRow(data, length, 4);

    QRect rect = curve.updateRect();
    rect.setTop(0);
    rect.setBottom(height());
    update(rect);
    //repaint(rect);
}