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

LOTFillRenderer::LOTFillRenderer(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeFill *fill)
: LOTRenderNode(inputNode, fill.keyname)
{
    colorInterpolator_ = colorInterpolator_.create(fill.color.keyframes);
    opacityInterpolator_ = opacityInterpolator_.create(fill.opacity.keyframes);
    centerPoint_DEBUG = [CALayer layer];
    centerPoint_DEBUG.bounds = CGRectMake(0, 0, 20, 20);
    if (ENABLE_DEBUG_SHAPES) {
        [outputLayer addSublayer:centerPoint_DEBUG];
    }
    _evenOddFillRule = fill.evenOddFillRule;

    outputLayer.fillRule = _evenOddFillRule ? @"even-odd" : @"non-zero";
}

NSDictionary *LOTFillRenderer::actionsForRenderLayer() const
{
    return @{@"backgroundColor": [NSNull null],
             @"fillColor": [NSNull null],
             @"opacity" : [NSNull null]};
}

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
    centerPoint_DEBUG.backgroundColor =  colorInterpolator_->colorForFrame(currentFrame);
    centerPoint_DEBUG.borderColor = [UIColor lightGrayColor].CGColor;
    centerPoint_DEBUG.borderWidth = 2.f;
    outputLayer.fillColor = colorInterpolator_->colorForFrame(currentFrame);
    outputLayer.opacity = opacityInterpolator_->floatValueForFrame(currentFrame);
}

void LOTFillRenderer::rebuildOutputs()
{
    outputLayer.path = inputNode->outputPath().CGPath;
}
