//
//  LOTMask.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#pragma once

#include "LOTKeyframe.h"

enum LOTMaskMode {
  LOTMaskModeAdd,
  LOTMaskModeSubtract,
  LOTMaskModeIntersect,
  LOTMaskModeUnknown
};

class LOTMask
{
public:
    LOTMask(const QVariantMap &jsonDictionary);
    ~LOTMask();

//@property (nonatomic, readonly)
    bool closed;
//@property (nonatomic, readonly)
    bool inverted;
//@property (nonatomic, readonly)
    LOTMaskMode maskMode;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *maskPath = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *opacity = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *expansion = nullptr;
};
