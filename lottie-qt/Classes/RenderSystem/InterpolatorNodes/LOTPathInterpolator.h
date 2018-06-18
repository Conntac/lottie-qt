//
//  LOTPathInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTValueInterpolator.h"
#include "LOTBezierPath.h"
#include "LOTValueDelegate.h"

class LOTPathInterpolator : public LOTValueInterpolator
{
public:
    LOTPathInterpolator(const QList<LOTKeyframe *> &keyframes);

    QSharedPointer<LOTBezierPath> pathForFrame(qreal frame, bool cacheLengths);

//@property (nonatomic, weak, nullable)
    LOTPathValueDelegate *delegate = nullptr;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(LOTValueDelegate *delegate) override;
};
