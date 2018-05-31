//
//  LOTColorInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTColorInterpolator.h"
#import "LOTPlatformCompat.h"
#import "UIColor+Expanded.h"

LOTColorInterpolator::LOTColorInterpolator(NSArray<LOTKeyframe *> *keyframes)
: LOTValueInterpolator(keyframes)
{
}

CGColorRef LOTColorInterpolator::colorForFrame(NSNumber *frame)
{
    CGFloat progress = progressForFrame(frame.floatValue);
    UIColor *returnColor;

    if (progress == 0) {
      returnColor = leadingKeyframe.colorValue;
    } else if (progress == 1) {
      returnColor = trailingKeyframe.colorValue;
    } else {
      returnColor = [UIColor LOT_colorByLerpingFromColor:leadingKeyframe.colorValue toColor:trailingKeyframe.colorValue amount:progress];
    }
    if (hasDelegateOverride()) {
      return [delegate colorForFrame:frame.floatValue
                       startKeyframe:leadingKeyframe.keyframeTime.floatValue
                         endKeyframe:trailingKeyframe.keyframeTime.floatValue
                interpolatedProgress:progress
                          startColor:leadingKeyframe.colorValue.CGColor
                            endColor:trailingKeyframe.colorValue.CGColor
                        currentColor:returnColor.CGColor];
    }

    return returnColor.CGColor;
}

void LOTColorInterpolator::setValueDelegate(id<LOTValueDelegate> delegate)
{
    Q_ASSERT_X(([delegate conformsToProtocol:@protocol(LOTColorValueDelegate)]), "setValueDelegate", "Color Interpolator set with incorrect callback type. Expected LOTColorValueDelegate");
    this->delegate = (id<LOTColorValueDelegate>)delegate;
}

bool LOTColorInterpolator::hasDelegateOverride() const
{
    return delegate != nil;
}
