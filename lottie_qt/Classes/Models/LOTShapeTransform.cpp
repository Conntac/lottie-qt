//
//  LOTShapeTransform.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTShapeTransform.h"
#include "LOTHelpers.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logLOTShapeTransform, "lottie.shape_transform")

/*
- (NSString *)description {
  return [NSString stringWithFormat:@"LOTShapeTransform \"Position: %@ Anchor: %@ Scale: %@ Rotation: %@ Opacity: %@\"", _position.description, _anchor.description, _scale.description, _rotation.description, _opacity.description];
}
*/

LOTShapeTransform::LOTShapeTransform(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    if (jsonDictionary.contains("p")) {
      position = new LOTKeyframeGroup(jsonDictionary.value("p"));
    }

    if (jsonDictionary.contains("a")) {
      anchor = new LOTKeyframeGroup(jsonDictionary.value("a"));
    }

    if (jsonDictionary.contains("s")) {
      scale = new LOTKeyframeGroup(jsonDictionary.value("s"));
      scale->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, -100, 100, -1, 1);
      });
    }

    if (jsonDictionary.contains("r")) {
      rotation = new LOTKeyframeGroup(jsonDictionary.value("r"));
      rotation->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_DegreesToRadians(inValue);
      });
    }

    if (jsonDictionary.contains("o")) {
      opacity = new LOTKeyframeGroup(jsonDictionary.value("o"));
      opacity->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, 0, 100, 0, 1);
      });
    }

    QVariantMap skew = jsonDictionary["sk"].toMap();
    bool hasSkew = (jsonDictionary.contains("sk") && skew.value("k").toReal() != 0.0);
    QVariantMap skewAxis = jsonDictionary["sa"].toMap();
    bool hasSkewAxis = (jsonDictionary.contains("sa") && skewAxis.value("k").toReal() != 0.0);

    if (hasSkew || hasSkewAxis) {
        qCWarning(logLOTShapeTransform) << "skew is not supported:" << keyname;
    }
}

LOTShapeTransform::~LOTShapeTransform()
{
    delete position;
    delete anchor;
    delete scale;
    delete rotation;
    delete opacity;
}

/*
QString LOTShapeTransform::toString() const
{
    return QString("LOTShapeTransform \"Position: %1 Anchor: %2 Scale: %3 Rotation: %4 Opacity: %5\"")
            .arg(_position->toString())
            .arg(_anchor.description)
            .arg(_scale.description)
            .arg(_rotation.description)
            .arg(_opacity.description);
}
*/
