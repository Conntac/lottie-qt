//
//  LOTSizeInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTValueInterpolator.h"
#include "LOTValueDelegate.h"

#include <QSizeF>

class LOTSizeInterpolator : public LOTValueInterpolator
{
public:
    LOTSizeInterpolator(const QList<LOTKeyframe *> &keyframes);

    // Functions
    QSizeF sizeValueForFrame(qreal frame);

    // Properties
    LOTSizeValueDelegate *delegate = nullptr;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(LOTValueDelegate *delegate) override;
};
