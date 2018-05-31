//
//  LOTStrokeRenderer.m
//  Lottie
//
//  Created by brandon_withrow on 7/17/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTStrokeRenderer.h"
#import "LOTColorInterpolator.h"
#import "LOTNumberInterpolator.h"

#include <QSharedPointer>
#include <QList>

@implementation LOTStrokeRenderer {
  QSharedPointer<LOTColorInterpolator> _colorInterpolator;
  QSharedPointer<LOTNumberInterpolator> _opacityInterpolator;
  QSharedPointer<LOTNumberInterpolator> _widthInterpolator;
  QSharedPointer<LOTNumberInterpolator> _dashOffsetInterpolator;
  QList<QSharedPointer<LOTNumberInterpolator>> _dashPatternInterpolators;
}

- (instancetype)initWithInputNode:(LOTAnimatorNode *)inputNode
                                shapeStroke:(LOTShapeStroke *)stroke {
  self = [super initWithInputNode:inputNode keyName:stroke.keyname];
  if (self) {
    _colorInterpolator = _colorInterpolator.create(stroke.color.keyframes);
    _opacityInterpolator = _opacityInterpolator.create(stroke.opacity.keyframes);
    _widthInterpolator = _widthInterpolator.create(stroke.width.keyframes);
    
    QList<QSharedPointer<LOTNumberInterpolator>> dashPatternIntpolators;
    NSMutableArray *dashPatterns = [NSMutableArray array];
    for (LOTKeyframeGroup *keyframegroup in stroke.lineDashPattern) {
      QSharedPointer<LOTNumberInterpolator> interpolator = interpolator.create(keyframegroup.keyframes);
      dashPatternIntpolators.append(interpolator);
      if (dashPatterns && keyframegroup.keyframes.count == 1) {
        LOTKeyframe *first = keyframegroup.keyframes.firstObject;
        [dashPatterns addObject:@(first.floatValue)];
      }
      if (keyframegroup.keyframes.count > 1) {
        dashPatterns = nil;
      }
    }
    
    if (dashPatterns.count) {
      self.outputLayer.lineDashPattern = dashPatterns;
    } else {
      _dashPatternInterpolators = dashPatternIntpolators;
    }
    
    if (stroke.dashOffset) {
      _dashOffsetInterpolator = _dashOffsetInterpolator.create(stroke.dashOffset.keyframes);
    }
    
    self.outputLayer.fillColor = nil;
    self.outputLayer.lineCap = stroke.capType == LOTLineCapTypeRound ? kCALineCapRound : kCALineCapButt;
    switch (stroke.joinType) {
      case LOTLineJoinTypeBevel:
        self.outputLayer.lineJoin = kCALineJoinBevel;
        break;
      case LOTLineJoinTypeMiter:
        self.outputLayer.lineJoin = kCALineJoinMiter;
        break;
      case LOTLineJoinTypeRound:
        self.outputLayer.lineJoin = kCALineJoinRound;
        break;
      default:
        break;
    }
  }
  return self;
}

- (QMap<QString, QSharedPointer<LOTValueInterpolator>>)valueInterpolators {
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Color", _colorInterpolator);
    map.insert("Opacity", _opacityInterpolator);
    map.insert("Stroke Width", _widthInterpolator);
    return map;
}

- (void)_updateLineDashPatternsForFrame:(NSNumber *)frame {
  if (_dashPatternInterpolators.size()) {
    NSMutableArray *lineDashPatterns = [NSMutableArray array];
    CGFloat dashTotal = 0;
    for (auto interpolator : _dashPatternInterpolators) {
      CGFloat patternValue = interpolator->floatValueForFrame(frame.floatValue);
      dashTotal = dashTotal + patternValue;
      [lineDashPatterns addObject:@(patternValue)];
    }
    if (dashTotal > 0) {
      self.outputLayer.lineDashPattern = lineDashPatterns;
    }
  }
}

- (BOOL)needsUpdateForFrame:(NSNumber *)frame {
  [self _updateLineDashPatternsForFrame:frame];
  BOOL dashOffset = NO;
  if (_dashOffsetInterpolator) {
    dashOffset = _dashOffsetInterpolator->hasUpdateForFrame(frame.floatValue);
  }
  return (dashOffset ||
          _colorInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _opacityInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _widthInterpolator->hasUpdateForFrame(frame.floatValue));
}

- (void)performLocalUpdate {
  self.outputLayer.lineDashPhase = _dashOffsetInterpolator->floatValueForFrame(self.currentFrame.floatValue);
  self.outputLayer.strokeColor = _colorInterpolator->colorForFrame(self.currentFrame);
  self.outputLayer.lineWidth = _widthInterpolator->floatValueForFrame(self.currentFrame.floatValue);
  self.outputLayer.opacity = _opacityInterpolator->floatValueForFrame(self.currentFrame.floatValue);
}

- (void)rebuildOutputs {
  self.outputLayer.path = self.inputNode.outputPath.CGPath;
}

- (NSDictionary *)actionsForRenderLayer {
  return @{@"strokeColor": [NSNull null],
           @"lineWidth": [NSNull null],
           @"opacity" : [NSNull null]};
}

@end
