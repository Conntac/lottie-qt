//
//  LOTShapeGradientFill.h
//  Lottie
//
//  Created by brandon_withrow on 7/26/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTKeyframe.h"
#include "lotbase.h"

enum LOTGradientType {
  LOTGradientTypeLinear,
  LOTGradientTypeRadial
};

class LOTShapeGradientFill : public LOTShapeItem
{
public:
    LOTShapeGradientFill(const QVariantMap &jsonDictionary);
    ~LOTShapeGradientFill();

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly)
    int numberOfColors = 0;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *startPoint = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *endPoint = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *gradient = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *opacity = nullptr;
//@property (nonatomic, readonly)
    bool evenOddFillRule;
//@property (nonatomic, readonly)
    LOTGradientType type;

};
