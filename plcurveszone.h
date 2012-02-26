#ifndef PLCURVESZONE_H
#define PLCURVESZONE_H

#include <QWidget>
#include "plsinglecurve.h"

class PlCurvesZone : public QWidget
{
    Q_OBJECT
public:
    explicit PlCurvesZone(QWidget *parent = 0);
signals:
    
public slots:
    void addData(qreal *data, int size);

    void reconfigure(int curves,int size);

    void scalePlots();
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent (QResizeEvent *);

    QVector<PlSingleCurve> mCurves;
};

#endif // PLCURVESZONE_H
