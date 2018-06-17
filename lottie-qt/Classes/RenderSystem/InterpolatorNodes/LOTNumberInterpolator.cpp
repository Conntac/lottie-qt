//
//  LOTNumberInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/11/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTNumberInterpolator.h"
#import "CGGeometry+LOTAdditions.h"

LOTNumberInterpolator::LOTNumberInterpolator(const QList<LOTKeyframe *> &keyframes)
: LOTValueInterpolator(keyframes)
{
}

qreal LOTNumberInterpolator::floatValueForFrame(qreal frame)
{
    qreal progress = progressForFrame(frame);
    qreal returnValue;
    if (progress == 0) {
      returnValue = leadingKeyframe->floatValue;
    } else if (progress == 1) {
      returnValue = trailingKeyframe->floatValue;
    } else {
      returnValue = LOT_RemapValue(progress, 0, 1, leadingKeyframe->floatValue, trailingKeyframe->floatValue);
    }
    if (hasDelegateOverride()) {
      return delegate->floatValueForFrame(frame,
                                          leadingKeyframe->keyframeTime,
                                          trailingKeyframe->keyframeTime,
                                          progress,
                                          leadingKeyframe->floatValue,
                                          trailingKeyframe->floatValue,
                                          returnValue);
    }

    return returnValue;
}

bool LOTNumberInterpolator::hasDelegateOverride() const
{
    return delegate != nil;
}

void LOTNumberInterpolator::setValueDelegate(LOTValueDelegate *delegate)
{
    Q_ASSERT_X(dynamic_cast<LOTNumberValueDelegate *>(delegate), "setValueDelegate", "Number Interpolator set with incorrect callback type. Expected LOTNumberValueDelegate");
    this->delegate = dynamic_cast<LOTNumberValueDelegate *>(delegate);
}
