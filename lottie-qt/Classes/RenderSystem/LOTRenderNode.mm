//
//  LOTRenderNode.m
//  Pods
//
//  Created by brandon_withrow on 6/27/17.
//
//

#import "LOTRenderNode.h"

LOTRenderNode::LOTRenderNode(const QSharedPointer<LOTAnimatorNode> &inputNode, const QString &keyname)
: LOTAnimatorNode(inputNode, keyname)
{
//    outputLayer = [CAShapeLayer new];
    outputLayer = outputLayer.create();
    // TODO: Comment me in and don't use virtuals
//    outputLayer.actions = actionsForRenderLayer();
}

/// Layer Properties that need to disable implicit animations
//NSDictionary * _Nonnull LOTRenderNode::actionsForRenderLayer() const
//{
//    return @{@"path": [NSNull null]};
//}

QSharedPointer<LOTBezierPath> LOTRenderNode::localPath() const
{
    return inputNode->localPath();
}

/// Forwards its input node's output path forwards downstream
QSharedPointer<LOTBezierPath> LOTRenderNode::outputPath() const
{
    return inputNode->outputPath();
}

/// Local interpolators have changed. Update layer specific properties.
void LOTRenderNode::performLocalUpdate()
{
}

/// The path for rendering has changed. Do any rendering required.
void LOTRenderNode::rebuildOutputs()
{
}
