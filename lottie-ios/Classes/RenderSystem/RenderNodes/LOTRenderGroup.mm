//
//  LOTRenderGroup.m
//  Lottie
//
//  Created by brandon_withrow on 6/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTRenderGroup.h"
#import "LOTModels.h"
#import "LOTPathAnimator.h"
#import "LOTFillRenderer.h"
#import "LOTStrokeRenderer.h"
#import "LOTNumberInterpolator.h"
#import "LOTTransformInterpolator.h"
#import "LOTCircleAnimator.h"
#import "LOTRoundedRectAnimator.h"
#import "LOTTrimPathNode.h"
#import "LOTShapeStar.h"
#import "LOTPolygonAnimator.h"
#import "LOTPolystarAnimator.h"
#import "LOTShapeGradientFill.h"
#import "LOTGradientFillRender.h"
#import "LOTRepeaterRenderer.h"
#import "LOTShapeRepeater.h"

#include <QSharedPointer>

LOTRenderGroup::LOTRenderGroup(const QSharedPointer<LOTAnimatorNode> &inputNode, NSArray *contents, NSString *keyname)
: LOTRenderNode(inputNode, keyname)
{
    containerLayer = [CALayer layer];
    containerLayer.actions = @{@"transform": [NSNull null],
                                @"opacity": [NSNull null]};

    buildContents(contents);
}

QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTRenderGroup::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;

    if (_opacityInterpolator && _transformInterolator) {
        map.insert("Opacity", _opacityInterpolator);
        map.insert("Position", _transformInterolator->positionInterpolator);
        map.insert("Scale", _transformInterolator->scaleInterpolator);
        map.insert("Rotation", _transformInterolator->scaleInterpolator);
        map.insert("Anchor Point", _transformInterolator->anchorInterpolator);
        // Deprecated
        map.insert("Transform.Opacity", _opacityInterpolator);
        map.insert("Transform.Position", _transformInterolator->positionInterpolator);
        map.insert("Transform.Scale", _transformInterolator->scaleInterpolator);
        map.insert("Transform.Rotation", _transformInterolator->scaleInterpolator);
        map.insert("Transform.Anchor Point", _transformInterolator->anchorInterpolator);
    }

    return map;
}

LOTBezierPath *LOTRenderGroup::localPath() const
{
    return _localPath;
}

LOTBezierPath *LOTRenderGroup::outputPath() const
{
    return _outputPath;
}

bool LOTRenderGroup::needsUpdateForFrame(qreal frame)
{
    bool opacityNeedsUpdate = _opacityInterpolator ? _opacityInterpolator->hasUpdateForFrame(frame) : false;
    bool transformNeedsUpdate = _transformInterolator ? _transformInterolator->hasUpdateForFrame(frame) : false;
    return (opacityNeedsUpdate ||
            transformNeedsUpdate ||
            _rootNodeHasUpdate);
}

bool LOTRenderGroup::updateWithFrame(qreal frame, std::function<void (LOTAnimatorNode *)> modifier, bool forceUpdate)
{
    indentation_level = indentation_level + 1;
    _rootNodeHasUpdate = _rootNode->updateWithFrame(frame, modifier, forceUpdate);
    indentation_level = indentation_level - 1;
    BOOL update = LOTRenderNode::updateWithFrame(frame, modifier, forceUpdate);
    return update;
}

void LOTRenderGroup::setPathShouldCacheLengths(bool pathShouldCacheLengths)
{
    LOTRenderNode::setPathShouldCacheLengths(pathShouldCacheLengths);
    _rootNode->setPathShouldCacheLengths(pathShouldCacheLengths);
}

void LOTRenderGroup::performLocalUpdate()
{
    if (_opacityInterpolator) {
      containerLayer.opacity = _opacityInterpolator->floatValueForFrame(currentFrame);
    }
    if (_transformInterolator) {
      CATransform3D xform = _transformInterolator->transformForFrame(currentFrame);
      containerLayer.transform = xform;

      CGAffineTransform appliedXform = CATransform3DGetAffineTransform(xform);
      _localPath = [_rootNode->outputPath() copy];
      [_localPath LOT_applyTransform:appliedXform];
    } else {
      _localPath = [_rootNode->outputPath() copy];
    }
}

void LOTRenderGroup::rebuildOutputs()
{
    if (inputNode) {
      _outputPath = [inputNode->outputPath() copy];
      [_outputPath LOT_appendPath:localPath()];
    } else {
      _outputPath = localPath();
    }
}

