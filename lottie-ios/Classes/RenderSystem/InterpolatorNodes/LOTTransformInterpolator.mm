//
//  LOTTransformInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/18/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTTransformInterpolator.h"

// TODO BW Perf update, Cache transform

LOTTransformInterpolator::LOTTransformInterpolator(NSArray<LOTKeyframe *> *position, NSArray<LOTKeyframe *> *rotation, NSArray<LOTKeyframe *> *anchor, NSArray<LOTKeyframe *> *scale)
{
    initialize(nil, nil, position, rotation, anchor, scale);
}

LOTTransformInterpolator::LOTTransformInterpolator(NSArray<LOTKeyframe *> *positionX, NSArray<LOTKeyframe *> *positionY, NSArray<LOTKeyframe *> *rotation, NSArray<LOTKeyframe *> *anchor, NSArray<LOTKeyframe *> *scale)
{
    initialize(positionX, positionY, nil, rotation, anchor, scale);
}

QSharedPointer<LOTTransformInterpolator> LOTTransformInterpolator::transformForLayer(LOTLayer *layer)
{
    QSharedPointer<LOTTransformInterpolator> interpolator;
    if (layer.position) {
      interpolator = interpolator.create(layer.position.keyframes,
                                         layer.rotation.keyframes,
                                         layer.anchor.keyframes,
                                         layer.scale.keyframes);
    } else {
      interpolator = interpolator.create(layer.positionX.keyframes,
                                         layer.positionY.keyframes,
                                         layer.rotation.keyframes,
                                         layer.anchor.keyframes,
                                         layer.scale.keyframes);
    }
    interpolator->parentKeyName = [layer.layerName copy];
    return interpolator;
}

CATransform3D LOTTransformInterpolator::transformForFrame(qreal frame)
{
    CATransform3D baseXform = CATransform3DIdentity;
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
    CATransform3D translateXform = CATransform3DTranslate(baseXform, position.x, position.y, 0);
    CATransform3D rotateXform = CATransform3DRotate(translateXform, rotation, 0, 0, 1);
    CATransform3D scaleXform = CATransform3DScale(rotateXform, scale.width, scale.height, 1);
    CATransform3D anchorXform = CATransform3DTranslate(scaleXform, -1 * anchor.x, -1 * anchor.y, 0);
    return anchorXform;
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

void LOTTransformInterpolator::initialize(NSArray<LOTKeyframe *> *positionX, NSArray<LOTKeyframe *> *positionY, NSArray<LOTKeyframe *> *position, NSArray<LOTKeyframe *> *rotation, NSArray<LOTKeyframe *> *anchor, NSArray<LOTKeyframe *> *scale)
{
    if (position) {
      positionInterpolator = positionInterpolator.create(position);
    }
    if (positionY) {
      positionYInterpolator = positionYInterpolator.create(positionY);
    }
    if (positionX) {
      positionXInterpolator = positionXInterpolator.create(positionX);
    }
    anchorInterpolator = anchorInterpolator.create(anchor);
    scaleInterpolator = scaleInterpolator.create(scale);
    rotationInterpolator = rotationInterpolator.create(rotation);
}
