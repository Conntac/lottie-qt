//
//  LOTRenderNode.h
//  Pods
//
//  Created by brandon_withrow on 6/27/17.
//
//

#import "LOTAnimatorNode.h"

#include "qquicklottielayer.h"

class LOTRenderNode : public LOTAnimatorNode
{
public:
    explicit LOTRenderNode(const QSharedPointer<LOTAnimatorNode> &inputNode, NSString *_Nullable keyname);

//@property (nonatomic, readonly, strong)
//    CAShapeLayer * _Nonnull outputLayer;
    QSharedPointer<QQuickLottieLayer> outputLayer;

    virtual NSDictionary *actionsForRenderLayer() const;

    // LOTAnimatorNode interface
    QSharedPointer<LOTBezierPath> localPath() const override;
    QSharedPointer<LOTBezierPath> outputPath() const override;
    void performLocalUpdate() override;
    void rebuildOutputs() override;
};