void LOTRenderGroup::buildContents(NSArray *contents)
{
    QSharedPointer<LOTAnimatorNode> previousNode;
    LOTShapeTransform *transform;
    for (id item in contents) {
      if ([item isKindOfClass:[LOTShapeFill class]]) {
        QSharedPointer<LOTFillRenderer> fillRenderer = fillRenderer.create(previousNode, (LOTShapeFill *)item);
        [containerLayer insertSublayer:fillRenderer->outputLayer atIndex:0];
        previousNode = fillRenderer;
      } else if ([item isKindOfClass:[LOTShapeStroke class]]) {
        QSharedPointer<LOTStrokeRenderer> strokRenderer = strokRenderer.create(previousNode, (LOTShapeStroke *)item);
        [containerLayer insertSublayer:strokRenderer->outputLayer atIndex:0];
        previousNode = strokRenderer;
      } else if ([item isKindOfClass:[LOTShapePath class]]) {
        QSharedPointer<LOTPathAnimator> pathAnimator = pathAnimator.create(previousNode, (LOTShapePath *)item);
        previousNode = pathAnimator;
      } else if ([item isKindOfClass:[LOTShapeRectangle class]]) {
        QSharedPointer<LOTRoundedRectAnimator> rectAnimator = rectAnimator.create(previousNode, (LOTShapeRectangle *)item);
        previousNode = rectAnimator;
      } else if ([item isKindOfClass:[LOTShapeCircle class]]) {
        QSharedPointer<LOTCircleAnimator> circleAnimator = circleAnimator.create(previousNode, (LOTShapeCircle *)item);
        previousNode = circleAnimator;
      } else if ([item isKindOfClass:[LOTShapeGroup class]]) {
        LOTShapeGroup *shapeGroup = (LOTShapeGroup *)item;
        QSharedPointer<LOTRenderGroup> renderGroup = renderGroup.create(previousNode, shapeGroup.items, shapeGroup.keyname);
        [containerLayer insertSublayer:renderGroup->containerLayer atIndex:0];
        previousNode = renderGroup;
      } else if ([item isKindOfClass:[LOTShapeTransform class]]) {
        transform = (LOTShapeTransform *)item;
      } else if ([item isKindOfClass:[LOTShapeTrimPath class]]) {
        QSharedPointer<LOTTrimPathNode> trim = trim.create(previousNode, (LOTShapeTrimPath *)item);
        previousNode = trim;
      } else if ([item isKindOfClass:[LOTShapeStar class]]) {
        LOTShapeStar *star = (LOTShapeStar *)item;
        if (star.type == LOTPolystarShapeStar) {
          QSharedPointer<LOTPolystarAnimator> starAnimator = starAnimator.create(previousNode, star);
          previousNode = starAnimator;
        }
        if (star.type == LOTPolystarShapePolygon) {
          QSharedPointer<LOTPolygonAnimator> polygonAnimator = polygonAnimator.create(previousNode, star);
          previousNode = polygonAnimator;
        }
      } else if ([item isKindOfClass:[LOTShapeGradientFill class]]) {
        QSharedPointer<LOTGradientFillRender> gradientFill = gradientFill.create(previousNode, (LOTShapeGradientFill *)item);
        previousNode = gradientFill;
        [containerLayer insertSublayer:gradientFill->outputLayer atIndex:0];
      } else if ([item isKindOfClass:[LOTShapeRepeater class]]) {
        QSharedPointer<LOTRepeaterRenderer> repeater = repeater.create(previousNode, (LOTShapeRepeater *)item);
        previousNode = repeater;
        [containerLayer insertSublayer:repeater->outputLayer atIndex:0];
      }
    }
    if (transform) {
      _opacityInterpolator = _opacityInterpolator.create(transform.opacity.keyframes);
      _transformInterolator = _transformInterolator.create(transform.position.keyframes,
                                                           transform.rotation.keyframes,
                                                           transform.anchor.keyframes,
                                                           transform.scale.keyframes);
    }
    _rootNode = previousNode;
}


void LOTRenderGroup::searchNodesForKeypath(LOTKeypath *keypath)
{
    inputNode->searchNodesForKeypath(keypath);
    if ([keypath pushKey:keyname]) {
      // Matches self. Dig deeper.
      // Check interpolators

      if ([keypath pushKey:@"Transform"]) {
        // Matches a Transform interpolator!
        if (valueInterpolators()[QString::fromNSString(keypath.currentKey)] != nil) {
          [keypath pushKey:keypath.currentKey];
//          [keypath addSearchResultForCurrentPath:this];
          [keypath popKey];
        }
        [keypath popKey];
      }

      if (keypath.endOfKeypath) {
        // We have a match!
//        [keypath addSearchResultForCurrentPath:this];
      }
      // Check child nodes
      _rootNode->searchNodesForKeypath(keypath);
      [keypath popKey];
    }
}

void LOTRenderGroup::setValueDelegate(id<LOTValueDelegate> delegate, LOTKeypath *keypath)
{
    if ([keypath pushKey:keyname]) {
      // Matches self. Dig deeper.
      // Check interpolators
      if ([keypath pushKey:@"Transform"]) {
        // Matches a Transform interpolator!
        QSharedPointer<LOTValueInterpolator> interpolator = valueInterpolators()[QString::fromNSString(keypath.currentKey)];
        if (interpolator) {
          // We have a match!
          interpolator->setValueDelegate(delegate);
        }
        [keypath popKey];
      }

      // Check child nodes
      _rootNode->setValueDelegate(delegate, keypath);

      [keypath popKey];
    }

    // Check upstream
    inputNode->setValueDelegate(delegate, keypath);
}
