//
//  LOTShapeCircle.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTShapeCircle.h"

LOTShapeCircle::LOTShapeCircle(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    QVariantMap position = jsonDictionary["p"].toMap();
    if (!position.isEmpty()) {
      this->position = new LOTKeyframeGroup(position);
    }

    QVariantMap size = jsonDictionary["s"].toMap();
    if (!size.isEmpty()) {
      this->size = new LOTKeyframeGroup(size);
    }
    reversed = (jsonDictionary.value("d").toInt() == 3);
}

LOTShapeCircle::~LOTShapeCircle()
{
    delete position;
    delete size;
}
