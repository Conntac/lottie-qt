//
//  LOTShapeGradientFill.m
//  Lottie
//
//  Created by brandon_withrow on 7/26/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTShapeGradientFill.h"
#import "CGGeometry+LOTAdditions.h"

LOTShapeGradientFill::LOTShapeGradientFill(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    int type = jsonDictionary.value("t").toInt();

    if (type != 1) {
      this->type = LOTGradientTypeRadial;
    } else {
      this->type = LOTGradientTypeLinear;
    }

    if (jsonDictionary.contains("s")) {
      startPoint = new LOTKeyframeGroup(jsonDictionary.value("s"));
    }

    if (jsonDictionary.contains("e")) {
      endPoint = new LOTKeyframeGroup(jsonDictionary.value("e"));
    }

    QVariantMap gradient = jsonDictionary["g"].toMap();
    if (!gradient.isEmpty()) {
      QVariantMap unwrappedGradient = gradient["k"].toMap();
      this->numberOfColors = gradient["p"].toInt();
      this->gradient = new LOTKeyframeGroup(unwrappedGradient);
    }

    if (jsonDictionary.contains("o")) {
      opacity = new LOTKeyframeGroup(jsonDictionary.value("o"));
      opacity->remapKeyframesWithBlock([](CGFloat inValue) -> qreal {
        return LOT_RemapValue(inValue, 0, 100, 0, 1);
      });
    }

    int evenOdd = jsonDictionary.value("r").toInt();
    if (evenOdd == 2) {
      evenOddFillRule = true;
    } else {
      evenOddFillRule = false;
    }
}
