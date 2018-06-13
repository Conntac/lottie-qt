//
//  LOTArrayInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTValueInterpolator.h"

NS_ASSUME_NONNULL_BEGIN

class LOTArrayInterpolator : public LOTValueInterpolator
{
public:
    LOTArrayInterpolator(const QList<LOTKeyframe *> &keyframes);

    QList<qreal> numberArrayForFrame(qreal frame);
};

NS_ASSUME_NONNULL_END
