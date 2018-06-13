//
//  LOTPathInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTPathInterpolator.h"
#import "CGGeometry+LOTAdditions.h"

LOTPathInterpolator::LOTPathInterpolator(const QList<LOTKeyframe *> &keyframes)
: LOTValueInterpolator(keyframes)
{
}

QSharedPointer<LOTBezierPath> LOTPathInterpolator::pathForFrame(qreal frame, bool cacheLengths)
{
    CGFloat progress = progressForFrame(frame);
    if (hasDelegateOverride()) {
      CGPathRef callBackPath = [delegate pathForFrame:frame
                                             startKeyframe:leadingKeyframe->keyframeTime
                                               endKeyframe:trailingKeyframe->keyframeTime
                                      interpolatedProgress:progress];
      return QSharedPointer<LOTBezierPath>::create(callBackPath);
    }

    QSharedPointer<LOTBezierPath> returnPath = returnPath.create();
    returnPath->cacheLengths = cacheLengths;
    QSharedPointer<LOTBezierData> leadingData;
    if (leadingKeyframe) {
        leadingData = leadingKeyframe->pathData;
    }
    QSharedPointer<LOTBezierData> trailingData;
    if (trailingKeyframe) {
        trailingData = trailingKeyframe->pathData;
    }
    int vertexCount = leadingData ? leadingData->count() : trailingData->count();
    bool closePath = leadingData ? leadingData->closed() : trailingData->closed();
    QPointF cp1;
    QPointF cp2, p1, cp3;
    QPointF startPoint;
    QPointF startInTangent;
    for (int i = 0; i < vertexCount; i++) {
      if (progress == 0) {
        cp2 = leadingData->inTangentAtIndex(i);
        p1 = leadingData->vertexAtIndex(i);
        cp3 = leadingData->outTangentAtIndex(i);
      } else if (progress == 1) {
        cp2 = trailingData->inTangentAtIndex(i);
        p1 = trailingData->vertexAtIndex(i);
        cp3 = trailingData->outTangentAtIndex(i);
      } else {
        cp2 = LOT_PointInLine(leadingData->inTangentAtIndex(i),
                              trailingData->inTangentAtIndex(i),
                              progress);
        p1 = LOT_PointInLine(leadingData->vertexAtIndex(i),
                             trailingData->vertexAtIndex(i),
                             progress);
        cp3 = LOT_PointInLine(leadingData->outTangentAtIndex(i),
                              trailingData->outTangentAtIndex(i),
                              progress);
      }
      if (i == 0) {
        startPoint = p1;
        startInTangent = cp2;
        returnPath->LOT_moveToPoint(p1);
      } else {
        returnPath->LOT_addCurveToPoint(p1, cp1, cp2);
      }
      cp1 = cp3;
    }

    if (closePath) {
      returnPath->LOT_addCurveToPoint(startPoint, cp3, startInTangent);
      returnPath->LOT_closePath();
    }

    return returnPath;
}


bool LOTPathInterpolator::hasDelegateOverride() const
{
    return delegate != nil;
}

void LOTPathInterpolator::setValueDelegate(id<LOTValueDelegate> delegate)
{
    Q_ASSERT_X(([delegate conformsToProtocol:@protocol(LOTPathValueDelegate)]), "setValueDelegate", "Path Interpolator set with incorrect callback type. Expected LOTPathValueDelegate");
    this->delegate = (id<LOTPathValueDelegate>)delegate;
}
