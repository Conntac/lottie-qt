//
//  LOTRepeaterRenderer.h
//  Lottie
//
//  Created by brandon_withrow on 7/28/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTRenderNode.h"
#include "LOTShapeRepeater.h"

class LOTTransformInterpolator;
class LOTNumberInterpolator;

class LOTRepeaterRenderer : public LOTRenderNode
{
public:
    explicit LOTRepeaterRenderer(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeRepeater *repeater);

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;

private:
    void recursivelyAddChildLayers(const QSharedPointer<LOTAnimatorNode> &node);

    QSharedPointer<LOTTransformInterpolator> _transformInterpolator;
    QSharedPointer<LOTNumberInterpolator> _copiesInterpolator;
    QSharedPointer<LOTNumberInterpolator> _offsetInterpolator;
    QSharedPointer<LOTNumberInterpolator> _startOpacityInterpolator;
    QSharedPointer<LOTNumberInterpolator> _endOpacityInterpolator;

    QSharedPointer<QQuickLottieLayer> _instanceLayer;
    QSharedPointer<QQuickLottieReplicatorLayer> _replicatorLayer;
    QSharedPointer<QQuickLottieLayer> centerPoint_DEBUG;
};
