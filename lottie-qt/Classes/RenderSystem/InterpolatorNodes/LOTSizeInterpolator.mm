//
//  LOTSizeInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTSizeInterpolator.h"
#import "CGGeometry+LOTAdditions.h"

LOTSizeInterpolator::LOTSizeInterpolator(const QList<LOTKeyframe *> &keyframes)
: LOTValueInterpolator(keyframes)
{
}

QSizeF LOTSizeInterpolator::sizeValueForFrame(qreal frame)
{
    CGFloat progress = progressForFrame(frame);
    QSizeF returnSize;
    if (progress == 0) {
      returnSize = leadingKeyframe->sizeValue;
    }else if (progress == 1) {
      returnSize = trailingKeyframe->sizeValue;
    } else {
      returnSize = QSizeF(LOT_RemapValue(progress, 0, 1, leadingKeyframe->sizeValue.width(), trailingKeyframe->sizeValue.width()),
                          LOT_RemapValue(progress, 0, 1, leadingKeyframe->sizeValue.height(), trailingKeyframe->sizeValue.height()));
    }
    if (hasDelegateOverride()) {
      returnSize = delegate->sizeForFrame(frame,
                                          leadingKeyframe->keyframeTime,
                                          trailingKeyframe->keyframeTime,
                                          progress,
                                          leadingKeyframe->sizeValue,
                                          trailingKeyframe->sizeValue,
                                          returnSize);
    }
    return returnSize;
}

bool LOTSizeInterpolator::hasDelegateOverride() const
{
    return delegate != nil;
}

void LOTSizeInterpolator::setValueDelegate(LOTValueDelegate *delegate)
{
    Q_ASSERT_X(dynamic_cast<LOTSizeValueDelegate *>(delegate), "setValueDelegate", "Size Interpolator set with incorrect callback type. Expected LOTSizeValueDelegate");
    this->delegate = dynamic_cast<LOTSizeValueDelegate *>(delegate);
}
