//
//  LOTPolystarAnimator.h
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTAnimatorNode.h"
#import "LOTShapeStar.h"

class LOTNumberInterpolator;
class LOTPointInterpolator;

class LOTPolystarAnimator : public LOTAnimatorNode
{
public:
    explicit LOTPolystarAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode,
                                 LOTShapeStar *_Nonnull shapeStar);

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;

private:
    QSharedPointer<LOTNumberInterpolator> _outerRadiusInterpolator;
    QSharedPointer<LOTNumberInterpolator> _innerRadiusInterpolator;
    QSharedPointer<LOTNumberInterpolator> _outerRoundnessInterpolator;
    QSharedPointer<LOTNumberInterpolator> _innerRoundnessInterpolator;
    QSharedPointer<LOTPointInterpolator> _positionInterpolator;
    QSharedPointer<LOTNumberInterpolator> _pointsInterpolator;
    QSharedPointer<LOTNumberInterpolator> _rotationInterpolator;
};
