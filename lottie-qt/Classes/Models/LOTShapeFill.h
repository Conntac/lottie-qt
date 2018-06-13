//
//  LOTShapeFill.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LOTKeyframe.h"

#include "lotbase.h"

class LOTShapeFill : public LOTShapeItem
{
public:
    LOTShapeFill(const QVariantMap &jsonDictionary);

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly)
    bool fillEnabled;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *color = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *opacity = nullptr;
//@property (nonatomic, readonly)
    bool evenOddFillRule;
};
