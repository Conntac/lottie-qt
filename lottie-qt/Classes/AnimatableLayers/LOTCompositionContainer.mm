//
//  LOTCompositionContainer.m
//  Lottie
//
//  Created by brandon_withrow on 7/18/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTCompositionContainer.h"
#import "LOTAsset.h"
#import "CGGeometry+LOTAdditions.h"
#import "LOTHelpers.h"
#import "LOTValueInterpolator.h"
#import "LOTAnimatorNode.h"
#import "LOTRenderNode.h"
#import "LOTRenderGroup.h"
#import "LOTNumberInterpolator.h"

#include <QSharedPointer>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logCompositionContainer, "lottie.composition_container")

LOTCompositionContainer::LOTCompositionContainer(LOTLayer *layer, LOTLayerGroup *layerGroup, LOTLayerGroup *childLayerGroup, LOTAssetGroup *assetGroup)
: LOTLayerContainer(layer, layerGroup)
{
    DEBUG_Center = DEBUG_Center.create();

    DEBUG_Center->bounds = QRectF(0, 0, 20, 20);
    DEBUG_Center->borderColor = QColor("orange");
    DEBUG_Center->borderWidth = 2;
    DEBUG_Center->masksToBounds = YES;
    if (ENABLE_DEBUG_SHAPES) {
      wrapperLayer->addSublayer(DEBUG_Center);
    }
    if (layer && layer->startFrame) {
      _frameOffset = layer->startFrame;
    } else {
      _frameOffset = 0.0;
    }

    if (layer && layer->timeRemapping) {
      _timeInterpolator = _timeInterpolator.create(layer->timeRemapping->keyframes);
    }

    initializeWithChildGroup(childLayerGroup, assetGroup);
}

QStringList LOTCompositionContainer::keysForKeyPath(LOTKeypath *keypath)
{
//    if (_keypathCache == nil) {
//      _keypathCache = [NSMutableDictionary dictionary];
//    }
    searchNodesForKeypath(keypath);
    QMapIterator<QString, QSharedPointer<LOTBase>> iter(keypath->searchResults());
    while (iter.hasNext()) {
        iter.next();

        _keypathCache.insert(iter.key(), iter.value());
    }
    return keypath->searchResults().keys();
}

/*
CGPoint LOTCompositionContainer::convertPointToKeypathLayer(CGPoint point, LOTKeypath *keypath, CALayer *parent)
{
    CALayer *layer = _layerForKeypath(keypath);
    if (!layer) {
      return CGPointZero;
    }
    return [parent convertPoint:point toLayer:layer];
}

CGRect LOTCompositionContainer::convertRectToKeypathLayer(CGRect rect, LOTKeypath *keypath, CALayer *parent)
{
    CALayer *layer = _layerForKeypath(keypath);
    if (!layer) {
      return CGRectZero;
    }
    return [parent convertRect:rect toLayer:layer];
}

CGPoint LOTCompositionContainer::convertPointFromKeypathLayer(CGPoint point, LOTKeypath *keypath, CALayer *parent)
{
    CALayer *layer = _layerForKeypath(keypath);
    if (!layer) {
      return CGPointZero;
    }
    return [parent convertPoint:point fromLayer:layer];
}

CGRect LOTCompositionContainer::convertRectFromKeypathLayer(CGRect rect, LOTKeypath *keypath, CALayer *parent)
{
    CALayer *layer = _layerForKeypath(keypath);
    if (!layer) {
      return CGRectZero;
    }
    return [parent convertRect:rect fromLayer:layer];
}

void LOTCompositionContainer::addSublayer(CALayer *subLayer, LOTKeypath *keypath)
{
    CALayer *layer = _layerForKeypath(keypath);
    if (layer) {
      [layer addSublayer:subLayer];
    }
}

void LOTCompositionContainer::maskSublayer(CALayer *subLayer, LOTKeypath *keypath)
{
    CALayer *layer = _layerForKeypath(keypath);
    if (layer) {
      [layer.superlayer addSublayer:subLayer];
      [layer removeFromSuperlayer];
      subLayer.mask = layer;
    }
}
*/

void LOTCompositionContainer::setViewportBounds(const QRectF &viewportBounds)
{
    LOTLayerContainer::setViewportBounds(viewportBounds);
    for (auto layer : childLayers) {
      layer->setViewportBounds(viewportBounds);
    }
}

