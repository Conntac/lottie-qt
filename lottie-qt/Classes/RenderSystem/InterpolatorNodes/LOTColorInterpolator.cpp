//
//  LOTColorInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTColorInterpolator.h"

#include <QColor>

/*
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
*/

template<class T>
inline const T& clamp(const T& x, const T& upper, const T& lower) {
    return qMin(upper, qMax(x, lower));
}

static QColor LOT_colorByLerpingFromColor(QColor fromColor, QColor toColor, qreal amount) {
  Q_ASSERT_X(toColor.isValid() && fromColor.isValid(), "LOT_colorByLerpingFromColor", "Passing Nil Color");
  amount = clamp(amount, 0.0, 1.0);

  qreal fromComponents[4];
  fromColor.getRgbF(&fromComponents[0], &fromComponents[1], &fromComponents[2], &fromComponents[3]);
  qreal toComponents[4];
  toColor.getRgbF(&toComponents[0], &toComponents[1], &toComponents[2], &toComponents[3]);

  qreal r = fromComponents[0] + ((toComponents[0] - fromComponents[0]) * amount);
  qreal g = fromComponents[1] + ((toComponents[1] - fromComponents[1]) * amount);
  qreal b = fromComponents[2] + ((toComponents[2] - fromComponents[2]) * amount);
  qreal a = fromComponents[3] + ((toComponents[3] - fromComponents[3]) * amount);

  QColor c;
  c.setRgbF(r, g, b, a);
  return c;
}

LOTColorInterpolator::LOTColorInterpolator(const QList<LOTKeyframe *> &keyframes)
: LOTValueInterpolator(keyframes)
{
}

QColor LOTColorInterpolator::colorForFrame(qreal frame)
{
    qreal progress = progressForFrame(frame);
    QColor returnColor;

    if (progress == 0) {
      returnColor = leadingKeyframe->colorValue;
    } else if (progress == 1) {
      returnColor = trailingKeyframe->colorValue;
    } else {
      returnColor = LOT_colorByLerpingFromColor(leadingKeyframe->colorValue, trailingKeyframe->colorValue, progress);
    }
    if (hasDelegateOverride()) {
      return delegate->colorForFrame(frame,
                                     leadingKeyframe->keyframeTime,
                                     trailingKeyframe->keyframeTime,
                                     progress,
                                     leadingKeyframe->colorValue,
                                     trailingKeyframe->colorValue,
                                     returnColor);
    }

    return returnColor;
}

void LOTColorInterpolator::setValueDelegate(LOTValueDelegate *delegate)
{
    Q_ASSERT_X(dynamic_cast<LOTColorValueDelegate *>(delegate), "setValueDelegate", "Color Interpolator set with incorrect callback type. Expected LOTColorValueDelegate");
    this->delegate = dynamic_cast<LOTColorValueDelegate *>(delegate);
}

bool LOTColorInterpolator::hasDelegateOverride() const
{
    return delegate != nullptr;
}
