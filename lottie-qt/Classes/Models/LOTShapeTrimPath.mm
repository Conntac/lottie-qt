//
//  LOTShapeTrimPath.m
//  LottieAnimator
//
//  Created by brandon_withrow on 7/26/16.
//  Copyright © 2016 Brandon Withrow. All rights reserved.
//

#import "LOTShapeTrimPath.h"

LOTShapeTrimPath::LOTShapeTrimPath(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    if (jsonDictionary.contains("s")) {
      start = new LOTKeyframeGroup(jsonDictionary.value("s"));
    }

    if (jsonDictionary.contains("e")) {
      end = new LOTKeyframeGroup(jsonDictionary.value("e"));
    }

    if (jsonDictionary.contains("o")) {
      offset = new LOTKeyframeGroup(jsonDictionary.value("o"));
    }
}
