//
//  LOTTrimPathNode.m
//  Lottie
//
//  Created by brandon_withrow on 7/21/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTTrimPathNode.h"
#import "LOTNumberInterpolator.h"
#import "LOTPathAnimator.h"
#import "LOTCircleAnimator.h"
#import "LOTRoundedRectAnimator.h"
#import "LOTRenderGroup.h"

#include <QSharedPointer>

@implementation LOTTrimPathNode {
  QSharedPointer<LOTNumberInterpolator> _startInterpolator;
  QSharedPointer<LOTNumberInterpolator> _endInterpolator;
  QSharedPointer<LOTNumberInterpolator> _offsetInterpolator;
  
  CGFloat _startT;
  CGFloat _endT;
  CGFloat _offsetT;
}

- (instancetype _Nonnull)initWithInputNode:(LOTAnimatorNode *_Nullable)inputNode
                                   trimPath:(LOTShapeTrimPath *_Nonnull)trimPath {
  self = [super initWithInputNode:inputNode keyName:trimPath.keyname];
  if (self) {
    inputNode.pathShouldCacheLengths = YES;
    _startInterpolator = _startInterpolator.create(trimPath.start.keyframes);
    _endInterpolator = _endInterpolator.create(trimPath.end.keyframes);
    _offsetInterpolator = _offsetInterpolator.create(trimPath.offset.keyframes);
  }
  return self;
}

- (QMap<QString, QSharedPointer<LOTValueInterpolator>>)valueInterpolators {
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Start", _startInterpolator);
    map.insert("End", _endInterpolator);
    map.insert("Offset", _offsetInterpolator);
    return map;
}

- (BOOL)needsUpdateForFrame:(NSNumber *)frame {
  return (_startInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _endInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _offsetInterpolator->hasUpdateForFrame(frame.floatValue));
}

- (BOOL)updateWithFrame:(NSNumber *)frame
      withModifierBlock:(void (^ _Nullable)(LOTAnimatorNode * _Nonnull))modifier
       forceLocalUpdate:(BOOL)forceUpdate {
  BOOL localUpdate = [self needsUpdateForFrame:frame];
  [self forceSetCurrentFrame:frame];
  if (localUpdate) {
    [self performLocalUpdate];
  }
  if (self.inputNode == nil) {
    return localUpdate;
  }
  
  BOOL inputUpdated = [self.inputNode updateWithFrame:frame withModifierBlock:^(LOTAnimatorNode * _Nonnull inputNode) {
    if ([inputNode isKindOfClass:[LOTPathAnimator class]] ||
        [inputNode isKindOfClass:[LOTCircleAnimator class]] ||
        [inputNode isKindOfClass:[LOTRoundedRectAnimator class]]) {
      [inputNode.localPath trimPathFromT:self->_startT toT:self->_endT offset:self->_offsetT];
    }
    if (modifier) {
      modifier(inputNode);
    }
    
  } forceLocalUpdate:(localUpdate || forceUpdate)];
  
  return inputUpdated;
}

- (void)performLocalUpdate {
  _startT = _startInterpolator->floatValueForFrame(self.currentFrame.floatValue) / 100;
  _endT = _endInterpolator->floatValueForFrame(self.currentFrame.floatValue) / 100;
  _offsetT = _offsetInterpolator->floatValueForFrame(self.currentFrame.floatValue) / 360;
}

- (void)rebuildOutputs {
  // Skip this step.
}

- (LOTBezierPath *)localPath {
  return self.inputNode.localPath;
}

/// Forwards its input node's output path forwards downstream
- (LOTBezierPath *)outputPath {
  return self.inputNode.outputPath;
}

@end
