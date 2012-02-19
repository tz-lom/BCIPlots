#include "signalplot.h"
#include <QPainter>
#include <QDebug>
#include <QPaintEvent>
#include <math.h>

SignalPlot::SignalPlot(QWidget *parent) :
    QWidget(parent),
    mChannels(1),
    mFrequency(1),
    mTimeInterval(1),
    mAmp(1)
{
    rebuildChannelContainers();
    mBackgroundColor = QColor("black");
    mBorderColor = QColor("cyan");
    mTextColor = QColor(255, 128, 0);
    mLinesColor = QColor("white");
}

int SignalPlot::timeInterval()
{
    return mTimeInterval;
}

int SignalPlot::frequency()
{
    return mFrequency;
}

int SignalPlot::channels()
{
    return mChannels;
}

double SignalPlot::amplification()
{
    return mAmp;
}

void SignalPlot::addData(const int *data, const int size)
{
    if(size%mChannels !=0) return;
    int length = size/mChannels;

    int ch=0;
    for(int i=0; i<size; ++i)
    {
        mChannelData[ch].append(data[i]);
        if(++ch == mChannels) ch=0;
    }
    incrementalUpdate(length);
}

void SignalPlot::incrementalUpdate(int items)
{
    update();
}

void SignalPlot::setChannels(int channels)
{
    mChannels = channels;
    rebuildChannelContainers();
}

void SignalPlot::setFrequency(int freq)
{
    mFrequency = freq;
    rebuildChannelContainers();
}

void SignalPlot::setTimeInterval(int interval)
{
    mTimeInterval = interval;
    rebuildChannelContainers();
}

void SignalPlot::setAmplification(double amp)
{
    mAmp = amp;
}

void SignalPlot::rebuildChannelContainers()
{
    mChannelData.resize(mChannels);
    mChannelNames.resize(mChannels);
    for(int i=0; i<mChannels; ++i)
    {
        mChannelData[i].resize( mFrequency*mTimeInterval );
        if(mChannelNames[i].isEmpty())
        {
            mChannelNames[i] = QString::number(i+1);
        }
    }
    update();
}

void SignalPlot::buildBackground()
{
    mBackground = QImage(this->size(), QImage::Format_RGB32);
    mBackground.fill(mBackgroundColor);

    QPainter painter;
    painter.begin(&mBackground);

    const int border = 4;

    int bottomLine = painter.fontMetrics().boundingRect("1s").height()+border*2;
    int leftLine = 0;
    // draw channel names
    for(int i=0; i<mChannels; ++i)
    {
        int width = painter.fontMetrics().boundingRect(mChannelNames[i]).width();
        if(leftLine<width) leftLine = width;
    }
    leftLine+= border*2;

    mPlotArea = this->size()-QSize(leftLine,bottomLine);


    for(int i=0; i<mChannels; ++i)
    {
        int offset = mPlotArea.height()/mChannels/2*(i*2+1);

        painter.setPen(mBorderColor);
        painter.drawLine(leftLine-border/2, offset, leftLine, offset);

        painter.setPen(mTextColor);
        painter.drawText(border,
                         offset + painter.fontMetrics().boundingRect(mChannelNames[i]).height()/3,
                         mChannelNames[i]);
    }

    for(int i=0; i<mTimeInterval; ++i)
    {
        painter.drawText(leftLine+i*mPlotArea.width()/mTimeInterval,
                         this->size().height()-border,
                         QString::number(i+1));
    }

    painter.setPen(mBorderColor);
    painter.drawLine(leftLine, 0, leftLine, this->size().height());
    painter.drawLine(0, this->size().height()-bottomLine, this->size().width(), this->size().height()-bottomLine);

    painter.end();
}

void SignalPlot::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setClipRect(event->rect());
    //painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(QPoint(0,0), mBackground);
    drawSignal();
    painter.end();
}

void SignalPlot::drawSignal(QRect clippingRect)
{
    QPainter painter;
    painter.begin(this);


    int beginLine = 0,
            endLine = mChannelData[0].size();
    if(!clippingRect.isNull())
    {
        int leftBorder = std::max(clippingRect.left() - this->width()+mPlotArea.width(), 0);
        int rightBorder = std::min(clippingRect.right(), this->width());
        int length = rightBorder-leftBorder;
        beginLine = floor(leftBorder/length*mChannelData[0].size());
        endLine = ceil(rightBorder/length*mChannelData[0].size());
    }
    QTransform matrix;
    matrix.translate(
                    this->size().width() - mPlotArea.width(),
                    0
                );
    matrix.scale(
                    (qreal)mPlotArea.width()/this->size().width(),
                    1
                );

    painter.setTransform(matrix, true);
    painter.setPen(mLinesColor);

    for(int channel=0; channel<mChannels; ++channel)
    {
        int baseY = mPlotArea.height()/mChannels/2*(channel*2+1);

        int y = mChannelData[channel](beginLine)*mAmp;

        for(int i=beginLine+1; i<endLine; ++i)
        {
            int newY = mChannelData[channel](i)*mAmp;
            painter.drawLine(i-1, baseY+y, i, baseY+newY);
            y = newY;
        }
    }

    QPen pen(mTextColor);
    pen.setWidth(3);
    painter.setPen(pen);

    int pos = mChannelData[0].internalPos();
    painter.drawLine(pos, 0, pos, mPlotArea.height());
}

void SignalPlot::resizeEvent(QResizeEvent *)
{
    buildBackground();
    update();
}