void LOTCompositionContainer::displayWithFrame(qreal frame, bool forceUpdate)
{
    if (ENABLE_DEBUG_LOGGING) NSLog(@"-------------------- Composition Displaying Frame %lf --------------------", frame);
    LOTLayerContainer::displayWithFrame(frame, forceUpdate);
    qreal newFrame = (frame  - _frameOffset) / timeStretchFactor;
    if (_timeInterpolator) {
      newFrame = _timeInterpolator->floatValueForFrame(newFrame);
    }
    for (auto child : childLayers) {
      child->displayWithFrame(newFrame, forceUpdate);
    }
    if (ENABLE_DEBUG_LOGGING) NSLog(@"-------------------- ------------------------------- --------------------");
    if (ENABLE_DEBUG_LOGGING) NSLog(@"-------------------- ------------------------------- --------------------");
}

void LOTCompositionContainer::initializeWithChildGroup(LOTLayerGroup *childGroup, LOTAssetGroup *assetGroup)
{
    QMap<QString, QSharedPointer<LOTLayerContainer>> childMap;
    QList<QSharedPointer<LOTLayerContainer>> children;

    QListIterator<LOTLayer *> iter(childGroup->layers);
    iter.toBack();

    QSharedPointer<QQuickLottieLayer> maskedLayer;
    while (iter.hasPrevious()) {
      LOTLayer *layer = iter.previous();

      LOTAsset *asset = nullptr;
      if (!layer->referenceID.isNull()) {
        // Get relevant Asset
        asset = assetGroup->assetModelForID(layer->referenceID);
      }

      QSharedPointer<LOTLayerContainer> child;
      if (asset && asset->layerGroup) {
        // Layer is a precomp
        QSharedPointer<LOTCompositionContainer> compLayer = compLayer.create(layer, childGroup, asset->layerGroup, assetGroup);
        child = compLayer;
      } else {
        child = child.create(layer, childGroup);
      }
      if (maskedLayer) {
        maskedLayer->mask = child;
        maskedLayer.clear();
      } else {
        if (layer->matteType == LOTMatteTypeAdd) {
          maskedLayer = child;
        }
        wrapperLayer->addSublayer(child);
      }
      children.append(child);
      if (!child->layerName.isNull()) {
        childMap.insert(child->layerName, child);
      }
    }
    this->childMap = childMap;
    this->childLayers = children;
}

/*
CALayer *LOTCompositionContainer::_layerForKeypath(LOTKeypath *keypath)
{
    auto node = _keypathCache[keypath->absoluteKeypath()];
    if (node == nil) {
      keysForKeyPath(keypath);
      node = _keypathCache[keypath->absoluteKeypath()];
    }
    if (node == nil) {
      qCDebug(logCompositionContainer) << "LOTComposition could not find layer for keypath:" << keypath->absoluteKeypath();
      return nil;
    }
  //  if ([node isKindOfClass:[CALayer class]]) {
  //    return (CALayer *)node;
  //  }
  //  if (![node isKindOfClass:[LOTRenderNode class]]) {
  //    NSLog(@"LOTComposition: Keypath return non-layer node:%@ ", keypath.absoluteKeypath);
  //    return nil;
  //  }
  //  if ([node isKindOfClass:[LOTRenderGroup class]]) {
  //    return [(LOTRenderGroup *)node containerLayer];
  //  }
  //  LOTRenderNode *renderNode = (LOTRenderNode *)node;
  //  return renderNode.outputLayer;
    return nil;
}
*/

void LOTCompositionContainer::searchNodesForKeypath(LOTKeypath *keypath)
{
    if (layerName != nil) {
      LOTLayerContainer::searchNodesForKeypath(keypath);
    }
    if (layerName == nil ||
        keypath->pushKey(layerName)) {
      for (auto child : childLayers) {
        child->searchNodesForKeypath(keypath);
      }
      if (layerName != nil) {
        keypath->popKey();
      }
    }
}

void LOTCompositionContainer::setValueDelegate(LOTValueDelegate *delegate, LOTKeypath *keypath)
{
    if (layerName != nil) {
      LOTLayerContainer::setValueDelegate(delegate, keypath);
    }
    if (layerName == nil ||
        keypath->pushKey(layerName)) {
      for (auto child : childLayers) {
        child->setValueDelegate(delegate, keypath);
      }
      if (layerName != nil) {
        keypath->popKey();
      }
    }
}
