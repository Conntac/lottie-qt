//
//  LOTRenderGroup.h
//  Lottie
//
//  Created by brandon_withrow on 6/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTRenderNode.h"

class LOTNumberInterpolator;
class LOTTransformInterpolator;

class LOTRenderGroup : public LOTRenderNode
{
public:
    explicit LOTRenderGroup(const QSharedPointer<LOTAnimatorNode> &inputNode, NSArray * _Nonnull contents, NSString *_Nullable keyname);

//@property (nonatomic, strong, readonly)
    CALayer * _Nonnull containerLayer;

    // LOTAnimatorNode interface
    QMap<QString, QSharedPointer<LOTValueInterpolator>> valueInterpolators() const override;
    LOTBezierPath *localPath() const override;
    LOTBezierPath *outputPath() const override;
    bool needsUpdateForFrame(qreal frame) override;
    bool updateWithFrame(qreal frame, std::function<void (LOTAnimatorNode *)> modifier, bool forceUpdate) override;
    void setPathShouldCacheLengths(bool pathShouldCacheLengths) override;
    void performLocalUpdate() override;
    void rebuildOutputs() override;
    void searchNodesForKeypath(LOTKeypath *keypath) override;
    void setValueDelegate(id<LOTValueDelegate> delegate, LOTKeypath *keypath) override;

private:
    void buildContents(NSArray *contents);

    QSharedPointer<LOTAnimatorNode> _rootNode;
    LOTBezierPath *_outputPath;
    LOTBezierPath *_localPath;
    BOOL _rootNodeHasUpdate;
    QSharedPointer<LOTNumberInterpolator> _opacityInterpolator;
    QSharedPointer<LOTTransformInterpolator> _transformInterolator;
};
