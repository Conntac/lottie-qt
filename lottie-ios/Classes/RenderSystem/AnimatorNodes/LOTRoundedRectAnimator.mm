//
//  LOTRoundedRectAnimator.m
//  Lottie
//
//  Created by brandon_withrow on 7/19/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTRoundedRectAnimator.h"
#import "LOTPointInterpolator.h"
#import "LOTNumberInterpolator.h"
#import "CGGeometry+LOTAdditions.h"

#include <QSharedPointer>

static void addCorner(CGPoint cornerPoint, CGFloat radius, LOTBezierPath *path, bool clockwise)
{
  CGPoint currentPoint = path.currentPoint;
  
  CGFloat ellipseControlPointPercentage = 0.55228;
  
  if (cornerPoint.y == currentPoint.y) {
    // Moving east/west
    if (cornerPoint.x < currentPoint.x) {
      // Moving west
      CGPoint corner = CGPointMake(cornerPoint.x + radius, currentPoint.y);
      [path LOT_addLineToPoint:corner];
      if (radius) {
        CGPoint curvePoint = clockwise ? CGPointMake(cornerPoint.x, cornerPoint.y - radius) : CGPointMake(cornerPoint.x, cornerPoint.y + radius);
        CGPoint cp1 = CGPointMake(corner.x - (radius * ellipseControlPointPercentage), corner.y);
        CGPoint cp2 = (clockwise ?
                       CGPointMake(curvePoint.x, curvePoint.y + (radius * ellipseControlPointPercentage)) :
                       CGPointMake(curvePoint.x, curvePoint.y - (radius * ellipseControlPointPercentage)));
        [path LOT_addCurveToPoint:curvePoint controlPoint1:cp1 controlPoint2:cp2];
      }
    } else {
      // Moving east
      CGPoint corner = CGPointMake(cornerPoint.x - radius, currentPoint.y);
      [path LOT_addLineToPoint:corner];
      if (radius) {
        CGPoint curvePoint = clockwise ? CGPointMake(cornerPoint.x, cornerPoint.y + radius) : CGPointMake(cornerPoint.x, cornerPoint.y - radius);
        CGPoint cp1 = CGPointMake(corner.x + (radius * ellipseControlPointPercentage), corner.y);
        CGPoint cp2 = (clockwise ?
                       CGPointMake(curvePoint.x, curvePoint.y - (radius * ellipseControlPointPercentage)) :
                       CGPointMake(curvePoint.x, curvePoint.y + (radius * ellipseControlPointPercentage)));
        [path LOT_addCurveToPoint:curvePoint controlPoint1:cp1 controlPoint2:cp2];
      }
    }
  } else {
    // Moving North/South
    if (cornerPoint.y < currentPoint.y) {
      // Moving North
      CGPoint corner = CGPointMake(currentPoint.x, cornerPoint.y + radius);
      [path LOT_addLineToPoint:corner];
      if (radius) {
        CGPoint curvePoint = clockwise ? CGPointMake(cornerPoint.x + radius, cornerPoint.y) : CGPointMake(cornerPoint.x - radius, cornerPoint.y);
        CGPoint cp1 = CGPointMake(corner.x, corner.y  - (radius * ellipseControlPointPercentage));
        CGPoint cp2 = (clockwise ?
                       CGPointMake(curvePoint.x - (radius * ellipseControlPointPercentage), curvePoint.y) :
                       CGPointMake(curvePoint.x + (radius * ellipseControlPointPercentage), curvePoint.y));
        [path LOT_addCurveToPoint:curvePoint controlPoint1:cp1 controlPoint2:cp2];
      }

    } else {
      // moving south
      CGPoint corner = CGPointMake(currentPoint.x, cornerPoint.y - radius);
      [path LOT_addLineToPoint:corner];
      if (radius) {
        CGPoint curvePoint = clockwise ? CGPointMake(cornerPoint.x - radius, cornerPoint.y) : CGPointMake(cornerPoint.x + radius, cornerPoint.y);
        CGPoint cp1 = CGPointMake(corner.x, corner.y  + (radius * ellipseControlPointPercentage));
        CGPoint cp2 = (clockwise ?
                       CGPointMake(curvePoint.x + (radius * ellipseControlPointPercentage), curvePoint.y) :
                       CGPointMake(curvePoint.x - (radius * ellipseControlPointPercentage), curvePoint.y));
        [path LOT_addCurveToPoint:curvePoint controlPoint1:cp1 controlPoint2:cp2];
      }
    }
  }
}

