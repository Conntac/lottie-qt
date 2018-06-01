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

#include <QColor>

QColor qcolorFromCGColor(CGColorRef cgcolor)
{
    QColor pc;
    CGColorSpaceModel model = CGColorSpaceGetModel(CGColorGetColorSpace(cgcolor));
    const CGFloat *components = CGColorGetComponents(cgcolor);
    if (model == kCGColorSpaceModelRGB) {
        pc.setRgbF(components[0], components[1], components[2], components[3]);
    } else if (model == kCGColorSpaceModelCMYK) {
        pc.setCmykF(components[0], components[1], components[2], components[3]);
    } else if (model == kCGColorSpaceModelMonochrome) {
        pc.setRgbF(components[0], components[0], components[0], components[1]);
    } else {
        // Colorspace we can't deal with.
        qWarning("Qt: qcolorFromCGColor: cannot convert from colorspace model: %d", model);
        Q_ASSERT(false);
    }
    return pc;
}

LOTColorInterpolator::LOTColorInterpolator(NSArray<LOTKeyframe *> *keyframes)
: LOTValueInterpolator(keyframes)
{
}

QColor LOTColorInterpolator::colorForFrame(qreal frame)
{
    CGFloat progress = progressForFrame(frame);
    UIColor *returnColor;

    if (progress == 0) {
      returnColor = leadingKeyframe.colorValue;
    } else if (progress == 1) {
      returnColor = trailingKeyframe.colorValue;
    } else {
      returnColor = [UIColor LOT_colorByLerpingFromColor:leadingKeyframe.colorValue toColor:trailingKeyframe.colorValue amount:progress];
    }
    if (hasDelegateOverride()) {
      return qcolorFromCGColor([delegate colorForFrame:frame
                       startKeyframe:leadingKeyframe.keyframeTime.floatValue
                         endKeyframe:trailingKeyframe.keyframeTime.floatValue
                interpolatedProgress:progress
                          startColor:leadingKeyframe.colorValue.CGColor
                            endColor:trailingKeyframe.colorValue.CGColor
                        currentColor:returnColor.CGColor]);
    }

    return qcolorFromCGColor(returnColor.CGColor);
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
