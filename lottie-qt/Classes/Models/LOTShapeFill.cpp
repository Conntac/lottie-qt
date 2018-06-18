//
//  LOTShapeFill.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTShapeFill.h"
#include "CGGeometry+LOTAdditions.h"

LOTShapeFill::LOTShapeFill(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    if (jsonDictionary.contains("c")) {
      color = new LOTKeyframeGroup(jsonDictionary.value("c"));
    }

    if (jsonDictionary.contains("o")) {
      opacity = new LOTKeyframeGroup(jsonDictionary.value("o"));
      opacity->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, 0, 100, 0, 1);
      });
    }

    int evenOdd = jsonDictionary.value("r").toInt();
    if (evenOdd == 2) {
      evenOddFillRule = true;
    } else {
      evenOddFillRule = false;
    }

    fillEnabled = jsonDictionary.value("fillEnabled").toBool();
}
