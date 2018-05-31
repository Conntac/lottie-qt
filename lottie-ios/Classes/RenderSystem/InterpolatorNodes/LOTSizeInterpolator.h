//
//  LOTSizeInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTValueInterpolator.h"
#import "LOTValueDelegate.h"

#include <QSizeF>

NS_ASSUME_NONNULL_BEGIN

class LOTSizeInterpolator : public LOTValueInterpolator
{
public:
    LOTSizeInterpolator(NSArray <LOTKeyframe *> *keyframes);

    // Functions
    QSizeF sizeValueForFrame(qreal frame);

    // Properties
    id<LOTSizeValueDelegate> delegate;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(id<LOTValueDelegate> delegate) override;
};

NS_ASSUME_NONNULL_END
