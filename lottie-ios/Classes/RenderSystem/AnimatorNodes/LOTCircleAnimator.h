//
//  LOTCircleAnimator.h
//  Lottie
//
//  Created by brandon_withrow on 7/19/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTAnimatorNode.h"
#import "LOTShapeCircle.h"
#import "LOTPointInterpolator.h"

class LOTCircleAnimator : public LOTAnimatorNode
{
public:
    explicit LOTCircleAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode,
                               LOTShapeCircle *_Nonnull shapeCircle);

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;

private:
    QSharedPointer<LOTPointInterpolator> _centerInterpolator;
    QSharedPointer<LOTPointInterpolator> _sizeInterpolator;
    BOOL _reversed;
};
