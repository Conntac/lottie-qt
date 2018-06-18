//
//  LOTMask.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTMask.h"
#include "CGGeometry+LOTAdditions.h"

LOTMask::LOTMask(const QVariantMap &jsonDictionary)
{
    closed = jsonDictionary.value("cl").toBool();
    inverted = jsonDictionary.value("inv").toBool();

    QString mode = jsonDictionary.value("mode").toString();
    if (mode == "a") {
      maskMode = LOTMaskModeAdd;
    } else if (mode == "s") {
      maskMode = LOTMaskModeSubtract;
    } else if (mode == "i") {
      maskMode = LOTMaskModeIntersect;
    } else {
      maskMode = LOTMaskModeUnknown;
    }

    QVariantMap maskshape = jsonDictionary.value("pt").toMap();
    if (!maskshape.isEmpty()) {
      maskPath = new LOTKeyframeGroup(maskshape);
    }

    QVariantMap opacity = jsonDictionary.value("o").toMap();
    if (!opacity.isEmpty()) {
      this->opacity = new LOTKeyframeGroup(opacity);
      this->opacity->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, 0, 100, 0, 1);
      });
    }

    QVariantMap expansion = jsonDictionary.value("x").toMap();
    if (!expansion.isEmpty()) {
      this->expansion = new LOTKeyframeGroup(expansion);
    }
}
