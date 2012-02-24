#ifndef PLSINGLECURVE_H
#define PLSINGLECURVE_H

#include <QVector>
#include <QPainter>

class PlSingleCurve
{
public:
    PlSingleCurve();

    enum Mode {
        Cyclic,
        Pushing
    };

    int width();
    int count();
    Mode mode();

    void setMode(Mode mode);
    void resize(int width, int count);

    void addData(qreal data);
    void addDataRow(qreal *data, int size, int step=1);

    void draw(QPainter &painter);

    QRect updateRect();

protected:
    QVector<QPointF> mPaintData;
    int mWidth;
    qreal mItemPerPixel;
    int mSize;
    qreal mMean;
    int mMeanedPoints;
    int mFront;

    Mode mMode;
    QRect mUpdateRect;
};

#endif // PLSINGLECURVE_H
