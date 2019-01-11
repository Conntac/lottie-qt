//
//  LOTPathAnimator.h
//  Pods
//
//  Created by brandon_withrow on 6/27/17.
//
//

#pragma once

#include "LOTAnimatorNode.h"
#include "LOTShapePath.h"
#include "LOTPathInterpolator.h"

class LOTPathAnimator : public LOTAnimatorNode
{
public:
    explicit LOTPathAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode,
                             LOTShapePath *shapePath);

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;

private:
    LOTShapePath *_pathConent = nullptr;
    QSharedPointer<LOTPathInterpolator> _interpolator;
};
