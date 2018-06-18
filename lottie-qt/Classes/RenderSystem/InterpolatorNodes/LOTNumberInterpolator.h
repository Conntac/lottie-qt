//
//  LOTNumberInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/11/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTValueInterpolator.h"
#include "LOTValueDelegate.h"

class LOTNumberInterpolator : public LOTValueInterpolator
{
public:
    LOTNumberInterpolator(const QList<LOTKeyframe *> &keyframes);

    // Functions
    qreal floatValueForFrame(qreal frame);

    // Properties
    LOTNumberValueDelegate *delegate = nullptr;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(LOTValueDelegate *delegate) override;
};
