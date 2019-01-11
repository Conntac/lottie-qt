//
//  LOTRepeaterRenderer.m
//  Lottie
//
//  Created by brandon_withrow on 7/28/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTRepeaterRenderer.h"
#include "LOTTransformInterpolator.h"
#include "LOTNumberInterpolator.h"
#include "LOTHelpers.h"

#include <QSharedPointer>
#include <QtMath>

LOTRepeaterRenderer::LOTRepeaterRenderer(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeRepeater *repeater)
: LOTRenderNode(inputNode, repeater->keyname)
{
    _transformInterpolator = _transformInterpolator.create(repeater->position->keyframes,
                                                           repeater->rotation->keyframes,
                                                           repeater->anchorPoint->keyframes,
                                                           repeater->scale->keyframes);
    _copiesInterpolator = _copiesInterpolator.create(repeater->copies->keyframes);
    _offsetInterpolator = _offsetInterpolator.create(repeater->offset->keyframes);
    _startOpacityInterpolator = _startOpacityInterpolator.create(repeater->startOpacity->keyframes);
    _endOpacityInterpolator = _endOpacityInterpolator.create(repeater->endOpacity->keyframes);

    _instanceLayer = _instanceLayer.create();
    recursivelyAddChildLayers(inputNode);

    _replicatorLayer = _replicatorLayer.create();
    _replicatorLayer->actions = {{"instanceCount", QVariantMap()},
                                 {"instanceTransform", QVariantMap()},
                                 {"instanceAlphaOffset", QVariantMap()}};
    _replicatorLayer->addSublayer(_instanceLayer);
    outputLayer->addSublayer(_replicatorLayer);

    centerPoint_DEBUG = centerPoint_DEBUG.create();
    centerPoint_DEBUG->bounds = QRectF(0, 0, 20, 20);
    if (ENABLE_DEBUG_SHAPES) {
      outputLayer->addSublayer(centerPoint_DEBUG);
    }
}


QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTRepeaterRenderer::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Copies", _copiesInterpolator);
    map.insert("Offset", _offsetInterpolator);
    map.insert("Transform.Anchor Point", _transformInterpolator->anchorInterpolator);
    map.insert("Transform.Position", _transformInterpolator->positionInterpolator);
    map.insert("Transform.Scale", _transformInterpolator->scaleInterpolator);
    map.insert("Transform.Rotation", _transformInterpolator->rotationInterpolator);
    map.insert("Transform.Start Opacity", _startOpacityInterpolator);
    map.insert("Transform.End Opacity", _endOpacityInterpolator);
    return map;
}

bool LOTRepeaterRenderer::needsUpdateForFrame(qreal frame)
{
    // TODO BW Add offset ability
    return (_transformInterpolator->hasUpdateForFrame(frame) ||
            _copiesInterpolator->hasUpdateForFrame(frame) ||
            _startOpacityInterpolator->hasUpdateForFrame(frame) ||
            _endOpacityInterpolator->hasUpdateForFrame(frame));
}

void LOTRepeaterRenderer::performLocalUpdate()
{
    centerPoint_DEBUG->backgroundColor = QColor(Qt::green);
    centerPoint_DEBUG->borderColor = QColor(Qt::lightGray);
    centerPoint_DEBUG->borderWidth = 2.f;

    qreal copies = ceilf(_copiesInterpolator->floatValueForFrame(currentFrame));
    _replicatorLayer->instanceCount = (int)copies;
    _replicatorLayer->instanceTransform = _transformInterpolator->transformForFrame(currentFrame);
    qreal startOpacity = _startOpacityInterpolator->floatValueForFrame(currentFrame);
    qreal endOpacity = _endOpacityInterpolator->floatValueForFrame(currentFrame);
    qreal opacityStep = (endOpacity - startOpacity) / copies;
    _instanceLayer->setOpacity(startOpacity);
    _replicatorLayer->instanceAlphaOffset = opacityStep;
}

void LOTRepeaterRenderer::recursivelyAddChildLayers(const QSharedPointer<LOTAnimatorNode> &node)
{
    QSharedPointer<LOTRenderNode> renderNode = node.dynamicCast<LOTRenderNode>();
    if (renderNode) {
      _instanceLayer->addSublayer(renderNode->outputLayer);
    }
    if (!node.dynamicCast<LOTRepeaterRenderer>() &&
        node->inputNode) {
      recursivelyAddChildLayers(node->inputNode);
    }
}
