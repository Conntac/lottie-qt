//
//  LOTAnimationView
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#pragma once

#include "qquicklottielayer.h"

class LOTRadialGradientLayer : public QQuickLottieLayer
{
public:
    QPointF startPoint;
    QPointF endPoint;

    QList<QColor> colors;
    QList<qreal> locations;
    bool isRadial;
};



