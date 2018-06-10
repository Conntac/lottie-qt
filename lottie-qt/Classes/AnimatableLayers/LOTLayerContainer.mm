//
//  LOTLayerContainer.m
//  Lottie
//
//  Created by brandon_withrow on 7/18/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTLayerContainer.h"
#import "LOTTransformInterpolator.h"
#import "LOTNumberInterpolator.h"
#import "CGGeometry+LOTAdditions.h"
#import "LOTRenderGroup.h"
#import "LOTHelpers.h"
#import "LOTMaskContainer.h"
#import "LOTAsset.h"

#include <QSharedPointer>
#include <QMap>

//- (void)_setImageForAsset:(LOTAsset *)asset {
//  if (asset.imageName) {
//    NSArray *components = [asset.imageName componentsSeparatedByString:@"."];
//    NSImage *image = [NSImage imageNamed:components.firstObject];
//    if (image) {
//      NSWindow *window = [NSApp mainWindow];
//      CGFloat desiredScaleFactor = [window backingScaleFactor];
//      CGFloat actualScaleFactor = [image recommendedLayerContentsScale:desiredScaleFactor];
//      id layerContents = [image layerContentsForContentsScale:actualScaleFactor];
//      _wrapperLayer.contents = layerContents;
//    }
//  }
//}

// MARK - Animation

//+ (BOOL)needsDisplayForKey:(NSString *)key {
//  if ([key isEqualToString:@"currentFrame"]) {
//    return YES;
//  }
//  return [super needsDisplayForKey:key];
//}

extern QColor qcolorFromCGColor(CGColorRef cgcolor);

LOTLayerContainer::LOTLayerContainer(LOTLayer *layer, LOTLayerGroup *layerGroup)
{
    wrapperLayer = wrapperLayer.create();
    addSublayer(wrapperLayer);
    DEBUG_Center = DEBUG_Center.create();

    DEBUG_Center->bounds = QRectF(0, 0, 20, 20);
    DEBUG_Center->borderColor = QColor("blue");
    DEBUG_Center->borderWidth = 2;
    DEBUG_Center->masksToBounds = YES;

    if (ENABLE_DEBUG_SHAPES) {
      wrapperLayer->addSublayer(DEBUG_Center);
    }
    actions = {{"hidden", QVariant()}, {"opacity", QVariant()}, {"transform", QVariant()}};
    wrapperLayer->actions = actions;
    timeStretchFactor = 1.0;
    commonInitializeWith(layer, layerGroup);
}

//LOTLayerContainer::LOTLayerContainer(const QSharedPointer<QQuickLottieLayer> &layer)
//: QQuickLottieLayer(layer)
//{
//    QSharedPointer<LOTLayerContainer> other = layer.dynamicCast<LOTLayerContainer>();
//    if (other) {
//        currentFrame = other->currentFrame;
//    }
//}

void LOTLayerContainer::setViewportBounds(const QRectF &viewportBounds)
{
    _viewportBounds = viewportBounds;
    if (_maskLayer) {
      QPointF center = LOT_RectGetCenterPoint(viewportBounds);
      QRectF viewportBoundsCopy = viewportBounds;
      viewportBoundsCopy.setX(-center.x());
      viewportBoundsCopy.setY(-center.y());
      _maskLayer->bounds = viewportBoundsCopy;
    }
}

void LOTLayerContainer::displayWithFrame(qreal frame)
{
    displayWithFrame(frame, false);
}

void LOTLayerContainer::displayWithFrame(qreal frame, bool forceUpdate)
{
    qreal newFrame = frame / timeStretchFactor;
    if (ENABLE_DEBUG_LOGGING) NSLog(@"View %ld Displaying Frame %f, with local time %f", this, frame, newFrame);
    BOOL hidden = NO;
    if (_inFrame && _outFrame) {
      hidden = (frame < _inFrame.floatValue ||
                frame > _outFrame.floatValue);
    }
    setHidden(hidden);
    if (hidden) {
      return;
    }
    if (_opacityInterpolator && _opacityInterpolator->hasUpdateForFrame(newFrame)) {
      qreal opacity = _opacityInterpolator->floatValueForFrame(newFrame);
      setOpacity(opacity);
    }
    if (_transformInterpolator && _transformInterpolator->hasUpdateForFrame(newFrame)) {
      QTransform transform = _transformInterpolator->transformForFrame(newFrame);
      wrapperLayer->setTransform(transform);
    }
    if (_contentsGroup) {
      _contentsGroup->updateWithFrame(newFrame, nullptr, forceUpdate);
    }

    if (_maskLayer) {
        _maskLayer->setCurrentFrame(newFrame);
    }
}

void LOTLayerContainer::searchNodesForKeypath(LOTKeypath *keypath)
{
    if (_contentsGroup == nil && keypath->pushKey(layerName)) {
      // Matches self.
      if (keypath->pushKey("Transform")) {
        // Is a transform node, check interpolators
        QSharedPointer<LOTValueInterpolator> interpolator = valueInterpolators[keypath->currentKey()];
        if (interpolator) {
          // We have a match!
          keypath->pushKey(keypath->currentKey());
          keypath->addSearchResultForCurrentPath(wrapperLayer);
          keypath->popKey();
        }
        if (keypath->endOfKeypath()) {
          keypath->addSearchResultForCurrentPath(wrapperLayer);
        }
        keypath->popKey();
      }
      if (keypath->endOfKeypath()) {
        keypath->addSearchResultForCurrentPath(wrapperLayer);
      }
      keypath->popKey();
    }
    _contentsGroup->searchNodesForKeypath(keypath);
}

