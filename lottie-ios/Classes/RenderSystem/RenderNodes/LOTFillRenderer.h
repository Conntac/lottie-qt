//
//  LOTFillRenderer.h
//  Lottie
//
//  Created by brandon_withrow on 6/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTRenderNode.h"
#import "LOTShapeFill.h"

class LOTColorInterpolator;
class LOTNumberInterpolator;

class LOTFillRenderer : public LOTRenderNode
{
public:
    explicit LOTFillRenderer(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeFill *_Nonnull fill);

    // LOTRenderNode interface
    NSDictionary *actionsForRenderLayer() const override;

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    bool needsUpdateForFrame(qreal frame) override;
    void performLocalUpdate() override;
    void rebuildOutputs() override;

private:
    QSharedPointer<LOTColorInterpolator> colorInterpolator_;
    QSharedPointer<LOTNumberInterpolator> opacityInterpolator_;
    BOOL _evenOddFillRule;
    QSharedPointer<QQuickLottieLayer> centerPoint_DEBUG;
};
