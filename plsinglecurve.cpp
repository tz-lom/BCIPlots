#include "plsinglecurve.h"
#include <math.h>
#include <QDebug>

PlSingleCurve::PlSingleCurve():
    mWidth(1),
    mItemPerPixel(1),
    mSize(1),
    mMode(PlSingleCurve::Cyclic)
{
    setWidth(1);
}


int PlSingleCurve::size()
{
    return mSize;
}

int PlSingleCurve::width()
{
    return mWidth;
}

PlSingleCurve::Mode PlSingleCurve::mode()
{
    return mMode;
}

void PlSingleCurve::setMode(Mode mode)
{
    mMode = mode;
}

void PlSingleCurve::addData(qreal data)
{
    if(mItemPerPixel>1)
    {
        mMean += data;
        mMeanedPoints++;
        mAdded++;
        if(mAdded/mItemPerPixel>=mFront)
        {
            float avg = mMean/mMeanedPoints;
            if(mMode == Pushing)
            {
                for(int t=1; t<mPaintData.size(); ++t)
                {
                    mPaintData[t-1].setY(mPaintData[t].y());
                }
                mPaintData[mPaintData.size()-1].setY(avg);
            }
            else
            {
                mUpdateRect.setLeft( mFront-1 );
                mUpdateRect.setRight( mFront+1 );

                mPaintData[mFront].setY(avg);
            }
            if(++mFront>=mPaintData.size())
            {
                mFront=0;
                mMeanedPoints = 0;
            }
            mMean = 0;
            mMeanedPoints = 0;
        }
    }
    else
    {
        if(mMode == Pushing)
        {
            for(int t=1; t<mPaintData.size(); ++t)
            {
                mPaintData[t-1].setY(mPaintData[t].y());
            }
            mPaintData[mPaintData.size()-1].setY(data);
        }
        else
        {
            mUpdateRect.setLeft( floor((qreal)(mFront-1)/mItemPerPixel) );
            mUpdateRect.setRight( ceil((qreal)(mFront+1)/mItemPerPixel) );

            mPaintData[mFront++].setY(data);
            if(mFront>=mPaintData.size()) mFront=0;
        }
    }
}

void PlSingleCurve::addDataRow(qreal *data, int size, int step)
{
    if(mMode == Pushing)
    {
        for(int t=0; t<size; ++t, data+=step)
        {
            addData(*data);
        }
    }
    else
    {
        // mode: moving front

        addData(*data);
        QRect beg = mUpdateRect;

        data+=step;
        for(int t=1; t<size; ++t, data+=step)
        {
            addData(*data);
        }
        if(beg.left()<mUpdateRect.left())
        {
            mUpdateRect.setLeft(beg.left());
            mUpdateRect.setRight(mUpdateRect.right());
        }
        else
        {
            mUpdateRect.setLeft(0);
            mUpdateRect.setRight(mWidth);
        }
    }

}


void PlSingleCurve::setWidth(int width)
{
    if(mWidth==width) return;
    qreal itemPerPixel = (qreal)mSize/width;
    if(itemPerPixel>1)
    {
        // perform resampling

        QVector<QPointF> newData;
        newData.resize(width);
        for(int t=0; t<width; ++t)
        {
            newData[t].setX(t);
        }

        if(itemPerPixel > mItemPerPixel)
        {
            int point = 0;
            qreal avg = 0;
            int avgc  = 0;
            qreal step = (qreal)newData.size()/mPaintData.size();

            for(int t=0; t<mPaintData.size(); ++t)
            {
                avg+= mPaintData[t].y();
                avgc++;

                if(::floor(step*t)>point)
                {
                    newData[point].setY(avg/avgc);
                    avg  = 0;
                    avgc = 0;
                    point++;
                    if(point>newData.size()-1) point=newData.size()-1;
                }
            }
            if(avgc>0) newData[newData.size()-1].setY(avg/avgc);
        }
        else
        {

            for(int t=1; t<mPaintData.size(); ++t)
            {
                int     left = ::floor((qreal)(t-1)/mPaintData.size()*newData.size()),
                        right = ::ceil((qreal)(t)/mPaintData.size()*newData.size()),
                        w = right-left;

                qreal   b = mPaintData[t-1].y(),
                        a = (mPaintData[t].y()-mPaintData[t-1].y())/w;

                for(int x=0,i=left; i<=right; ++i,++x)
                {
                    newData[i].setY(a*x+b);
                }
            }
        }

        mPaintData = newData;
    }
    else
    {
        if(mItemPerPixel>1)
        {
            QVector<QPointF> newData;
            newData.resize(mSize);

            for(int t=1; t<mPaintData.size(); ++t)
            {
                int     left = ::floor((qreal)(t-1)/mPaintData.size()*newData.size()),
                        right = ::ceil((qreal)(t)/mPaintData.size()*newData.size());
                if(right>  newData.size()-1) right =  newData.size()-1;
                int w = right-left;

                qreal   b = mPaintData[t-1].y(),
                        a = (mPaintData[t].y()-mPaintData[t-1].y())/w;

                for(int x=0,i=left; i<=right; ++i,++x)
                {
                    newData[i].setY(a*x+b);
                }
            }
            mPaintData = newData;
        }
        mPaintData.resize(mSize);
        for(int t=0;t<mSize;++t)
        {
            mPaintData[t].setX(t/itemPerPixel);
        }
    }
    mItemPerPixel = itemPerPixel;
    mWidth = width;
    if(mFront>mPaintData.size()) mFront = 0;
    mAdded = mFront*mItemPerPixel;
    mMean = 0;
    mMeanedPoints = 0;

    if(mMode == Pushing)
    {
        mUpdateRect.setLeft( 0 );
        mUpdateRect.setRight( width );
    }
}

void PlSingleCurve::setSize(int size)
{
    if(mSize==size) return;

    /*
      @todo: here is the trick:
      resize to new itemPerPixel
      then restore width and set new count
     *
    int oldWidth = mWidth;
    qreal itemPerPixel = (qreal)size/mWidth;
    setWidth(mSize/itemPerPixel);
    setWidth(oldWidth-1);
    mSize = size;
    setWidth(oldWidth);
    */

    mSize = size;
    mFront = 0;
    mMean = 0;
    mMeanedPoints = 0;
    mAdded = mFront*mItemPerPixel;

    int realWidth = mWidth;
    mWidth=1;
    mPaintData.resize(0);
    setWidth(realWidth);

}

void PlSingleCurve::draw(QPainter &painter)
{
    painter.drawPolyline(mPaintData.data(), mPaintData.size());
}

QRect PlSingleCurve::updateRect()
{
    return mUpdateRect;
}

