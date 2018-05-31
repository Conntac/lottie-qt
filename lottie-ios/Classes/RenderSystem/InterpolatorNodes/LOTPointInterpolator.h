//
//  LOTPointInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/12/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTValueInterpolator.h"
#import "LOTValueDelegate.h"

#include <QPointF>

NS_ASSUME_NONNULL_BEGIN

class LOTPointInterpolator : public LOTValueInterpolator
{
public:
    LOTPointInterpolator(NSArray <LOTKeyframe *> *keyframes);

    // Functions
    QPointF pointValueForFrame(qreal frame);

    // Properties
    id<LOTPointValueDelegate> delegate = nil;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(id<LOTValueDelegate> delegate) override;
};

NS_ASSUME_NONNULL_END
