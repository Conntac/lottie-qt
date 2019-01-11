//
//  LOTArrayInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTValueInterpolator.h"

class LOTArrayInterpolator : public LOTValueInterpolator
{
public:
    LOTArrayInterpolator(const QList<LOTKeyframe *> &keyframes);

    QList<qreal> numberArrayForFrame(qreal frame);
};
