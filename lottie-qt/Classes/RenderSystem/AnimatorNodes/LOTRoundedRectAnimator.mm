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

static void addCorner(const QPointF &cornerPoint, CGFloat radius, QSharedPointer<LOTBezierPath> path, bool clockwise)
{
  QPointF currentPoint = path->currentPoint();
  
  CGFloat ellipseControlPointPercentage = 0.55228;
  
  if (cornerPoint.y() == currentPoint.y()) {
    // Moving east/west
    if (cornerPoint.x() < currentPoint.x()) {
      // Moving west
      QPointF corner = QPointF(cornerPoint.x() + radius, currentPoint.y());
      path->LOT_addLineToPoint(corner);
      if (radius) {
        QPointF curvePoint = clockwise ? QPointF(cornerPoint.x(), cornerPoint.y() - radius) : QPointF(cornerPoint.x(), cornerPoint.y() + radius);
        QPointF cp1 = QPointF(corner.x() - (radius * ellipseControlPointPercentage), corner.y());
        QPointF cp2 = (clockwise ?
                       QPointF(curvePoint.x(), curvePoint.y() + (radius * ellipseControlPointPercentage)) :
                       QPointF(curvePoint.x(), curvePoint.y() - (radius * ellipseControlPointPercentage)));
        path->LOT_addCurveToPoint(curvePoint, cp1, cp2);
      }
    } else {
      // Moving east
      QPointF corner = QPointF(cornerPoint.x() - radius, currentPoint.y());
      path->LOT_addLineToPoint(corner);
      if (radius) {
        QPointF curvePoint = clockwise ? QPointF(cornerPoint.x(), cornerPoint.y() + radius) : QPointF(cornerPoint.x(), cornerPoint.y() - radius);
        QPointF cp1 = QPointF(corner.x() + (radius * ellipseControlPointPercentage), corner.y());
        QPointF cp2 = (clockwise ?
                       QPointF(curvePoint.x(), curvePoint.y() - (radius * ellipseControlPointPercentage)) :
                       QPointF(curvePoint.x(), curvePoint.y() + (radius * ellipseControlPointPercentage)));
        path->LOT_addCurveToPoint(curvePoint, cp1, cp2);
      }
    }
  } else {
    // Moving North/South
    if (cornerPoint.y() < currentPoint.y()) {
      // Moving North
      QPointF corner = QPointF(currentPoint.x(), cornerPoint.y() + radius);
      path->LOT_addLineToPoint(corner);
      if (radius) {
        QPointF curvePoint = clockwise ? QPointF(cornerPoint.x() + radius, cornerPoint.y()) : QPointF(cornerPoint.x() - radius, cornerPoint.y());
        QPointF cp1 = QPointF(corner.x(), corner.y()  - (radius * ellipseControlPointPercentage));
        QPointF cp2 = (clockwise ?
                       QPointF(curvePoint.x() - (radius * ellipseControlPointPercentage), curvePoint.y()) :
                       QPointF(curvePoint.x() + (radius * ellipseControlPointPercentage), curvePoint.y()));
        path->LOT_addCurveToPoint(curvePoint, cp1, cp2);
      }

    } else {
      // moving south
      QPointF corner = QPointF(currentPoint.x(), cornerPoint.y() - radius);
      path->LOT_addLineToPoint(corner);
      if (radius) {
        QPointF curvePoint = clockwise ? QPointF(cornerPoint.x() - radius, cornerPoint.y()) : QPointF(cornerPoint.x() + radius, cornerPoint.y());
        QPointF cp1 = QPointF(corner.x(), corner.y()  + (radius * ellipseControlPointPercentage));
        QPointF cp2 = (clockwise ?
                       QPointF(curvePoint.x() + (radius * ellipseControlPointPercentage), curvePoint.y()) :
                       QPointF(curvePoint.x() - (radius * ellipseControlPointPercentage), curvePoint.y()));
        path->LOT_addCurveToPoint(curvePoint, cp1, cp2);
      }
    }
  }
}

LOTRoundedRectAnimator::LOTRoundedRectAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeRectangle *shapeRectangle)
: LOTAnimatorNode(inputNode, shapeRectangle->keyname)
{
    _centerInterpolator = _centerInterpolator.create(shapeRectangle->position->keyframes);
    _sizeInterpolator = _sizeInterpolator.create(shapeRectangle->size->keyframes);
    _cornerRadiusInterpolator = _cornerRadiusInterpolator.create(shapeRectangle->cornerRadius->keyframes);
    _reversed = shapeRectangle->reversed;
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
    QPointF size = _sizeInterpolator->pointValueForFrame(currentFrame);
    QPointF position = _centerInterpolator->pointValueForFrame(currentFrame);

    CGFloat halfWidth = size.x() / 2;
    CGFloat halfHeight = size.y() / 2;

    QRectF rectFrame(position.x() - halfWidth, position.y() - halfHeight, size.x(), size.y());

    QPointF topLeft = rectFrame.topLeft();
    QPointF topRight = rectFrame.topRight();
    QPointF bottomLeft = rectFrame.bottomLeft();
    QPointF bottomRight = rectFrame.bottomRight();
    // UIBezierPath Draws rects from the top left corner, After Effects draws them from the top right.
    // Switching to manual drawing.

    CGFloat radius = MIN(MIN(halfWidth, halfHeight), cornerRadius);
    BOOL clockWise = !_reversed;

    QSharedPointer<LOTBezierPath> path1 = path1.create();
    path1->cacheLengths = pathShouldCacheLengths();
    QPointF startPoint = (clockWise ?
                          QPointF(topRight.x(), topRight.y() + radius) :
                          QPointF(topRight.x() - radius, topRight.y()));
    path1->LOT_moveToPoint(startPoint);
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
    path1->LOT_closePath();

    setLocalPath(path1);
}
