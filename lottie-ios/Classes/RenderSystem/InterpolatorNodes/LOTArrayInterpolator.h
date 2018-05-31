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
    LOTArrayInterpolator(NSArray <LOTKeyframe *> *keyframes);

    NSArray *numberArrayForFrame(qreal frame);
};

NS_ASSUME_NONNULL_END
