//
//  LOTShapeStar.h
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTKeyframe.h"
#include "lotbase.h"

enum LOTPolystarShape {
  LOTPolystarShapeNone,
  LOTPolystarShapeStar,
  LOTPolystarShapePolygon
};

class LOTShapeStar : public LOTShapeItem
{
public:
    LOTShapeStar(const QVariantMap &jsonDictionary);

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *outerRadius = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *outerRoundness = nullptr;

//@property (nonatomic, readonly)
    LOTKeyframeGroup *innerRadius = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *innerRoundness = nullptr;

//@property (nonatomic, readonly)
    LOTKeyframeGroup *position = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *numberOfPoints = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *rotation = nullptr;

//@property (nonatomic, readonly)
    LOTPolystarShape type;
};
