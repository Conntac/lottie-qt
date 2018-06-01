//
//  LOTTrimPathNode.h
//  Lottie
//
//  Created by brandon_withrow on 7/21/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTAnimatorNode.h"
#import "LOTShapeTrimPath.h"

class LOTNumberInterpolator;

class LOTTrimPathNode : public LOTAnimatorNode
{
public:
    explicit LOTTrimPathNode(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapeTrimPath *_Nonnull trimPath);

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator> > valueInterpolators() const override;
    LOTBezierPath *localPath() const override;
    LOTBezierPath *outputPath() const override;
    bool needsUpdateForFrame(qreal frame) override;
    bool updateWithFrame(qreal frame, std::function<void(LOTAnimatorNode * _Nonnull inputNode)> modifier, bool forceUpdate) override;
    void performLocalUpdate() override;
    void rebuildOutputs() override;

private:
    QSharedPointer<LOTNumberInterpolator> _startInterpolator;
    QSharedPointer<LOTNumberInterpolator> _endInterpolator;
    QSharedPointer<LOTNumberInterpolator> _offsetInterpolator;

    CGFloat _startT;
    CGFloat _endT;
    CGFloat _offsetT;
};
