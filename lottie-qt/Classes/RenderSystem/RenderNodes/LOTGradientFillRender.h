//
//  LOTGradientFillRender.h
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTRenderNode.h"
#import "LOTShapeGradientFill.h"
#import "LOTRadialGradientLayer.h"

class LOTArrayInterpolator;
class LOTPointInterpolator;
class LOTNumberInterpolator;

class LOTGradientFillRender : public LOTRenderNode
{
public:
    explicit LOTGradientFillRender(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeGradientFill *fill);

    // LOTRenderNode interface
//    NSDictionary *actionsForRenderLayer() const override;

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;
    void rebuildOutputs() override;

private:
    bool _evenOddFillRule;
    QSharedPointer<QQuickLottieLayer> centerPoint_DEBUG;

    QSharedPointer<QQuickLottieLayer> _maskShape;
//    QSharedPointer<LOTRadialGradientLayer> _gradientOpacityLayer;
//    QSharedPointer<LOTRadialGradientLayer> _gradientLayer;
    int _numberOfPositions;

    QPointF _startPoint;
    QPointF _endPoint;

    QSharedPointer<LOTArrayInterpolator> _gradientInterpolator;
    QSharedPointer<LOTPointInterpolator> _startPointInterpolator;
    QSharedPointer<LOTPointInterpolator> _endPointInterpolator;
    QSharedPointer<LOTNumberInterpolator> _opacityInterpolator;
};

