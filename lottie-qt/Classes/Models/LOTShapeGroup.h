//
//  LOTShape.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#include "lotbase.h"

#include <QString>

class LOTShapeGroup : public LOTShapeItem
{
public:
    LOTShapeGroup(const QVariantMap &jsonDictionary);

//@property (nonatomic, readonly)
    QString keyname;
//@property (nonatomic, readonly, nonnull)
    QList<LOTBase *> items;

    static LOTShapeItem *shapeItemWithJSON(const QVariantMap &itemJSON);
};
