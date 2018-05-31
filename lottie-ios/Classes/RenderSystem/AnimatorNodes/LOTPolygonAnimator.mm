//
//  LOTPolygonAnimator.m
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTPolygonAnimator.h"
#import "LOTKeyframe.h"
#import "LOTPointInterpolator.h"
#import "LOTNumberInterpolator.h"
#import "LOTBezierPath.h"
#import "CGGeometry+LOTAdditions.h"

#include <QSharedPointer>

const CGFloat kPOLYGON_MAGIC_NUMBER = .25f;

@implementation LOTPolygonAnimator {
  QSharedPointer<LOTNumberInterpolator> _outerRadiusInterpolator;
  QSharedPointer<LOTNumberInterpolator> _outerRoundnessInterpolator;
  QSharedPointer<LOTPointInterpolator> _positionInterpolator;
  QSharedPointer<LOTNumberInterpolator> _pointsInterpolator;
  QSharedPointer<LOTNumberInterpolator> _rotationInterpolator;
}

- (instancetype _Nonnull)initWithInputNode:(LOTAnimatorNode *_Nullable)inputNode
                             shapePolygon:(LOTShapeStar *_Nonnull)shapeStar {
  self = [super initWithInputNode:inputNode keyName:shapeStar.keyname];
  if (self) {
    _outerRadiusInterpolator = _outerRadiusInterpolator.create(shapeStar.outerRadius.keyframes);
    _outerRoundnessInterpolator = _outerRoundnessInterpolator.create(shapeStar.outerRoundness.keyframes);
    _pointsInterpolator = _pointsInterpolator.create(shapeStar.numberOfPoints.keyframes);
    _rotationInterpolator = _rotationInterpolator.create(shapeStar.rotation.keyframes);
    _positionInterpolator = _positionInterpolator.create(shapeStar.position.keyframes);
  }
  return self;
}

- (QMap<QString, QSharedPointer<LOTValueInterpolator>>)valueInterpolators {
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Points", _pointsInterpolator);
    map.insert("Position", _positionInterpolator);
    map.insert("Rotation", _rotationInterpolator);
    map.insert("Outer Radius", _outerRadiusInterpolator);
    map.insert("Outer Roundness", _outerRoundnessInterpolator);
    return map;
}

- (BOOL)needsUpdateForFrame:(NSNumber *)frame {
  return (_outerRadiusInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _outerRoundnessInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _pointsInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _rotationInterpolator->hasUpdateForFrame(frame.floatValue) ||
          _positionInterpolator->hasUpdateForFrame(frame.floatValue));
}

- (void)performLocalUpdate {
  CGFloat outerRadius = _outerRadiusInterpolator->floatValueForFrame(self.currentFrame.floatValue);
  CGFloat outerRoundness = _outerRoundnessInterpolator->floatValueForFrame(self.currentFrame.floatValue) / 100.f;
  CGFloat points = _pointsInterpolator->floatValueForFrame(self.currentFrame.floatValue);
  CGFloat rotation = _rotationInterpolator->floatValueForFrame(self.currentFrame.floatValue);
  CGPoint position = _positionInterpolator->pointValueForFrame(self.currentFrame.floatValue).toCGPoint();
  
  LOTBezierPath *path = [[LOTBezierPath alloc] init];
  path.cacheLengths = self.pathShouldCacheLengths;
  CGFloat currentAngle = LOT_DegreesToRadians(rotation - 90);
  CGFloat anglePerPoint = (CGFloat)((2 * M_PI) / points);

  CGFloat x;
  CGFloat y;
  CGFloat previousX;
  CGFloat previousY;
  x = (CGFloat) (outerRadius * cosf(currentAngle));
  y = (CGFloat) (outerRadius * sinf(currentAngle));
  [path LOT_moveToPoint:CGPointMake(x, y)];
  currentAngle += anglePerPoint;
  
  double numPoints = ceil(points);
  for (int i = 0; i < numPoints; i++) {
    previousX = x;
    previousY = y;
    x = (CGFloat) (outerRadius * cosf(currentAngle));
    y = (CGFloat) (outerRadius * sinf(currentAngle));
    
    if (outerRoundness != 0) {
      CGFloat cp1Theta = (CGFloat) (atan2(previousY, previousX) - M_PI / 2.f);
      CGFloat cp1Dx = (CGFloat) cosf(cp1Theta);
      CGFloat cp1Dy = (CGFloat) sinf(cp1Theta);
      
      CGFloat cp2Theta = (CGFloat) (atan2(y, x) - M_PI / 2.f);
      CGFloat cp2Dx = (CGFloat) cosf(cp2Theta);
      CGFloat cp2Dy = (CGFloat) sinf(cp2Theta);
      
      CGFloat cp1x = outerRadius * outerRoundness * kPOLYGON_MAGIC_NUMBER * cp1Dx;
      CGFloat cp1y = outerRadius * outerRoundness * kPOLYGON_MAGIC_NUMBER * cp1Dy;
      CGFloat cp2x = outerRadius * outerRoundness * kPOLYGON_MAGIC_NUMBER * cp2Dx;
      CGFloat cp2y = outerRadius * outerRoundness * kPOLYGON_MAGIC_NUMBER * cp2Dy;
      [path LOT_addCurveToPoint:CGPointMake(x, y)
                  controlPoint1:CGPointMake(previousX - cp1x, previousY - cp1y)
                  controlPoint2:CGPointMake(x + cp2x, y + cp2y)];
    } else {
      [path LOT_addLineToPoint:CGPointMake(x, y)];
    }
    
    currentAngle += anglePerPoint;
  }
  [path LOT_closePath];
  [path LOT_applyTransform:CGAffineTransformMakeTranslation(position.x, position.y)];
  self.localPath = path;
}

@end
