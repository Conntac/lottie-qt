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
    LOTTransformInterpolator(const QList<LOTKeyframe *> &position,
                             const QList<LOTKeyframe *> &rotation,
                             const QList<LOTKeyframe *> &anchor,
                             const QList<LOTKeyframe *> &scale);

    LOTTransformInterpolator(const QList<LOTKeyframe *> &positionX,
                             const QList<LOTKeyframe *> &positionY,
                             const QList<LOTKeyframe *> &rotation,
                             const QList<LOTKeyframe *> &anchor,
                             const QList<LOTKeyframe *> &scale);

    static QSharedPointer<LOTTransformInterpolator> transformForLayer(LOTLayer *layer);

    // Properties
    QSharedPointer<LOTTransformInterpolator> inputNode;

    QSharedPointer<LOTPointInterpolator> positionInterpolator;
    QSharedPointer<LOTPointInterpolator> anchorInterpolator;
    QSharedPointer<LOTSizeInterpolator> scaleInterpolator;
    QSharedPointer<LOTNumberInterpolator> rotationInterpolator;
    QSharedPointer<LOTNumberInterpolator> positionXInterpolator;
    QSharedPointer<LOTNumberInterpolator> positionYInterpolator;
    QString parentKeyName;

    // Functions
    QTransform transformForFrame(qreal frame);
    bool hasUpdateForFrame(qreal frame);

private:
    void initialize(const QList<LOTKeyframe *> &positionX,
                    const QList<LOTKeyframe *> &positionY,
                    const QList<LOTKeyframe *> &position,
                    const QList<LOTKeyframe *> &rotation,
                    const QList<LOTKeyframe *> &anchor,
                    const QList<LOTKeyframe *> &scale);
};

NS_ASSUME_NONNULL_END
