//
//  LOTStrokeRenderer.h
//  Lottie
//
//  Created by brandon_withrow on 7/17/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTRenderNode.h"
#import "LOTShapeStroke.h"

class LOTColorInterpolator;
class LOTNumberInterpolator;

class LOTStrokeRenderer : public LOTRenderNode
{
public:
    explicit LOTStrokeRenderer(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeStroke *_Nonnull stroke);

    // LOTRenderNode interface
//    NSDictionary *actionsForRenderLayer() const override;

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;
    void rebuildOutputs() override;

private:
    void _updateLineDashPatternsForFrame(qreal frame);

    QSharedPointer<LOTColorInterpolator> _colorInterpolator;
    QSharedPointer<LOTNumberInterpolator> _opacityInterpolator;
    QSharedPointer<LOTNumberInterpolator> _widthInterpolator;
    QSharedPointer<LOTNumberInterpolator> _dashOffsetInterpolator;
    QList<QSharedPointer<LOTNumberInterpolator>> _dashPatternInterpolators;
};
