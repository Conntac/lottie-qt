//
//  LOTMask.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LOTKeyframe.h"

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

//@property (nonatomic, readonly)
    BOOL closed;
//@property (nonatomic, readonly)
    BOOL inverted;
//@property (nonatomic, readonly)
    LOTMaskMode maskMode;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *maskPath = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *opacity = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *expansion = nullptr;
};
