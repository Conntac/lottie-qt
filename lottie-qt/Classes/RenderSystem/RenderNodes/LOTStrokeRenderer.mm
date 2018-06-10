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

LOTStrokeRenderer::LOTStrokeRenderer(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeStroke *stroke)
: LOTRenderNode(inputNode, stroke.keyname)
{
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
      Q_ASSERT(false);
//    outputLayer.lineDashPattern = dashPatterns;
  } else {
    _dashPatternInterpolators = dashPatternIntpolators;
  }

  if (stroke.dashOffset) {
    _dashOffsetInterpolator = _dashOffsetInterpolator.create(stroke.dashOffset.keyframes);
  }

  // TODO: This might be a nil color?
  outputLayer->setFillColor(QColor(Qt::transparent));
  outputLayer->setCapStyle(stroke.capType == LOTLineCapTypeRound ? QQuickShapePath::RoundCap : QQuickShapePath::FlatCap);
  switch (stroke.joinType) {
    case LOTLineJoinTypeBevel:
      outputLayer->setJoinStyle(QQuickShapePath::BevelJoin);
      break;
    case LOTLineJoinTypeMiter:
      outputLayer->setJoinStyle(QQuickShapePath::MiterJoin);
      break;
    case LOTLineJoinTypeRound:
      outputLayer->setJoinStyle(QQuickShapePath::RoundJoin);
      break;
    default:
      break;
  }
}

NSDictionary *LOTStrokeRenderer::actionsForRenderLayer() const
{
    return @{@"strokeColor": [NSNull null],
             @"lineWidth": [NSNull null],
             @"opacity" : [NSNull null]};
}

QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTStrokeRenderer::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Color", _colorInterpolator);
    map.insert("Opacity", _opacityInterpolator);
    map.insert("Stroke Width", _widthInterpolator);
    return map;
}

bool LOTStrokeRenderer::needsUpdateForFrame(qreal frame)
{
    _updateLineDashPatternsForFrame(frame);
    BOOL dashOffset = NO;
    if (_dashOffsetInterpolator) {
      dashOffset = _dashOffsetInterpolator->hasUpdateForFrame(frame);
    }
    return (dashOffset ||
            _colorInterpolator->hasUpdateForFrame(frame) ||
            _opacityInterpolator->hasUpdateForFrame(frame) ||
            _widthInterpolator->hasUpdateForFrame(frame));
}

void LOTStrokeRenderer::performLocalUpdate()
{
    outputLayer->lineDashPhase = _dashOffsetInterpolator ? _dashOffsetInterpolator->floatValueForFrame(currentFrame) : 0.0f;
    outputLayer->setStrokeColor(_colorInterpolator->colorForFrame(currentFrame));
    outputLayer->setStrokeWidth(_widthInterpolator->floatValueForFrame(currentFrame));
    outputLayer->setOpacity(_opacityInterpolator->floatValueForFrame(currentFrame));
}

void LOTStrokeRenderer::rebuildOutputs()
{
    if (inputNode->outputPath()) {
        outputLayer->setPainterPath(inputNode->outputPath()->CGPath());
    }
}

void LOTStrokeRenderer::_updateLineDashPatternsForFrame(qreal frame)
{
  if (_dashPatternInterpolators.size()) {
    QVector<qreal> lineDashPatterns;
    qreal dashTotal = 0;
    for (auto interpolator : _dashPatternInterpolators) {
      qreal patternValue = interpolator->floatValueForFrame(frame);
      dashTotal = dashTotal + patternValue;
      lineDashPatterns.append(patternValue);
    }
    if (dashTotal > 0) {
      outputLayer->setDashPattern(lineDashPatterns);
    }
  }
}
