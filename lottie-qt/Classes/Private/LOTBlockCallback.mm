//
//  LOTBlockCallback.m
//  Lottie
//
//  Created by brandon_withrow on 12/15/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTBlockCallback.h"

LOTColorBlockCallback::LOTColorBlockCallback(LOTColorValueCallbackBlock block)
: callback(block)
{
}

QColor LOTColorBlockCallback::colorForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QColor &startColor, const QColor &endColor, const QColor &interpolatedColor)
{
    return callback(currentFrame, startKeyframe, endKeyframe, interpolatedProgress, startColor, endColor, interpolatedColor);
}


LOTNumberBlockCallback::LOTNumberBlockCallback(LOTNumberValueCallbackBlock block)
: callback(block)
{
}

qreal LOTNumberBlockCallback::floatValueForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, qreal startValue, qreal endValue, qreal interpolatedValue)
{
    return callback(currentFrame, startKeyframe, endKeyframe, interpolatedProgress, startValue, endValue, interpolatedValue);
}

LOTPointBlockCallback::LOTPointBlockCallback(LOTPointValueCallbackBlock block)
: callback(block)
{
}

QPointF LOTPointBlockCallback::pointForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QPointF &startPoint, const QPointF &endPoint, const QPointF &interpolatedPoint)
{
    return callback(currentFrame, startKeyframe, endKeyframe, interpolatedProgress, startPoint, endPoint, interpolatedPoint);
}

LOTSizeBlockCallback::LOTSizeBlockCallback(LOTSizeValueCallbackBlock block)
: callback(block)
{
}

QSizeF LOTSizeBlockCallback::sizeForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QSizeF &startSize, const QSizeF &endSize, const QSizeF &interpolatedSize)
{
    return callback(currentFrame, startKeyframe, endKeyframe, interpolatedProgress, startSize, endSize, interpolatedSize);
}

LOTPathBlockCallback::LOTPathBlockCallback(LOTPathValueCallbackBlock block)
: callback(block)
{
}

QPainterPath LOTPathBlockCallback::pathForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress)
{
    return callback(currentFrame, startKeyframe, endKeyframe, interpolatedProgress);
}
