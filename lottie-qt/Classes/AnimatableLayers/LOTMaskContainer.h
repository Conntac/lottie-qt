//
//  LOTMaskContainer.h
//  Lottie
//
//  Created by brandon_withrow on 7/19/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTMask.h"
#include "qquicklottielayer.h"

class LOTMaskNodeLayer;

class LOTMaskContainer : public QQuickLottieLayer
{
public:
    explicit LOTMaskContainer(const QList<LOTMask *> &masks);

    void setCurrentFrame(qreal currentFrame);
    qreal currentFrame() const;

private:
    qreal _currentFrame = 0.0;
    QList<QSharedPointer<LOTMaskNodeLayer>> _masks;
};
