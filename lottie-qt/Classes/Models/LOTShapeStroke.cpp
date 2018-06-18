//
//  LOTShapeStroke.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTShapeStroke.h"
#include "CGGeometry+LOTAdditions.h"

LOTShapeStroke::LOTShapeStroke(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    if (jsonDictionary.contains("c")) {
      color = new LOTKeyframeGroup(jsonDictionary.value("c"));
    }

    if (jsonDictionary.contains("w")) {
      width = new LOTKeyframeGroup(jsonDictionary.value("w"));
    }

    if (jsonDictionary.contains("o")) {
      opacity = new LOTKeyframeGroup(jsonDictionary.value("o"));
      opacity->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, 0, 100, 0, 1);
      });
    }

    capType = static_cast<LOTLineCapType>(jsonDictionary["lc"].toInt() - 1);
    joinType = static_cast<LOTLineJoinType>(jsonDictionary["lj"].toInt() - 1);

    fillEnabled = jsonDictionary.value("fillEnabled").toBool();

    QVariant dashOffset;
    QVariantList dashes = jsonDictionary["d"].toList();
    if (!dashes.isEmpty()) {
      for(const QVariant &variant : dashes) {
        QVariantMap dash = variant.toMap();

        if (dash.value("n").toString() == "o") {
          dashOffset = dash.value("v");
          continue;
        }
        // TODO DASH PATTERNS
        QVariant value = dash.value("v");
        LOTKeyframeGroup *keyframeGroup = new LOTKeyframeGroup(value);
        lineDashPattern.append(keyframeGroup);
      }
    }
    if (dashOffset.isValid()) {
      this->dashOffset = new LOTKeyframeGroup(dashOffset);
    }
}
