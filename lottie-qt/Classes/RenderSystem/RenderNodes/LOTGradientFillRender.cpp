//
//  LOTGradientFillRender.m
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTGradientFillRender.h"
#include "LOTArrayInterpolator.h"
#include "LOTPointInterpolator.h"
#include "LOTNumberInterpolator.h"
#include "CGGeometry+LOTAdditions.h"
#include "LOTHelpers.h"

#include <QSharedPointer>

LOTGradientFillRender::LOTGradientFillRender(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeGradientFill *fill)
: LOTRenderNode(inputNode, fill->keyname)
{
  _gradientInterpolator = _gradientInterpolator.create(fill->gradient->keyframes);
  _startPointInterpolator = _startPointInterpolator.create(fill->startPoint->keyframes);
  _endPointInterpolator = _endPointInterpolator.create(fill->endPoint->keyframes);
  _opacityInterpolator = _opacityInterpolator.create(fill->opacity->keyframes);
  _numberOfPositions = fill->numberOfColors;

  _evenOddFillRule = fill->evenOddFillRule;
  QSharedPointer<QQuickLottieLayer> wrapperLayer = wrapperLayer.create();
  _maskShape = _maskShape.create();
  _maskShape->setFillRule(_evenOddFillRule ? Qt::OddEvenFill : Qt::WindingFill);
  _maskShape->setFillColor(Qt::white);
  _maskShape->actions = {{"path", QVariant()}};

  Q_ASSERT(false);
//  _gradientOpacityLayer = _gradientOpacityLayer.create();
//  _gradientOpacityLayer->isRadial = (fill->type == LOTGradientTypeRadial);
//  _gradientOpacityLayer->actions = {{"startPoint", QVariant()},
//                                   {"endPoint", QVariant()},
//                                   {"opacity", QVariant()},
//                                   {"locations", QVariant()},
//                                   {"colors", QVariant()},
//                                   {"bounds", QVariant()},
//                                   {"anchorPoint", QVariant()},
//                                   {"isRadial", QVariant()}};
//  _gradientOpacityLayer->mask = _maskShape;
//  wrapperLayer->addSublayer(_gradientOpacityLayer);

//  _gradientLayer = _gradientLayer.create();
//  _gradientLayer->isRadial = (fill->type == LOTGradientTypeRadial);
//  _gradientLayer->mask = wrapperLayer;
//  _gradientLayer->actions = [_gradientOpacityLayer.actions copy];
//  outputLayer->addSublayer(_gradientLayer);

  centerPoint_DEBUG = centerPoint_DEBUG.create();
  centerPoint_DEBUG->bounds = QRectF(0, 0, 20, 20);
  if (ENABLE_DEBUG_SHAPES) {
      outputLayer->addSublayer(centerPoint_DEBUG);
  }
}

//NSDictionary *LOTGradientFillRender::actionsForRenderLayer() const
//{
//    return @{@"backgroundColor": [NSNull null],
//             @"fillColor": [NSNull null],
//             @"opacity" : [NSNull null]};
//}

QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTGradientFillRender::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Start Point", _startPointInterpolator);
    map.insert("End Point", _endPointInterpolator);
    map.insert("Opacity", _opacityInterpolator);
    return map;
}

bool LOTGradientFillRender::needsUpdateForFrame(qreal frame)
{
    return (_gradientInterpolator->hasUpdateForFrame(frame) ||
            _startPointInterpolator->hasUpdateForFrame(frame) ||
            _endPointInterpolator->hasUpdateForFrame(frame) ||
            _opacityInterpolator->hasUpdateForFrame(frame));
}

void LOTGradientFillRender::performLocalUpdate()
{
    Q_ASSERT(false);
//    centerPoint_DEBUG.backgroundColor =  [UIColor magentaColor].CGColor;
//    centerPoint_DEBUG.borderColor = [UIColor lightGrayColor].CGColor;
//    centerPoint_DEBUG.borderWidth = 2.f;
//    _startPoint = _startPointInterpolator->pointValueForFrame(currentFrame);
//    _endPoint = _endPointInterpolator->pointValueForFrame(currentFrame);
//    outputLayer.opacity = _opacityInterpolator->floatValueForFrame(currentFrame);
//    NSArray *numberArray = _gradientInterpolator->numberArrayForFrame(currentFrame);
//    NSMutableArray *colorArray = [NSMutableArray array];
//    NSMutableArray *locationsArray = [NSMutableArray array];

//    NSMutableArray *opacityArray = [NSMutableArray array];
//    NSMutableArray *opacitylocationsArray = [NSMutableArray array];
//    for (int i = 0; i < _numberOfPositions; i++) {
//      int ix = i * 4;
//      NSNumber *location = numberArray[ix];
//      NSNumber *r = numberArray[(ix + 1)];
//      NSNumber *g = numberArray[(ix + 2)];
//      NSNumber *b = numberArray[(ix + 3)];
//      [locationsArray addObject:location];
//      UIColor *color = [UIColor colorWithRed:r.floatValue green:g.floatValue blue:b.floatValue alpha:1];
//      [colorArray addObject:(id)(color.CGColor)];
//    }
//    for (NSInteger i = (_numberOfPositions * 4); i < numberArray.count; i = i + 2) {
//      NSNumber *opacityLocation = numberArray[i];
//      [opacitylocationsArray addObject:opacityLocation];
//      NSNumber *opacity = numberArray[i + 1];
//      UIColor *opacityColor = [UIColor colorWithWhite:1 alpha:opacity.floatValue];
//      [opacityArray addObject:(id)(opacityColor.CGColor)];
//    }
//    if (opacityArray.count == 0) {
//      _gradientOpacityLayer.backgroundColor = [UIColor whiteColor].CGColor;
//    } else {
//      _gradientOpacityLayer.startPoint = _startPoint;
//      _gradientOpacityLayer.endPoint = _endPoint;
//      _gradientOpacityLayer.locations = opacitylocationsArray;
//      _gradientOpacityLayer.colors = opacityArray;
//    }
//    _gradientLayer.startPoint = _startPoint;
//    _gradientLayer.endPoint = _endPoint;
//    _gradientLayer.locations = locationsArray;
//    _gradientLayer.colors = colorArray;
}

void LOTGradientFillRender::rebuildOutputs()
{
    QRectF frame = inputNode->outputPath()->bounds();
    QPointF modifiedAnchor = QPointF(-frame.x() / frame.width(),
                                     -frame.y() / frame.height());
//    _maskShape.path = inputNode->outputPath()->CGPath();
    Q_ASSERT(false);
//    _gradientOpacityLayer->bounds = frame;
//    _gradientOpacityLayer->anchorPoint = modifiedAnchor;

//    _gradientLayer.bounds = frame.toCGRect();
//    _gradientLayer.anchorPoint = modifiedAnchor;
}
