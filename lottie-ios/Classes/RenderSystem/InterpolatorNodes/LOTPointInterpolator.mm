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
    CGPoint returnPoint;
    if (progress == 0) {
      returnPoint = leadingKeyframe.pointValue;
    } else if (progress == 1) {
      returnPoint = trailingKeyframe.pointValue;
    } else if (!CGPointEqualToPoint(leadingKeyframe.spatialOutTangent, CGPointZero) ||
               !CGPointEqualToPoint(trailingKeyframe.spatialInTangent, CGPointZero)) {
      // Spatial Bezier path
      CGPoint outTan = LOT_PointAddedToPoint(leadingKeyframe.pointValue, leadingKeyframe.spatialOutTangent);
      CGPoint inTan = LOT_PointAddedToPoint(trailingKeyframe.pointValue, trailingKeyframe.spatialInTangent);
      returnPoint = LOT_PointInCubicCurve(leadingKeyframe.pointValue, outTan, inTan, trailingKeyframe.pointValue, progress);
    } else {
      returnPoint = LOT_PointInLine(leadingKeyframe.pointValue, trailingKeyframe.pointValue, progress);
    }
    if (hasDelegateOverride()) {
      returnPoint = [delegate pointForFrame:frame
                            startKeyframe:leadingKeyframe.keyframeTime.floatValue
                              endKeyframe:trailingKeyframe.keyframeTime.floatValue
                     interpolatedProgress:progress
                               startPoint:leadingKeyframe.pointValue
                                 endPoint:trailingKeyframe.pointValue
                             currentPoint:returnPoint];
    }
    return QPointF::fromCGPoint(returnPoint);
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
