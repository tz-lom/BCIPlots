#ifndef SIGNALPLOT_H
#define SIGNALPLOT_H

#include <QWidget>
#include <QVector>
#include "cyclicvector.h"

class SignalPlot : public QWidget
{
    Q_OBJECT
public:
    explicit SignalPlot(QWidget *parent = 0);
    
    int channels();
    int frequency();

    void setTimeInterval(int interval);
    int timeInterval();
    double amplification();

signals:

public slots:
    void setChannels(int channels);
    void setFrequency(int freq);
    void addData(const int *data, const int size);
    void setAmplification(double amp);

protected:
    int mChannels;
    QVector<QString> mChannelNames;
    int mFrequency;
    QVector<CyclicVector<int> > mChannelData;

    int mTimeInterval;
    double mAmp;

    QSize  mPlotArea;
    QImage mBackground;
    QColor mBackgroundColor;
    QColor mBorderColor;
    QColor mTextColor;
    QColor mLinesColor;

    void buildBackground();
    void drawSignal(QPainter &painter);//QRect clippingRect = QRect());

    void rebuildChannelContainers();
    void paintEvent(QPaintEvent *);
    void resizeEvent (QResizeEvent *);

    void incrementalUpdate(int items);
    int mItemsPerPixel;
    int mChannelDataReceived;
};

#endif // SIGNALPLOT_H
