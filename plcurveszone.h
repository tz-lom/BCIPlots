#ifndef PLCURVESZONE_H
#define PLCURVESZONE_H

#include <QWidget>
#include "plsinglecurve.h"

class PlCurvesZone : public QWidget
{
    Q_OBJECT
public:
    explicit PlCurvesZone(QWidget *parent = 0);
    
    PlSingleCurve curve;

signals:
    
public slots:
    void addData(qreal *data, int size);
    void scalePlots();
    
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent (QResizeEvent *);
};

#endif // PLCURVESZONE_H
