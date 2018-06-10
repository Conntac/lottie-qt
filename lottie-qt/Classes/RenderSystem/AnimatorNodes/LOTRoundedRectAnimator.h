//
//  LOTRoundedRectAnimator.h
//  Lottie
//
//  Created by brandon_withrow on 7/19/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTAnimatorNode.h"
#import "LOTShapeRectangle.h"

class LOTPointInterpolator;
class LOTNumberInterpolator;

class LOTRoundedRectAnimator : public LOTAnimatorNode
{
public:
    explicit LOTRoundedRectAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode,
                                    LOTShapeRectangle *_Nonnull shapeRectangle);

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;

private:
    QSharedPointer<LOTPointInterpolator> _centerInterpolator;
    QSharedPointer<LOTPointInterpolator> _sizeInterpolator;
    QSharedPointer<LOTNumberInterpolator> _cornerRadiusInterpolator;
    bool _reversed;
};
