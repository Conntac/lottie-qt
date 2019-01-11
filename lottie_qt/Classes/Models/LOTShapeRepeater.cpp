//
//  LOTShapeRepeater.m
//  Lottie
//
//  Created by brandon_withrow on 7/28/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTShapeRepeater.h"
#include "CGGeometry+LOTAdditions.h"

LOTShapeRepeater::LOTShapeRepeater(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    if (jsonDictionary.contains("c")) {
      copies = new LOTKeyframeGroup(jsonDictionary.value("c"));
    }

    if (jsonDictionary.contains("o")) {
      offset = new LOTKeyframeGroup(jsonDictionary.value("o"));
    }

    QVariantMap transform = jsonDictionary["tr"].toMap();

    if (transform.contains("r")) {
      rotation = new LOTKeyframeGroup(transform.value("r"));
      rotation->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_DegreesToRadians(inValue);
      });
    }

    if (transform.contains("so")) {
      startOpacity = new LOTKeyframeGroup(transform.value("so"));
      startOpacity->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, 0, 100, 0, 1);
      });
    }

    if (transform.contains("eo")) {
      endOpacity = new LOTKeyframeGroup(transform.value("eo"));
      endOpacity->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, 0, 100, 0, 1);
      });
    }

    if (transform.contains("a")) {
      anchorPoint = new LOTKeyframeGroup(transform.value("a"));
    }

    if (transform.contains("p")) {
      position = new LOTKeyframeGroup(transform.value("p"));
    }

    if (transform.contains("s")) {
      scale = new LOTKeyframeGroup(transform.value("s"));
      scale->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, -100, 100, -1, 1);
      });
    }
}

LOTShapeRepeater::~LOTShapeRepeater()
{
    delete copies;
    delete offset;
    delete anchorPoint;
    delete scale;
    delete position;
    delete rotation;
    delete startOpacity;
    delete endOpacity;
}
