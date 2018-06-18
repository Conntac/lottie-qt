//
//  LOTFillRenderer.m
//  Lottie
//
//  Created by brandon_withrow on 6/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTFillRenderer.h"
#include "LOTColorInterpolator.h"
#include "LOTNumberInterpolator.h"
#include "LOTHelpers.h"

#include <QSharedPointer>

LOTFillRenderer::LOTFillRenderer(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeFill *fill)
: LOTRenderNode(inputNode, fill->keyname)
{
    colorInterpolator_ = colorInterpolator_.create(fill->color->keyframes);
    opacityInterpolator_ = opacityInterpolator_.create(fill->opacity->keyframes);
    centerPoint_DEBUG = centerPoint_DEBUG.create();
    centerPoint_DEBUG->bounds = QRectF(0, 0, 20, 20);
    if (ENABLE_DEBUG_SHAPES) {
        outputLayer->addSublayer(centerPoint_DEBUG);
    }
    _evenOddFillRule = fill->evenOddFillRule;

    outputLayer->setFillRule(_evenOddFillRule ? Qt::OddEvenFill : Qt::WindingFill);
}

//NSDictionary *LOTFillRenderer::actionsForRenderLayer() const
//{
//    return @{@"backgroundColor": [NSNull null],
//             @"fillColor": [NSNull null],
//             @"opacity" : [NSNull null]};
//}

QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTFillRenderer::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Color", colorInterpolator_);
    map.insert("Opacity", opacityInterpolator_);
    return map;
}

bool LOTFillRenderer::needsUpdateForFrame(qreal frame)
{
    return colorInterpolator_->hasUpdateForFrame(frame) || opacityInterpolator_->hasUpdateForFrame(frame);
}

void LOTFillRenderer::performLocalUpdate()
{
    centerPoint_DEBUG->backgroundColor =  colorInterpolator_->colorForFrame(currentFrame);
    centerPoint_DEBUG->borderColor = QColor(Qt::lightGray);
    centerPoint_DEBUG->borderWidth = 2.f;
    outputLayer->setFillColor(colorInterpolator_->colorForFrame(currentFrame));
    outputLayer->setOpacity(opacityInterpolator_->floatValueForFrame(currentFrame));
}

void LOTFillRenderer::rebuildOutputs()
{
    outputLayer->setPath(inputNode->outputPath()->CGPath());
}
