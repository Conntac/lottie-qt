//
//  LOTColorInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTValueInterpolator.h"
#import "LOTValueDelegate.h"

class LOTColorInterpolator : public LOTValueInterpolator
{
public:
    LOTColorInterpolator(const QList<LOTKeyframe *> &keyframes);

    QColor colorForFrame(qreal frame);

//    @property (nonatomic, weak, nullable)
    LOTColorValueDelegate *delegate = nullptr;

    // LOTValueInterpolator interface
    bool hasDelegateOverride() const override;
    void setValueDelegate(LOTValueDelegate *delegate) override;
};
