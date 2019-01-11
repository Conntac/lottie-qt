//
//  LOTShapeTransform.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#pragma once

#include "LOTKeyframe.h"
#include "lotbase.h"

class LOTShapeTransform : public LOTShapeItem
{
public:
    LOTShapeTransform(const QVariantMap &jsonDictionary);
    ~LOTShapeTransform();

    QString toString() const;

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *position = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *anchor = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *scale = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *rotation = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *opacity = nullptr;

};
