//
//  LOTInterpolatorCallback.m
//  Lottie
//
//  Created by brandon_withrow on 1/5/18.
//  Copyright © 2018 Airbnb. All rights reserved.
//

#include "LOTInterpolatorCallback.h"
#include "CGGeometry+LOTAdditions.h"

LOTPointInterpolatorCallback::LOTPointInterpolatorCallback(const QPointF &fromPoint, const QPointF &toPoint)
: fromPoint(fromPoint)
, toPoint(toPoint)
{
}

QPointF LOTPointInterpolatorCallback::pointForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QPointF &startPoint, const QPointF &endPoint, const QPointF &interpolatedPoint)
{
    return LOT_PointInLine(fromPoint, toPoint, currentProgress);
}

LOTSizeInterpolatorCallback::LOTSizeInterpolatorCallback(const QSizeF &fromSize, const QSizeF &toSize)
: fromSize(fromSize)
, toSize(toSize)
{
}

QSizeF LOTSizeInterpolatorCallback::sizeForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QSizeF &startSize, const QSizeF &endSize, const QSizeF &interpolatedSize)
{
    QPointF from(fromSize.width(), fromSize.height());
    QPointF to(toSize.width(), toSize.height());
    QPointF returnPoint = LOT_PointInLine(from, to, currentProgress);
    return QSizeF(returnPoint.x(), returnPoint.y());
}

LOTFloatInterpolatorCallback::LOTFloatInterpolatorCallback(qreal fromFloat, qreal toFloat)
: fromFloat(fromFloat)
, toFloat(toFloat)
{
}

qreal LOTFloatInterpolatorCallback::floatValueForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, qreal startValue, qreal endValue, qreal interpolatedValue)
{
    return LOT_RemapValue(currentProgress, 0, 1, fromFloat, toFloat);
}
