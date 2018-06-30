//
//  LOTShapePath.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#pragma once

#include "LOTKeyframe.h"
#include "lotbase.h"

class LOTShapePath : public LOTShapeItem
{
public:
    LOTShapePath(const QVariantMap &jsonDictionary);
    ~LOTShapePath();

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly)
    bool closed;
//@property (nonatomic, readonly)
    int index = -1;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *shapePath = nullptr;
};
