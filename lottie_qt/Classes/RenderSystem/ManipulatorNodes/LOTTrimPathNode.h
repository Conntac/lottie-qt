//
//  LOTTrimPathNode.h
//  Lottie
//
//  Created by brandon_withrow on 7/21/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTAnimatorNode.h"
#include "LOTShapeTrimPath.h"

class LOTNumberInterpolator;

class LOTTrimPathNode : public LOTAnimatorNode
{
public:
    explicit LOTTrimPathNode(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeTrimPath *trimPath);

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    QSharedPointer<LOTBezierPath> localPath() const override;
    QSharedPointer<LOTBezierPath> outputPath() const override;
    bool needsUpdateForFrame(qreal frame) override;
    bool updateWithFrame(qreal frame, std::function<void(LOTAnimatorNode *inputNode)> modifier, bool forceUpdate) override;
    void performLocalUpdate() override;
    void rebuildOutputs() override;

private:
    QSharedPointer<LOTNumberInterpolator> _startInterpolator;
    QSharedPointer<LOTNumberInterpolator> _endInterpolator;
    QSharedPointer<LOTNumberInterpolator> _offsetInterpolator;

    qreal _startT = 0.0;
    qreal _endT = 0.0;
    qreal _offsetT = 0.0;
};
