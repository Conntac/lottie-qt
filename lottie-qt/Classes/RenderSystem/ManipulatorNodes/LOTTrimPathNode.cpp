//
//  LOTTrimPathNode.m
//  Lottie
//
//  Created by brandon_withrow on 7/21/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTTrimPathNode.h"
#include "LOTNumberInterpolator.h"
#include "LOTPathAnimator.h"
#include "LOTCircleAnimator.h"
#include "LOTRoundedRectAnimator.h"
#include "LOTRenderGroup.h"

#include <QSharedPointer>

LOTTrimPathNode::LOTTrimPathNode(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeTrimPath *trimPath)
: LOTAnimatorNode(inputNode, trimPath->keyname)
{
    inputNode->setPathShouldCacheLengths(true);
    _startInterpolator = _startInterpolator.create(trimPath->start->keyframes);
    _endInterpolator = _endInterpolator.create(trimPath->end->keyframes);
    _offsetInterpolator = _offsetInterpolator.create(trimPath->offset->keyframes);
}


QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTTrimPathNode::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Start", _startInterpolator);
    map.insert("End", _endInterpolator);
    map.insert("Offset", _offsetInterpolator);
    return map;
}

QSharedPointer<LOTBezierPath> LOTTrimPathNode::localPath() const
{
    return inputNode->localPath();
}

/// Forwards its input node's output path forwards downstream
QSharedPointer<LOTBezierPath> LOTTrimPathNode::outputPath() const
{
    return inputNode->outputPath();
}

bool LOTTrimPathNode::needsUpdateForFrame(qreal frame)
{
    return (_startInterpolator->hasUpdateForFrame(frame) ||
            _endInterpolator->hasUpdateForFrame(frame) ||
            _offsetInterpolator->hasUpdateForFrame(frame));
}

bool LOTTrimPathNode::updateWithFrame(qreal frame, std::function<void(LOTAnimatorNode *inputNode)> modifier, bool forceUpdate)
{
    bool localUpdate = needsUpdateForFrame(frame);
    forceSetCurrentFrame(frame);
    if (localUpdate) {
      performLocalUpdate();
    }
    if (inputNode == nullptr) {
      return localUpdate;
    }

    bool inputUpdated = inputNode->updateWithFrame(frame, [=](LOTAnimatorNode *inputNode) {
      if (dynamic_cast<LOTPathAnimator *>(inputNode) ||
          dynamic_cast<LOTCircleAnimator *>(inputNode) ||
          dynamic_cast<LOTRoundedRectAnimator *>(inputNode)) {
        inputNode->localPath()->trimPathFromT(_startT, _endT, _offsetT);
      }
      if (modifier) {
        modifier(inputNode);
      }

    }, (localUpdate || forceUpdate));

    return inputUpdated;
}

void LOTTrimPathNode::performLocalUpdate()
{
    _startT = _startInterpolator->floatValueForFrame(currentFrame) / 100;
    _endT = _endInterpolator->floatValueForFrame(currentFrame) / 100;
    _offsetT = _offsetInterpolator->floatValueForFrame(currentFrame) / 360;
}

void LOTTrimPathNode::rebuildOutputs()
{
    // Skip this step.
}
