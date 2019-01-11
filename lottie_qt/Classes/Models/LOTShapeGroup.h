//
//  LOTShape.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#pragma once

#include "lotbase.h"
#include <QString>

class LOTShapeGroup : public LOTShapeItem
{
public:
    LOTShapeGroup(const QVariantMap &jsonDictionary);
    ~LOTShapeGroup();

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly, nonnull)
    QList<LOTBase *> items;

    static LOTShapeItem *shapeItemWithJSON(const QVariantMap &itemJSON);
};
