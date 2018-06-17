//
//  LOTShapeRectangle.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTKeyframe.h"
#include "lotbase.h"

class LOTShapeRectangle : public LOTShapeItem
{
public:
    LOTShapeRectangle(const QVariantMap &jsonDictionary);

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *position = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *size = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *cornerRadius = nullptr;
//@property (nonatomic, readonly)
    bool reversed;
};
