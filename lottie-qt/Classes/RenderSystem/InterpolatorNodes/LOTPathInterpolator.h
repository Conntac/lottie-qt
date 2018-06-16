//
//  LOTPathInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTValueInterpolator.h"
#import "LOTBezierPath.h"
#import "LOTValueDelegate.h"

class LOTPathInterpolator : public LOTValueInterpolator
{
public:
    LOTPathInterpolator(const QList<LOTKeyframe *> &keyframes);

    QSharedPointer<LOTBezierPath> pathForFrame(qreal frame, bool cacheLengths);

//@property (nonatomic, weak, nullable)
    LOTPathValueDelegate *delegate = nullptr;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(LOTValueDelegate *delegate) override;
};
