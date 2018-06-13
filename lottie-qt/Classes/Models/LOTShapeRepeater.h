//
//  LOTShapeRepeater.h
//  Lottie
//
//  Created by brandon_withrow on 7/28/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LOTKeyframe.h"
#include "lotbase.h"

class LOTShapeRepeater : public LOTShapeItem
{
public:
    LOTShapeRepeater(const QVariantMap &jsonDictionary);

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *copies = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *offset = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *anchorPoint = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *scale = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *position = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *rotation = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *startOpacity = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *endOpacity = nullptr;
};

