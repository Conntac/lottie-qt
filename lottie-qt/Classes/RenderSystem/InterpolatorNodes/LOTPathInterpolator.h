//
//  LOTPathInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTValueInterpolator.h"
#import "LOTPlatformCompat.h"
#import "LOTBezierPath.h"
#import "LOTValueDelegate.h"

NS_ASSUME_NONNULL_BEGIN

class LOTPathInterpolator : public LOTValueInterpolator
{
public:
    LOTPathInterpolator(const QList<LOTKeyframe *> &keyframes);

    QSharedPointer<LOTBezierPath> pathForFrame(qreal frame, bool cacheLengths);

//@property (nonatomic, weak, nullable)
    id<LOTPathValueDelegate> delegate = nil;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(id<LOTValueDelegate> delegate) override;
};

NS_ASSUME_NONNULL_END
