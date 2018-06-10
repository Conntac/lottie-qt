//
//  LOTPointInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/12/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTPointInterpolator.h"
#import "CGGeometry+LOTAdditions.h"

LOTPointInterpolator::LOTPointInterpolator(NSArray<LOTKeyframe *> *keyframes)
: LOTValueInterpolator(keyframes)
{
}

QPointF LOTPointInterpolator::pointValueForFrame(qreal frame)
{
    CGFloat progress = progressForFrame(frame);
    QPointF returnPoint;
    if (progress == 0) {
      returnPoint = leadingKeyframe.pointValue;
    } else if (progress == 1) {
      returnPoint = trailingKeyframe.pointValue;
    } else if (!leadingKeyframe.spatialOutTangent.isNull() ||
               !trailingKeyframe.spatialInTangent.isNull()) {
      // Spatial Bezier path
      QPointF outTan = LOT_PointAddedToPoint(leadingKeyframe.pointValue, leadingKeyframe.spatialOutTangent);
      QPointF inTan = LOT_PointAddedToPoint(trailingKeyframe.pointValue, trailingKeyframe.spatialInTangent);
      returnPoint = LOT_PointInCubicCurve(leadingKeyframe.pointValue, outTan, inTan, trailingKeyframe.pointValue, progress);
    } else {
      returnPoint = LOT_PointInLine(leadingKeyframe.pointValue, trailingKeyframe.pointValue, progress);
    }
    if (hasDelegateOverride()) {
      returnPoint = QPointF::fromCGPoint([delegate pointForFrame:frame
                            startKeyframe:leadingKeyframe.keyframeTime.floatValue
                              endKeyframe:trailingKeyframe.keyframeTime.floatValue
                     interpolatedProgress:progress
                               startPoint:leadingKeyframe.pointValue.toCGPoint()
                                 endPoint:trailingKeyframe.pointValue.toCGPoint()
                             currentPoint:returnPoint.toCGPoint()]);
    }
    return returnPoint;
}

bool LOTPointInterpolator::hasDelegateOverride() const
{
    return delegate != nil;
}

void LOTPointInterpolator::setValueDelegate(id<LOTValueDelegate> delegate)
{
    Q_ASSERT_X(([delegate conformsToProtocol:@protocol(LOTPointValueDelegate)]), "setValueDelegate", "Point Interpolator set with incorrect callback type. Expected LOTPointValueDelegate");
    this->delegate = (id<LOTPointValueDelegate>)delegate;
}