void LOTLayerContainer::setValueDelegate(id<LOTValueDelegate> delegate, LOTKeypath *keypath)
{
    if (keypath->pushKey(layerName)) {
      // Matches self.
      if (keypath->pushKey("Transform")) {
        // Is a transform node, check interpolators
        QSharedPointer<LOTValueInterpolator> interpolator = valueInterpolators[keypath->currentKey()];
        if (interpolator) {
          // We have a match!
          interpolator->setValueDelegate(delegate);
        }
        keypath->popKey();
      }
      keypath->popKey();
    }
    _contentsGroup->setValueDelegate(delegate, keypath);
}

void LOTLayerContainer::actionForKey(const QString &event)
{
    if (event == "currentFrame") {
//      CABasicAnimation *theAnimation = [CABasicAnimation
//                                        animationWithKeyPath:event];
//      theAnimation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
//      theAnimation.fromValue = [[self presentationLayer] valueForKey:event];
//      return theAnimation;
    }
    return QQuickLottieLayer::actionForKey(event);
}

void LOTLayerContainer::display()
{
//    @synchronized(self) {
      LOTLayerContainer *presentation = this;
      if (animationKeys.size() &&
        presentationLayer) {
          presentation = dynamic_cast<LOTLayerContainer *>(presentationLayer.data());
      }
      displayWithFrame(presentation->currentFrame);
//    }
}

void LOTLayerContainer::commonInitializeWith(LOTLayer *layer, LOTLayerGroup *layerGroup)
{
    if (layer == nil) {
      return;
    }
    layerName = layer.layerName;
    if (layer.layerType == LOTLayerTypeImage ||
        layer.layerType == LOTLayerTypeSolid ||
        layer.layerType == LOTLayerTypePrecomp) {
      wrapperLayer->bounds = QRectF(0, 0, layer.layerWidth.floatValue, layer.layerHeight.floatValue);
      wrapperLayer->anchorPoint = QPointF(0, 0);
      wrapperLayer->masksToBounds = true;
      DEBUG_Center->position = LOT_RectGetCenterPoint(bounds);
    }

    if (layer.layerType == LOTLayerTypeImage) {
        Q_ASSERT(false);
//      [self _setImageForAsset:layer.imageAsset];
    }

    _inFrame = [layer.inFrame copy];
    _outFrame = [layer.outFrame copy];

    timeStretchFactor = layer.timeStretch.floatValue;
    _transformInterpolator = LOTTransformInterpolator::transformForLayer(layer);

    if (layer.parentID) {
      NSNumber *parentID = layer.parentID;
      QSharedPointer<LOTTransformInterpolator> childInterpolator = _transformInterpolator;
      while (parentID != nil) {
        LOTLayer *parentModel = [layerGroup layerModelForID:parentID];
        QSharedPointer<LOTTransformInterpolator> interpolator = LOTTransformInterpolator::transformForLayer(parentModel);
        childInterpolator->inputNode = interpolator;
        childInterpolator = interpolator;
        parentID = parentModel.parentID;
      }
    }
    _opacityInterpolator = _opacityInterpolator.create(layer.opacity.keyframes);
    if (layer.layerType == LOTLayerTypeShape &&
        layer.shapes.count) {
      buildContents(layer.shapes);
    }
    if (layer.layerType == LOTLayerTypeSolid) {
      wrapperLayer->backgroundColor = layer.solidColor;
    }
    if (layer.masks.count) {
      _maskLayer = _maskLayer.create(layer.masks);
      wrapperLayer->mask = _maskLayer;
    }

    QMap<QString, QSharedPointer<LOTValueInterpolator>> interpolators;
    interpolators["Opacity"] = _opacityInterpolator;
    interpolators["Anchor Point"] = _transformInterpolator->anchorInterpolator;
    interpolators["Scale"] = _transformInterpolator->scaleInterpolator;
    interpolators["Rotation"] = _transformInterpolator->rotationInterpolator;
    if (_transformInterpolator->positionXInterpolator &&
        _transformInterpolator->positionYInterpolator) {
      interpolators["X Position"] = _transformInterpolator->positionXInterpolator;
      interpolators["Y Position"] = _transformInterpolator->positionYInterpolator;
    } else if (_transformInterpolator->positionInterpolator) {
      interpolators["Position"] = _transformInterpolator->positionInterpolator;
    }

    // Deprecated
    interpolators["Transform.Opacity"] = _opacityInterpolator;
    interpolators["Transform.Anchor Point"] = _transformInterpolator->anchorInterpolator;
    interpolators["Transform.Scale"] = _transformInterpolator->scaleInterpolator;
    interpolators["Transform.Rotation"] = _transformInterpolator->rotationInterpolator;
    if (_transformInterpolator->positionXInterpolator &&
        _transformInterpolator->positionYInterpolator) {
      interpolators["Transform.X Position"] = _transformInterpolator->positionXInterpolator;
      interpolators["Transform.Y Position"] = _transformInterpolator->positionYInterpolator;
    } else if (_transformInterpolator->positionInterpolator) {
      interpolators["Transform.Position"] = _transformInterpolator->positionInterpolator;
    }
    valueInterpolators = interpolators;
}

void LOTLayerContainer::buildContents(NSArray *contents)
{
    _contentsGroup = _contentsGroup.create(nil, contents, layerName);
    wrapperLayer->addSublayer(_contentsGroup->containerLayer);
}
