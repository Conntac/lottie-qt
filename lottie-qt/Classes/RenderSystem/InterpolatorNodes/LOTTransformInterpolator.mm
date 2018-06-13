//
//  LOTTransformInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/18/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTTransformInterpolator.h"

// TODO BW Perf update, Cache transform

LOTTransformInterpolator::LOTTransformInterpolator(const QList<LOTKeyframe *> &position, const QList<LOTKeyframe *> &rotation, const QList<LOTKeyframe *> &anchor, const QList<LOTKeyframe *> &scale)
{
    QList<LOTKeyframe *> empty;
    initialize(empty, empty, position, rotation, anchor, scale);
}

LOTTransformInterpolator::LOTTransformInterpolator(const QList<LOTKeyframe *> &positionX, const QList<LOTKeyframe *> &positionY, const QList<LOTKeyframe *> &rotation, const QList<LOTKeyframe *> &anchor, const QList<LOTKeyframe *> &scale)
{
    QList<LOTKeyframe *> empty;
    initialize(positionX, positionY, empty, rotation, anchor, scale);
}

QSharedPointer<LOTTransformInterpolator> LOTTransformInterpolator::transformForLayer(LOTLayer *layer)
{
    QSharedPointer<LOTTransformInterpolator> interpolator;
    if (layer->position) {
      interpolator = interpolator.create(layer->position->keyframes,
                                         layer->rotation->keyframes,
                                         layer->anchor->keyframes,
                                         layer->scale->keyframes);
    } else {
      interpolator = interpolator.create(layer->positionX->keyframes,
                                         layer->positionY->keyframes,
                                         layer->rotation->keyframes,
                                         layer->anchor->keyframes,
                                         layer->scale->keyframes);
    }
    interpolator->parentKeyName = layer->layerName;
    return interpolator;
}

QTransform LOTTransformInterpolator::transformForFrame(qreal frame)
{
    QTransform baseXform;
    if (inputNode) {
      baseXform = inputNode->transformForFrame(frame);
    }
    CGPoint position = CGPointZero;
    if (positionInterpolator) {
      position = positionInterpolator->pointValueForFrame(frame).toCGPoint();
    }
    if (positionXInterpolator &&
        positionYInterpolator) {
      position.x = positionXInterpolator->floatValueForFrame(frame);
      position.y = positionYInterpolator->floatValueForFrame(frame);
    }
    CGPoint anchor = anchorInterpolator->pointValueForFrame(frame).toCGPoint();
    CGSize scale = scaleInterpolator->sizeValueForFrame(frame).toCGSize();
    CGFloat rotation = rotationInterpolator->floatValueForFrame(frame);
    baseXform.translate(position.x, position.y);
    baseXform.rotate(rotation);
    baseXform.scale(scale.width, scale.height);
    baseXform.translate(-1 * anchor.x, -1 * anchor.y);
//    CATransform3D translateXform = CATransform3DTranslate(baseXform, position.x, position.y, 0);
//    CATransform3D rotateXform = CATransform3DRotate(translateXform, rotation, 0, 0, 1);
//    CATransform3D scaleXform = CATransform3DScale(rotateXform, scale.width, scale.height, 1);
//    CATransform3D anchorXform = CATransform3DTranslate(scaleXform, -1 * anchor.x, -1 * anchor.y, 0);
    return baseXform;
}

bool LOTTransformInterpolator::hasUpdateForFrame(qreal frame)
{
    bool inputUpdate = inputNode ? inputNode->hasUpdateForFrame(frame) : false;
    if (inputUpdate) {
      return inputUpdate;
    }
    if (positionInterpolator) {
      return (positionInterpolator->hasUpdateForFrame(frame) ||
              anchorInterpolator->hasUpdateForFrame(frame) ||
              scaleInterpolator->hasUpdateForFrame(frame) ||
              rotationInterpolator->hasUpdateForFrame(frame));
    }
    return (positionXInterpolator->hasUpdateForFrame(frame) ||
            positionYInterpolator->hasUpdateForFrame(frame) ||
            anchorInterpolator->hasUpdateForFrame(frame) ||
            scaleInterpolator->hasUpdateForFrame(frame) ||
            rotationInterpolator->hasUpdateForFrame(frame));
}

void LOTTransformInterpolator::initialize(const QList<LOTKeyframe *> &positionX, const QList<LOTKeyframe *> &positionY, const QList<LOTKeyframe *> &position, const QList<LOTKeyframe *> &rotation, const QList<LOTKeyframe *> &anchor, const QList<LOTKeyframe *> &scale)
{
    if (!position.isEmpty()) {
      positionInterpolator = positionInterpolator.create(position);
    }
    if (!positionY.isEmpty()) {
      positionYInterpolator = positionYInterpolator.create(positionY);
    }
    if (!positionX.isEmpty()) {
      positionXInterpolator = positionXInterpolator.create(positionX);
    }
    anchorInterpolator = anchorInterpolator.create(anchor);
    scaleInterpolator = scaleInterpolator.create(scale);
    rotationInterpolator = rotationInterpolator.create(rotation);
}