LOTRoundedRectAnimator::LOTRoundedRectAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeRectangle *shapeRectangle)
: LOTAnimatorNode(inputNode, shapeRectangle.keyname)
{
    _centerInterpolator = _centerInterpolator.create(shapeRectangle.position.keyframes);
    _sizeInterpolator = _sizeInterpolator.create(shapeRectangle.size.keyframes);
    _cornerRadiusInterpolator = _cornerRadiusInterpolator.create(shapeRectangle.cornerRadius.keyframes);
    _reversed = shapeRectangle.reversed;
}

QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTRoundedRectAnimator::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Size", _sizeInterpolator);
    map.insert("Position", _centerInterpolator);
    map.insert("Roundness", _cornerRadiusInterpolator);
    return map;
}

bool LOTRoundedRectAnimator::needsUpdateForFrame(qreal frame)
{
    return _centerInterpolator->hasUpdateForFrame(frame) || _sizeInterpolator->hasUpdateForFrame(frame) || _cornerRadiusInterpolator->hasUpdateForFrame(frame);
}

void LOTRoundedRectAnimator::performLocalUpdate()
{
    CGFloat cornerRadius = _cornerRadiusInterpolator->floatValueForFrame(currentFrame);
    CGPoint size = _sizeInterpolator->pointValueForFrame(currentFrame).toCGPoint();
    CGPoint position = _centerInterpolator->pointValueForFrame(currentFrame).toCGPoint();

    CGFloat halfWidth = size.x / 2;
    CGFloat halfHeight = size.y / 2;

    CGRect rectFrame =  CGRectMake(position.x - halfWidth, position.y - halfHeight, size.x, size.y);

    CGPoint topLeft = CGPointMake(CGRectGetMinX(rectFrame), CGRectGetMinY(rectFrame));
    CGPoint topRight = CGPointMake(CGRectGetMaxX(rectFrame), CGRectGetMinY(rectFrame));
    CGPoint bottomLeft = CGPointMake(CGRectGetMinX(rectFrame), CGRectGetMaxY(rectFrame));
    CGPoint bottomRight = CGPointMake(CGRectGetMaxX(rectFrame), CGRectGetMaxY(rectFrame));
    // UIBezierPath Draws rects from the top left corner, After Effects draws them from the top right.
    // Switching to manual drawing.

    CGFloat radius = MIN(MIN(halfWidth, halfHeight), cornerRadius);
    BOOL clockWise = !_reversed;

    LOTBezierPath *path1 = [[LOTBezierPath alloc] init];
    path1.cacheLengths = pathShouldCacheLengths();
    CGPoint startPoint = (clockWise ?
                          CGPointMake(topRight.x, topRight.y + radius) :
                          CGPointMake(topRight.x - radius, topRight.y));
    [path1 LOT_moveToPoint:startPoint];
    if (clockWise) {
      addCorner(bottomRight, radius, path1, clockWise);
      addCorner(bottomLeft, radius, path1, clockWise);
      addCorner(topLeft, radius, path1, clockWise);
      addCorner(topRight, radius, path1, clockWise);
    } else {
      addCorner(topLeft, radius, path1, clockWise);
      addCorner(bottomLeft, radius, path1, clockWise);
      addCorner(bottomRight, radius, path1, clockWise);
      addCorner(topRight, radius, path1, clockWise);
    }
    [path1 LOT_closePath];

    setLocalPath(path1);
}
