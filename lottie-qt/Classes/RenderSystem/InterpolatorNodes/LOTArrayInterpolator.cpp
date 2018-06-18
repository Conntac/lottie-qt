//
//  LOTArrayInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTArrayInterpolator.h"
#include "CGGeometry+LOTAdditions.h"

LOTArrayInterpolator::LOTArrayInterpolator(const QList<LOTKeyframe *> &keyframes)
: LOTValueInterpolator(keyframes)
{
}

QList<qreal> LOTArrayInterpolator::numberArrayForFrame(qreal frame)
{
    qreal progress = progressForFrame(frame);
    if (progress == 0) {
      return leadingKeyframe->arrayValue;
    }
    if (progress == 1) {
      return trailingKeyframe->arrayValue;
    }
    QList<qreal> returnArray;
    for (int i = 0; i < leadingKeyframe->arrayValue.size(); i ++) {
      qreal from = leadingKeyframe->arrayValue.at(i);
      qreal to = trailingKeyframe->arrayValue.at(i);
      qreal value = LOT_RemapValue(progress, 0, 1, from, to);
      returnArray.append(value);
    }
    return returnArray;
}
