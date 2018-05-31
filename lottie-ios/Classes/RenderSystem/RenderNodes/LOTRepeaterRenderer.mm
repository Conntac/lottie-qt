//
//  LOTRepeaterRenderer.m
//  Lottie
//
//  Created by brandon_withrow on 7/28/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTRepeaterRenderer.h"
#import "LOTTransformInterpolator.h"
#import "LOTNumberInterpolator.h"
#import "LOTHelpers.h"

#include <QSharedPointer>

@implementation LOTRepeaterRenderer {
  QSharedPointer<LOTTransformInterpolator> _transformInterpolator;
  QSharedPointer<LOTNumberInterpolator> _copiesInterpolator;
  QSharedPointer<LOTNumberInterpolator> _offsetInterpolator;
  QSharedPointer<LOTNumberInterpolator> _startOpacityInterpolator;
  QSharedPointer<LOTNumberInterpolator> _endOpacityInterpolator;
  
  CALayer *_instanceLayer;
  CAReplicatorLayer *_replicatorLayer;
  CALayer *centerPoint_DEBUG;
}

- (instancetype)initWithInputNode:(LOTAnimatorNode *)inputNode
                              shapeRepeater:(LOTShapeRepeater *)repeater {
  self = [super initWithInputNode:inputNode keyName:repeater.keyname];
  if (self) {
    _transformInterpolator = _transformInterpolator.create(repeater.position.keyframes,
                                                           repeater.rotation.keyframes,
                                                           repeater.anchorPoint.keyframes,
                                                           repeater.scale.keyframes);
    _copiesInterpolator = _copiesInterpolator.create(repeater.copies.keyframes);
    _offsetInterpolator = _offsetInterpolator.create(repeater.offset.keyframes);
    _startOpacityInterpolator = _startOpacityInterpolator.create(repeater.startOpacity.keyframes);
    _endOpacityInterpolator = _endOpacityInterpolator.create(repeater.endOpacity.keyframes);
    
    _instanceLayer = [CALayer layer];
    [self recursivelyAddChildLayers:inputNode];
    
    _replicatorLayer = [CAReplicatorLayer layer];
    _replicatorLayer.actions = @{@"instanceCount" : [NSNull null],
                                 @"instanceTransform" : [NSNull null],
                                 @"instanceAlphaOffset" : [NSNull null]};
    [_replicatorLayer addSublayer:_instanceLayer];
    [self.outputLayer addSublayer:_replicatorLayer];
    
    centerPoint_DEBUG = [CALayer layer];
    centerPoint_DEBUG.bounds = CGRectMake(0, 0, 20, 20);
    if (ENABLE_DEBUG_SHAPES) {
      [self.outputLayer addSublayer:centerPoint_DEBUG];
    }
  }
  return self;
}

- (QMap<QString, QSharedPointer<LOTValueInterpolator>>)valueInterpolators {
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Copies", _copiesInterpolator);
    map.insert("Offset", _offsetInterpolator);
    map.insert("Transform.Anchor Point", _transformInterpolator->anchorInterpolator);
    map.insert("Transform.Position", _transformInterpolator->positionInterpolator);
    map.insert("Transform.Scale", _transformInterpolator->scaleInterpolator);
    map.insert("Transform.Rotation", _transformInterpolator->rotationInterpolator);
    map.insert("Transform.Start Opacity", _startOpacityInterpolator);
    map.insert("Transform.End Opacity", _endOpacityInterpolator);
    return map;
}

- (void)recursivelyAddChildLayers:(LOTAnimatorNode *)node {
  if ([node isKindOfClass:[LOTRenderNode class]]) {
    [_instanceLayer addSublayer:[(LOTRenderNode *)node outputLayer]];
  }
  if (![node isKindOfClass:[LOTRepeaterRenderer class]] &&
      node.inputNode) {
    [self recursivelyAddChildLayers:node.inputNode];
  }
}

- (BOOL)needsUpdateForFrame:(NSNumber *)frame {
  // TODO BW Add offset ability
  return (_transformInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _copiesInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _startOpacityInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _endOpacityInterpolator->hasUpdateForFrame(frame.floatValue));
}

- (void)performLocalUpdate {
  centerPoint_DEBUG.backgroundColor =  [UIColor greenColor].CGColor;
  centerPoint_DEBUG.borderColor = [UIColor lightGrayColor].CGColor;
  centerPoint_DEBUG.borderWidth = 2.f;
  
  CGFloat copies = ceilf(_copiesInterpolator->floatValueForFrame(self.currentFrame.floatValue));
  _replicatorLayer.instanceCount = (NSInteger)copies;
  _replicatorLayer.instanceTransform = _transformInterpolator->transformForFrame(self.currentFrame.floatValue);
  CGFloat startOpacity = _startOpacityInterpolator->floatValueForFrame(self.currentFrame.floatValue);
  CGFloat endOpacity = _endOpacityInterpolator->floatValueForFrame(self.currentFrame.floatValue);
  CGFloat opacityStep = (endOpacity - startOpacity) / copies;
  _instanceLayer.opacity = startOpacity;
  _replicatorLayer.instanceAlphaOffset = opacityStep;
}

@end
