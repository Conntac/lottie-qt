//
//  LOTShapePath.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTShapePath.h"

LOTShapePath::LOTShapePath(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    index = jsonDictionary["ind"].toInt();
    closed = jsonDictionary["closed"].toBool();
    if (jsonDictionary.contains("ks")) {
      shapePath = new LOTKeyframeGroup(jsonDictionary.value("ks"));
    }
}
