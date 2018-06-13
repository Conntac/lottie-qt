//
//  LOTNumberInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/11/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LOTValueInterpolator.h"
#import "LOTValueDelegate.h"

class LOTNumberInterpolator : public LOTValueInterpolator
{
public:
    LOTNumberInterpolator(const QList<LOTKeyframe *> &keyframes);

    // Functions
    qreal floatValueForFrame(qreal frame);

    // Properties
    id<LOTNumberValueDelegate> delegate = nil;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(id<LOTValueDelegate> delegate) override;
};
