//
//  LOTRenderGroup.m
//  Lottie
//
//  Created by brandon_withrow on 6/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTRenderGroup.h"
#include "LOTModels.h"
#include "LOTPathAnimator.h"
#include "LOTFillRenderer.h"
#include "LOTStrokeRenderer.h"
#include "LOTNumberInterpolator.h"
#include "LOTTransformInterpolator.h"
#include "LOTCircleAnimator.h"
#include "LOTRoundedRectAnimator.h"
#include "LOTTrimPathNode.h"
#include "LOTShapeStar.h"
#include "LOTPolygonAnimator.h"
#include "LOTPolystarAnimator.h"
#include "LOTShapeGradientFill.h"
#include "LOTGradientFillRender.h"
#include "LOTRepeaterRenderer.h"
#include "LOTShapeRepeater.h"

#include <QSharedPointer>

LOTRenderGroup::LOTRenderGroup(const QSharedPointer<LOTAnimatorNode> &inputNode, const QList<LOTBase *> &contents, const QString &keyname)
: LOTRenderNode(inputNode, keyname)
{
//    containerLayer = [CALayer layer];
//    containerLayer.actions = @{@"transform": [NSNull null],
//                                @"opacity": [NSNull null]};

    containerLayer = containerLayer.create();

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

QSharedPointer<LOTBezierPath> LOTRenderGroup::localPath() const
{
    return _localPath;
}

QSharedPointer<LOTBezierPath> LOTRenderGroup::outputPath() const
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
    _rootNodeHasUpdate = _rootNode && _rootNode->updateWithFrame(frame, modifier, forceUpdate);
    indentation_level = indentation_level - 1;
    bool update = LOTRenderNode::updateWithFrame(frame, modifier, forceUpdate);
    return update;
}

void LOTRenderGroup::setPathShouldCacheLengths(bool pathShouldCacheLengths)
{
    LOTRenderNode::setPathShouldCacheLengths(pathShouldCacheLengths);
    if (_rootNode) {
        _rootNode->setPathShouldCacheLengths(pathShouldCacheLengths);
    }
}

void LOTRenderGroup::performLocalUpdate()
{
    if (_opacityInterpolator) {
      containerLayer->setOpacity(_opacityInterpolator->floatValueForFrame(currentFrame));
    }
    if (_transformInterolator) {
      QTransform xform = _transformInterolator->transformForFrame(currentFrame);
      containerLayer->setTransform(xform);

      Q_ASSERT(xform.isAffine());

      QTransform appliedXform = xform;
//      CGAffineTransform appliedXform = ; // = CATransform3DGetAffineTransform(xform);
//      QTransform appliedXform = xform;
//      Q_ASSERT(false);
      if (_rootNode && _rootNode->outputPath()) {
          _localPath = _rootNode->outputPath()->copy();
          _localPath->LOT_applyTransform(appliedXform);
      }
    } else {
        if (_rootNode && _rootNode->outputPath()) {
            _localPath = _rootNode->outputPath()->copy();
        }
    }
}

void LOTRenderGroup::rebuildOutputs()
{
    if (inputNode) {
        if (inputNode->outputPath()) {
            _outputPath = inputNode->outputPath()->copy();
            _outputPath->LOT_appendPath(localPath());
        }
    } else {
      _outputPath = localPath();
    }
}

