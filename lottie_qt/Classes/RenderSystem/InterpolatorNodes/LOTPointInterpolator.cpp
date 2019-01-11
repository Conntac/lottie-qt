//
//  LOTPointInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/12/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTPointInterpolator.h"
#include "CGGeometry+LOTAdditions.h"

LOTPointInterpolator::LOTPointInterpolator(const QList<LOTKeyframe *> &keyframes)
: LOTValueInterpolator(keyframes)
{
}

QPointF LOTPointInterpolator::pointValueForFrame(qreal frame)
{
    qreal progress = progressForFrame(frame);
    QPointF returnPoint;
    if (progress == 0) {
      returnPoint = leadingKeyframe->pointValue;
    } else if (progress == 1) {
      returnPoint = trailingKeyframe->pointValue;
    } else if (!leadingKeyframe->spatialOutTangent.isNull() ||
               !trailingKeyframe->spatialInTangent.isNull()) {
      // Spatial Bezier path
      QPointF outTan = LOT_PointAddedToPoint(leadingKeyframe->pointValue, leadingKeyframe->spatialOutTangent);
      QPointF inTan = LOT_PointAddedToPoint(trailingKeyframe->pointValue, trailingKeyframe->spatialInTangent);
      returnPoint = LOT_PointInCubicCurve(leadingKeyframe->pointValue, outTan, inTan, trailingKeyframe->pointValue, progress);
    } else {
      returnPoint = LOT_PointInLine(leadingKeyframe->pointValue, trailingKeyframe->pointValue, progress);
    }
    if (hasDelegateOverride()) {
      returnPoint = delegate->pointForFrame(frame,
                                            leadingKeyframe->keyframeTime,
                                            trailingKeyframe->keyframeTime,
                                            progress,
                                            leadingKeyframe->pointValue,
                                            trailingKeyframe->pointValue,
                                            returnPoint);
    }
    return returnPoint;
}

bool LOTPointInterpolator::hasDelegateOverride() const
{
    return delegate != nullptr;
}

void LOTPointInterpolator::setValueDelegate(LOTValueDelegate *delegate)
{
    Q_ASSERT_X(dynamic_cast<LOTPointValueDelegate *>(delegate), "setValueDelegate", "Point Interpolator set with incorrect callback type. Expected LOTPointValueDelegate");
    this->delegate = dynamic_cast<LOTPointValueDelegate *>(delegate);
}
