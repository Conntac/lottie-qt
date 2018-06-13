//
//  LOTColorInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTValueInterpolator.h"
#import "LOTPlatformCompat.h"
#import "LOTValueDelegate.h"

NS_ASSUME_NONNULL_BEGIN

class LOTColorInterpolator : public LOTValueInterpolator
{
public:
    LOTColorInterpolator(const QList<LOTKeyframe *> &keyframes);

    QColor colorForFrame(qreal frame);

//    @property (nonatomic, weak, nullable)
    id<LOTColorValueDelegate> delegate = nil;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(id<LOTValueDelegate> delegate) override;
};

NS_ASSUME_NONNULL_END
