//
//  LOTTransformInterpolator.h
//  Lottie
//
//  Created by brandon_withrow on 7/18/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LOTNumberInterpolator.h"
#import "LOTPointInterpolator.h"
#import "LOTSizeInterpolator.h"
#import "LOTKeyframe.h"
#import "LOTLayer.h"

#include <QTransform>

NS_ASSUME_NONNULL_BEGIN

class LOTTransformInterpolator
{
public:
    LOTTransformInterpolator(NSArray <LOTKeyframe *> *position,
                             NSArray <LOTKeyframe *> *rotation,
                             NSArray <LOTKeyframe *> *anchor,
                             NSArray <LOTKeyframe *> *scale);

    LOTTransformInterpolator(NSArray <LOTKeyframe *> *positionX,
                             NSArray <LOTKeyframe *> *positionY,
                             NSArray <LOTKeyframe *> *rotation,
                             NSArray <LOTKeyframe *> *anchor,
                             NSArray <LOTKeyframe *> *scale);

    static QSharedPointer<LOTTransformInterpolator> transformForLayer(LOTLayer *layer);

    // Properties
    QSharedPointer<LOTTransformInterpolator> inputNode;

    QSharedPointer<LOTPointInterpolator> positionInterpolator;
    QSharedPointer<LOTPointInterpolator> anchorInterpolator;
    QSharedPointer<LOTSizeInterpolator> scaleInterpolator;
    QSharedPointer<LOTNumberInterpolator> rotationInterpolator;
    QSharedPointer<LOTNumberInterpolator> positionXInterpolator;
    QSharedPointer<LOTNumberInterpolator> positionYInterpolator;
    NSString *parentKeyName;

    // Functions
    CATransform3D transformForFrame(qreal frame);
    bool hasUpdateForFrame(qreal frame);

private:
    void initialize(NSArray <LOTKeyframe *> *positionX,
                    NSArray <LOTKeyframe *> * positionY,
                    NSArray <LOTKeyframe *> * position,
                    NSArray <LOTKeyframe *> * rotation,
                    NSArray <LOTKeyframe *> * anchor,
                    NSArray <LOTKeyframe *> * scale);
};

NS_ASSUME_NONNULL_END
