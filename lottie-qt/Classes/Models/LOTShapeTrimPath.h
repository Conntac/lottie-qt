//
//  LOTShapeTrimPath.h
//  LottieAnimator
//
//  Created by brandon_withrow on 7/26/16.
//  Copyright © 2016 Brandon Withrow. All rights reserved.
//

#pragma once

#include "LOTKeyframe.h"
#include "lotbase.h"

class LOTShapeTrimPath : public LOTShapeItem
{
public:
    LOTShapeTrimPath(const QVariantMap &jsonDictionary);

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *start = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *end = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *offset = nullptr;
};