void LOTRenderGroup::buildContents(const QList<LOTBase *> &contents)
{
    QSharedPointer<LOTAnimatorNode> previousNode;
    LOTShapeTransform *transform = nullptr;
    for (LOTBase *item : contents) {
      if (dynamic_cast<LOTShapeFill *>(item)) {
        QSharedPointer<LOTFillRenderer> fillRenderer = fillRenderer.create(previousNode, dynamic_cast<LOTShapeFill *>(item));
        containerLayer->insertSublayer(fillRenderer->outputLayer, 0);
        previousNode = fillRenderer;
      } else if (dynamic_cast<LOTShapeStroke *>(item)) {
        QSharedPointer<LOTStrokeRenderer> strokRenderer = strokRenderer.create(previousNode, dynamic_cast<LOTShapeStroke *>(item));
        containerLayer->insertSublayer(strokRenderer->outputLayer, 0);
        previousNode = strokRenderer;
      } else if (dynamic_cast<LOTShapePath *>(item)) {
        QSharedPointer<LOTPathAnimator> pathAnimator = pathAnimator.create(previousNode, dynamic_cast<LOTShapePath *>(item));
        previousNode = pathAnimator;
      } else if (dynamic_cast<LOTShapeRectangle *>(item)) {
        QSharedPointer<LOTRoundedRectAnimator> rectAnimator = rectAnimator.create(previousNode, dynamic_cast<LOTShapeRectangle *>(item));
        previousNode = rectAnimator;
      } else if (dynamic_cast<LOTShapeCircle *>(item)) {
        QSharedPointer<LOTCircleAnimator> circleAnimator = circleAnimator.create(previousNode, dynamic_cast<LOTShapeCircle *>(item));
        previousNode = circleAnimator;
      } else if (dynamic_cast<LOTShapeGroup *>(item)) {
        LOTShapeGroup *shapeGroup = dynamic_cast<LOTShapeGroup *>(item);
        QSharedPointer<LOTRenderGroup> renderGroup = renderGroup.create(previousNode, shapeGroup->items, shapeGroup->keyname);
        containerLayer->insertSublayer(renderGroup->containerLayer, 0);
        previousNode = renderGroup;
      } else if (dynamic_cast<LOTShapeTransform *>(item)) {
        transform = dynamic_cast<LOTShapeTransform *>(item);
      } else if (dynamic_cast<LOTShapeTrimPath *>(item)) {
        QSharedPointer<LOTTrimPathNode> trim = trim.create(previousNode, dynamic_cast<LOTShapeTrimPath *>(item));
        previousNode = trim;
      } else if (dynamic_cast<LOTShapeStar *>(item)) {
        LOTShapeStar *star = dynamic_cast<LOTShapeStar *>(item);
        if (star->type == LOTPolystarShapeStar) {
          QSharedPointer<LOTPolystarAnimator> starAnimator = starAnimator.create(previousNode, star);
          previousNode = starAnimator;
        }
        if (star->type == LOTPolystarShapePolygon) {
          QSharedPointer<LOTPolygonAnimator> polygonAnimator = polygonAnimator.create(previousNode, star);
          previousNode = polygonAnimator;
        }
      } else if (dynamic_cast<LOTShapeGradientFill *>(item)) {
        QSharedPointer<LOTGradientFillRender> gradientFill = gradientFill.create(previousNode, dynamic_cast<LOTShapeGradientFill *>(item));
        previousNode = gradientFill;
        containerLayer->insertSublayer(gradientFill->outputLayer, 0);
      } else if (dynamic_cast<LOTShapeRepeater *>(item)) {
        QSharedPointer<LOTRepeaterRenderer> repeater = repeater.create(previousNode, dynamic_cast<LOTShapeRepeater *>(item));
        previousNode = repeater;
        containerLayer->insertSublayer(repeater->outputLayer, 0);
      }
    }
    if (transform) {
      _opacityInterpolator = _opacityInterpolator.create(transform->opacity->keyframes);
      _transformInterolator = _transformInterolator.create(transform->position->keyframes,
                                                           transform->rotation->keyframes,
                                                           transform->anchor->keyframes,
                                                           transform->scale->keyframes);
    }
    _rootNode = previousNode;
}


void LOTRenderGroup::searchNodesForKeypath(LOTKeypath *keypath)
{
    inputNode->searchNodesForKeypath(keypath);
    if (keypath->pushKey(keyname)) {
      // Matches self. Dig deeper.
      // Check interpolators

      if (keypath->pushKey("Transform")) {
        // Matches a Transform interpolator!
        if (valueInterpolators()[keypath->currentKey()]) {
          keypath->pushKey(keypath->currentKey());
          keypath->addSearchResultForCurrentPath(sharedFromThis());
          keypath->popKey();
        }
        keypath->popKey();
      }

      if (keypath->endOfKeypath()) {
        // We have a match!
        keypath->addSearchResultForCurrentPath(sharedFromThis());
      }
      // Check child nodes
      if (_rootNode) {
          _rootNode->searchNodesForKeypath(keypath);
      }
      keypath->popKey();
    }
}

void LOTRenderGroup::setValueDelegate(LOTValueDelegate *delegate, LOTKeypath *keypath)
{
    if (keypath->pushKey(keyname)) {
      // Matches self. Dig deeper.
      // Check interpolators
      if (keypath->pushKey("Transform")) {
        // Matches a Transform interpolator!
        QSharedPointer<LOTValueInterpolator> interpolator = valueInterpolators()[keypath->currentKey()];
        if (interpolator) {
          // We have a match!
          interpolator->setValueDelegate(delegate);
        }
        keypath->popKey();
      }

      // Check child nodes
      if (_rootNode) {
          _rootNode->setValueDelegate(delegate, keypath);
      }

      keypath->popKey();
    }

    // Check upstream
    if (inputNode) {
        inputNode->setValueDelegate(delegate, keypath);
    }
}
