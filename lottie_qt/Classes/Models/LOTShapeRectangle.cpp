//
//  LOTShapeRectangle.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTShapeRectangle.h"

LOTShapeRectangle::LOTShapeRectangle(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    if (jsonDictionary.contains("p")) {
      position = new LOTKeyframeGroup(jsonDictionary.value("p"));
    }

    if (jsonDictionary.contains("r")) {
      cornerRadius = new LOTKeyframeGroup(jsonDictionary.value("r"));
    }

    if (jsonDictionary.contains("s")) {
      size = new LOTKeyframeGroup(jsonDictionary.value("s"));
    }

    reversed = jsonDictionary.value("d").toInt() == 3;
}

LOTShapeRectangle::~LOTShapeRectangle()
{
    delete position;
    delete size;
    delete cornerRadius;
}
