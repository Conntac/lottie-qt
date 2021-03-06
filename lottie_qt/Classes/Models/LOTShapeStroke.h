//
//  LOTShapeStroke.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/15/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#pragma once

#include "LOTKeyframe.h"
#include "lotbase.h"

enum LOTLineCapType {
  LOTLineCapTypeButt,
  LOTLineCapTypeRound,
  LOTLineCapTypeUnknown
};

enum LOTLineJoinType {
  LOTLineJoinTypeMiter,
  LOTLineJoinTypeRound,
  LOTLineJoinTypeBevel
};

class LOTShapeStroke : public LOTShapeItem
{
public:
    LOTShapeStroke(const QVariantMap &jsonDictionary);
    ~LOTShapeStroke();

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly)
    bool fillEnabled;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *color = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *opacity = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *width = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *dashOffset = nullptr;
//@property (nonatomic, readonly)
    LOTLineCapType capType = LOTLineCapTypeButt;
//@property (nonatomic, readonly)
    LOTLineJoinType joinType = LOTLineJoinTypeMiter;

//@property (nonatomic, readonly)
    QList<LOTKeyframeGroup *> lineDashPattern;
};
