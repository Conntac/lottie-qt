//
//  LOTCircleAnimator.m
//  Lottie
//
//  Created by brandon_withrow on 7/19/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTCircleAnimator.h"

#include <QSharedPointer>

const CGFloat kLOTEllipseControlPointPercentage = 0.55228;

LOTCircleAnimator::LOTCircleAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeCircle *shapeCircle)
: LOTAnimatorNode(inputNode, shapeCircle.keyname)
{
    _centerInterpolator = _centerInterpolator.create(shapeCircle.position.keyframes);
    _sizeInterpolator = _sizeInterpolator.create(shapeCircle.size.keyframes);
    _reversed = shapeCircle.reversed;
}

QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTCircleAnimator::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Size", _sizeInterpolator);
    map.insert("Position", _centerInterpolator);
    return map;
}

bool LOTCircleAnimator::needsUpdateForFrame(qreal frame)
{
    return _centerInterpolator->hasUpdateForFrame(frame) || _sizeInterpolator->hasUpdateForFrame(frame);
}

void LOTCircleAnimator::performLocalUpdate()
{
    // Unfortunately we HAVE to manually build out the ellipse.
    // Every Apple method constructs from the 3 o-clock position
    // After effects constructs from the Noon position.
    // After effects does clockwise, but also has a flag for reversed.
    QPointF center = _centerInterpolator->pointValueForFrame(currentFrame);
    QPointF size = _sizeInterpolator->pointValueForFrame(currentFrame);

    CGFloat halfWidth = size.x() / 2;
    CGFloat halfHeight = size.y() / 2;

    if (_reversed) {
      halfWidth = halfWidth * -1;
    }

    QPointF circleQ1(center.x(), center.y() - halfHeight);
    QPointF circleQ2(center.x() + halfWidth, center.y());
    QPointF circleQ3(center.x(), center.y() + halfHeight);
    QPointF circleQ4(center.x() - halfWidth, center.y());

    CGFloat cpW = halfWidth * kLOTEllipseControlPointPercentage;
    CGFloat cpH = halfHeight * kLOTEllipseControlPointPercentage;

    LOTBezierPath *path = [[LOTBezierPath alloc] init];
    path.cacheLengths = pathShouldCacheLengths();
    [path LOT_moveToPoint:circleQ1];
    [path LOT_addCurveToPoint:circleQ2 controlPoint1:QPointF(circleQ1.x() + cpW, circleQ1.y()) controlPoint2:QPointF(circleQ2.x(), circleQ2.y() - cpH)];

    [path LOT_addCurveToPoint:circleQ3 controlPoint1:QPointF(circleQ2.x(), circleQ2.y() + cpH) controlPoint2:QPointF(circleQ3.x() + cpW, circleQ3.y())];

    [path LOT_addCurveToPoint:circleQ4 controlPoint1:QPointF(circleQ3.x() - cpW, circleQ3.y()) controlPoint2:QPointF(circleQ4.x(), circleQ4.y() + cpH)];

    [path LOT_addCurveToPoint:circleQ1 controlPoint1:QPointF(circleQ4.x(), circleQ4.y() - cpH) controlPoint2:QPointF(circleQ1.x() - cpW, circleQ1.y())];

    setLocalPath(path);
}
