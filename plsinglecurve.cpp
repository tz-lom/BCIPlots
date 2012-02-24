#include "plsinglecurve.h"
#include <math.h>
#include <QDebug>

PlSingleCurve::PlSingleCurve():
    mWidth(0),
    mSize(1),
    mMode(PlSingleCurve::Cyclic)
{
    resize(1,1);
}


int PlSingleCurve::count()
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
        if(mMeanedPoints >= mItemPerPixel)
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

                mPaintData[mFront++].setY(avg);
                if(mFront>=mPaintData.size()) mFront=0;
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
        /*if(mItemPerPixel>1)
        {

        }
        else
        {
            int lSize = mPaintData.size();

            if(size>=lSize)
            {
                data+=step*(size-lSize);
                size=lSize;
            }

            for(int t=size; t<lSize; ++t)
            {
                mPaintData[t-size].setY(mPaintData[t].y());
            }

            int lPos = lSize-size;
            for(int t=0; t<size; ++t,data+=step)
            {
                mPaintData[lPos+t].setY(*data);
            }
        }*/
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


void PlSingleCurve::resize(int width, int count)
{
    if(count<1) return;
    qreal itemPerPixel = (qreal)count/width;
    if(itemPerPixel>1)
    {
        // performe resampling

        QVector<QPointF> newData;
        newData.resize(width);
        for(int t=0;t<width;++t)
        {
            newData[t].setX(t);
        }

        mPaintData = newData;
    }
    else
    {
        mPaintData.resize(count);
        for(int t=0;t<count;++t)
        {
            mPaintData[t].setX(t/itemPerPixel);
        }
    }
    mItemPerPixel = itemPerPixel;
    mWidth = width;
    mSize = count;
    if(mFront>mPaintData.size()) mFront = 0;
    mMean = 0;
    mMeanedPoints = 0;

    if(mMode == Pushing)
    {
        mUpdateRect.setLeft( 0 );
        mUpdateRect.setRight( width );
    }
}

void PlSingleCurve::draw(QPainter &painter)
{
    painter.drawPolyline(mPaintData.data(), mPaintData.size());
}

QRect PlSingleCurve::updateRect()
{
    return mUpdateRect;
}

