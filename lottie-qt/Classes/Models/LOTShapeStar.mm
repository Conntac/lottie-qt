//
//  LOTShapeStar.m
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTShapeStar.h"

LOTShapeStar::LOTShapeStar(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    if (jsonDictionary.contains("or")) {
      outerRadius = new LOTKeyframeGroup(jsonDictionary.value("or"));
    }

    if (jsonDictionary.contains("os")) {
      outerRoundness = new LOTKeyframeGroup(jsonDictionary.value("os"));
    }

    if (jsonDictionary.contains("ir")) {
      innerRadius = new LOTKeyframeGroup(jsonDictionary.value("ir"));
    }

    if (jsonDictionary.contains("is")) {
      innerRoundness = new LOTKeyframeGroup(jsonDictionary.value("is"));
    }

    if (jsonDictionary.contains("p")) {
      position = new LOTKeyframeGroup(jsonDictionary.value("p"));
    }

    if (jsonDictionary.contains("pt")) {
      numberOfPoints = new LOTKeyframeGroup(jsonDictionary.value("pt"));
    }

    if (jsonDictionary.contains("r")) {
      rotation = new LOTKeyframeGroup(jsonDictionary.value("r"));
    }

    type = static_cast<LOTPolystarShape>(jsonDictionary.value("sy").toInt());
}
