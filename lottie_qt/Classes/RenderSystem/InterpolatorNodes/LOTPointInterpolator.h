//
//  LOTPointInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/12/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTValueInterpolator.h"
#include "LOTValueDelegate.h"

#include <QPointF>

class LOTPointInterpolator : public LOTValueInterpolator
{
public:
    LOTPointInterpolator(const QList<LOTKeyframe *> &keyframes);

    // Functions
    QPointF pointValueForFrame(qreal frame);

    // Properties
    LOTPointValueDelegate *delegate = nullptr;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(LOTValueDelegate *delegate) override;
};
