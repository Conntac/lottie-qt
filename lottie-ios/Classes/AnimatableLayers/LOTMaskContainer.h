//
//  LOTMaskContainer.h
//  Lottie
//
//  Created by brandon_withrow on 7/19/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "LOTMask.h"

#include "qquicklottielayer.h"

class LOTMaskNodeLayer;

class LOTMaskContainer : public QQuickLottieLayer
{
public:
    explicit LOTMaskContainer(NSArray<LOTMask *> * _Nonnull masks);

    void setCurrentFrame(qreal currentFrame);
    qreal currentFrame() const;

private:
    qreal _currentFrame = 0.0;
    QList<QSharedPointer<LOTMaskNodeLayer>> _masks;
};
