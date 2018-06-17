//
//  LOTPolystarAnimator.m
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTPolystarAnimator.h"
#import "LOTPointInterpolator.h"
#import "LOTNumberInterpolator.h"
#import "LOTBezierPath.h"
#import "CGGeometry+LOTAdditions.h"

#include <QSharedPointer>

const qreal kPOLYSTAR_MAGIC_NUMBER = .47829f;

LOTPolystarAnimator::LOTPolystarAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeStar *shapeStar)
: LOTAnimatorNode(inputNode, shapeStar->keyname)
{
    _outerRadiusInterpolator = _outerRadiusInterpolator.create(shapeStar->outerRadius->keyframes);
    _innerRadiusInterpolator = _innerRadiusInterpolator.create(shapeStar->innerRadius->keyframes);
    _outerRoundnessInterpolator = _outerRoundnessInterpolator.create(shapeStar->outerRoundness->keyframes);
    _innerRoundnessInterpolator = _innerRoundnessInterpolator.create(shapeStar->innerRoundness->keyframes);
    _pointsInterpolator = _pointsInterpolator.create(shapeStar->numberOfPoints->keyframes);
    _rotationInterpolator = _rotationInterpolator.create(shapeStar->rotation->keyframes);
    _positionInterpolator = _positionInterpolator.create(shapeStar->position->keyframes);
}


QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTPolystarAnimator::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Points", _pointsInterpolator);
    map.insert("Position", _positionInterpolator);
    map.insert("Rotation", _rotationInterpolator);
    map.insert("Inner Radius", _innerRadiusInterpolator);
    map.insert("Outer Radius", _outerRadiusInterpolator);
    map.insert("Inner Roundness", _innerRoundnessInterpolator);
    map.insert("Outer Roundness", _outerRoundnessInterpolator);
    return map;
}

bool LOTPolystarAnimator::needsUpdateForFrame(qreal frame)
{
    return (_outerRadiusInterpolator->hasUpdateForFrame(frame) ||
            _innerRadiusInterpolator->hasUpdateForFrame(frame) ||
            _outerRoundnessInterpolator->hasUpdateForFrame(frame) ||
            _innerRoundnessInterpolator->hasUpdateForFrame(frame) ||
            _pointsInterpolator->hasUpdateForFrame(frame) ||
            _rotationInterpolator->hasUpdateForFrame(frame) ||
            _positionInterpolator->hasUpdateForFrame(frame));
}

void LOTPolystarAnimator::performLocalUpdate()
{
    qreal outerRadius = _outerRadiusInterpolator->floatValueForFrame(currentFrame);
    qreal innerRadius = _innerRadiusInterpolator->floatValueForFrame(currentFrame);
    qreal outerRoundness = _outerRoundnessInterpolator->floatValueForFrame(currentFrame) / 100.f;
    qreal innerRoundness = _innerRoundnessInterpolator->floatValueForFrame(currentFrame)/ 100.f;
    qreal points = _pointsInterpolator->floatValueForFrame(currentFrame);
    qreal rotation = _rotationInterpolator->floatValueForFrame(currentFrame);
    QPointF position = _positionInterpolator->pointValueForFrame(currentFrame);
    QSharedPointer<LOTBezierPath> path = path.create();
    path->cacheLengths = pathShouldCacheLengths();
    qreal currentAngle = LOT_DegreesToRadians(rotation - 90);
    qreal anglePerPoint = (qreal)((2 * M_PI) / points);
    qreal halfAnglePerPoint = anglePerPoint / 2.0f;
    qreal partialPointAmount = points - floor(points);
    if (partialPointAmount != 0) {
      currentAngle += halfAnglePerPoint * (1.f - partialPointAmount);
    }

    qreal x;
    qreal y;
    qreal previousX;
    qreal previousY;
    qreal partialPointRadius = 0;
    if (partialPointAmount != 0) {
      partialPointRadius = innerRadius + partialPointAmount * (outerRadius - innerRadius);
      x = (qreal) (partialPointRadius * cosf(currentAngle));
      y = (qreal) (partialPointRadius * sinf(currentAngle));
      path->LOT_moveToPoint(QPointF(x, y));
      currentAngle += anglePerPoint * partialPointAmount / 2.f;
    } else {
      x = (float) (outerRadius * cosf(currentAngle));
      y = (float) (outerRadius * sinf(currentAngle));
      path->LOT_moveToPoint(QPointF(x, y));
      currentAngle += halfAnglePerPoint;
    }

    // True means the line will go to outer radius. False means inner radius.
    bool longSegment = false;
    qreal numPoints = ceil(points) * 2;
    for (int i = 0; i < numPoints; i++) {
      qreal radius = longSegment ? outerRadius : innerRadius;
      qreal dTheta = halfAnglePerPoint;
      if (partialPointRadius != 0 && i == numPoints - 2) {
        dTheta = anglePerPoint * partialPointAmount / 2.f;
      }
      if (partialPointRadius != 0 && i == numPoints - 1) {
        radius = partialPointRadius;
      }
      previousX = x;
      previousY = y;
      x = (qreal) (radius * cosf(currentAngle));
      y = (qreal) (radius * sinf(currentAngle));

      if (innerRoundness == 0 && outerRoundness == 0) {
        path->LOT_addLineToPoint(QPointF(x, y));
      } else {
        qreal cp1Theta = (qreal) (atan2f(previousY, previousX) - M_PI / 2.f);
        qreal cp1Dx = (qreal) cosf(cp1Theta);
        qreal cp1Dy = (qreal) sinf(cp1Theta);

        qreal cp2Theta = (qreal) (atan2f(y, x) - M_PI / 2.f);
        qreal cp2Dx = (qreal) cosf(cp2Theta);
        qreal cp2Dy = (qreal) sinf(cp2Theta);

        qreal cp1Roundedness = longSegment ? innerRoundness : outerRoundness;
        qreal cp2Roundedness = longSegment ? outerRoundness : innerRoundness;
        qreal cp1Radius = longSegment ? innerRadius : outerRadius;
        qreal cp2Radius = longSegment ? outerRadius : innerRadius;

        qreal cp1x = cp1Radius * cp1Roundedness * kPOLYSTAR_MAGIC_NUMBER * cp1Dx;
        qreal cp1y = cp1Radius * cp1Roundedness * kPOLYSTAR_MAGIC_NUMBER * cp1Dy;
        qreal cp2x = cp2Radius * cp2Roundedness * kPOLYSTAR_MAGIC_NUMBER * cp2Dx;
        qreal cp2y = cp2Radius * cp2Roundedness * kPOLYSTAR_MAGIC_NUMBER * cp2Dy;
        if (partialPointAmount != 0) {
          if (i == 0) {
            cp1x *= partialPointAmount;
            cp1y *= partialPointAmount;
          } else if (i == numPoints - 1) {
            cp2x *= partialPointAmount;
            cp2y *= partialPointAmount;
          }
        }
        path->LOT_addCurveToPoint(QPointF(x, y),
                                  QPointF(previousX - cp1x, previousY - cp1y),
                                  QPointF(x + cp2x, y + cp2y));
      }
      currentAngle += dTheta;
      longSegment = !longSegment;
    }
    path->LOT_closePath();
//    path->LOT_applyTransform(CGAffineTransformMakeTranslation(position.x(), position.y()));
    path->LOT_applyTransform(QTransform().translate(position.x(), position.y()));

    setLocalPath(path);
}
