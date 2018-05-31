//
//  LOTFillRenderer.m
//  Lottie
//
//  Created by brandon_withrow on 6/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTFillRenderer.h"
#import "LOTColorInterpolator.h"
#import "LOTNumberInterpolator.h"
#import "LOTHelpers.h"

#include <QSharedPointer>

@implementation LOTFillRenderer {
  QSharedPointer<LOTColorInterpolator> colorInterpolator_;
  QSharedPointer<LOTNumberInterpolator> opacityInterpolator_;
  BOOL _evenOddFillRule;
  CALayer *centerPoint_DEBUG;
}

- (instancetype)initWithInputNode:(LOTAnimatorNode *)inputNode
                                  shapeFill:(LOTShapeFill *)fill {
  self = [super initWithInputNode:inputNode keyName:fill.keyname];
  if (self) {
    colorInterpolator_ = colorInterpolator_.create(fill.color.keyframes);
    opacityInterpolator_ = opacityInterpolator_.create(fill.opacity.keyframes);
    centerPoint_DEBUG = [CALayer layer];
    centerPoint_DEBUG.bounds = CGRectMake(0, 0, 20, 20);
    if (ENABLE_DEBUG_SHAPES) {
      [self.outputLayer addSublayer:centerPoint_DEBUG];
    }
    _evenOddFillRule = fill.evenOddFillRule;
    
    self.outputLayer.fillRule = _evenOddFillRule ? @"even-odd" : @"non-zero";
  }
  return self;
}

- (QMap<QString, QSharedPointer<LOTValueInterpolator>>)valueInterpolators {
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Color", colorInterpolator_);
    map.insert("Opacity", opacityInterpolator_);
    return map;
}

- (BOOL)needsUpdateForFrame:(NSNumber *)frame {
  return colorInterpolator_->hasUpdateForFrame(frame.floatValue) || opacityInterpolator_->hasUpdateForFrame(frame.floatValue);
}

- (void)performLocalUpdate {
  centerPoint_DEBUG.backgroundColor =  colorInterpolator_->colorForFrame(self.currentFrame);
  centerPoint_DEBUG.borderColor = [UIColor lightGrayColor].CGColor;
  centerPoint_DEBUG.borderWidth = 2.f;
  self.outputLayer.fillColor = colorInterpolator_->colorForFrame(self.currentFrame);
  self.outputLayer.opacity = opacityInterpolator_->floatValueForFrame(self.currentFrame.floatValue);
}

- (void)rebuildOutputs {
  self.outputLayer.path = self.inputNode.outputPath.CGPath;
}

- (NSDictionary *)actionsForRenderLayer {
  return @{@"backgroundColor": [NSNull null],
           @"fillColor": [NSNull null],
           @"opacity" : [NSNull null]};
}

@end
