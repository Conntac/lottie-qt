//
//  LOTPolygonAnimator.h
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include "LOTAnimatorNode.h"
#include "LOTShapeStar.h"

class LOTNumberInterpolator;
class LOTPointInterpolator;

class LOTPolygonAnimator : public LOTAnimatorNode
{
public:
    explicit LOTPolygonAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode,
                                LOTShapeStar *shapeStar);

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;

private:
    QSharedPointer<LOTNumberInterpolator> _outerRadiusInterpolator;
    QSharedPointer<LOTNumberInterpolator> _outerRoundnessInterpolator;
    QSharedPointer<LOTPointInterpolator> _positionInterpolator;
    QSharedPointer<LOTNumberInterpolator> _pointsInterpolator;
    QSharedPointer<LOTNumberInterpolator> _rotationInterpolator;
};


