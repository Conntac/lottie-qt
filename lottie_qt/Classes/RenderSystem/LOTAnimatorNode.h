//
//  LOTAnimatorNode.h
//  Pods
//
//  Created by brandon_withrow on 6/27/17.
//
//

#pragma once

#include "LOTBezierPath.h"
#include "LOTKeypath.h"
#include "LOTValueDelegate.h"

#include <QMap>
#include <QSharedPointer>
#include <functional>

class LOTValueInterpolator;

extern int indentation_level;

class LOTAnimatorNode : public LOTBase
{
public:
    /// Initializes the node with and optional input node and keyname.
    explicit LOTAnimatorNode(const QSharedPointer<LOTAnimatorNode> &inputNode, const QString &keyname);
    virtual ~LOTAnimatorNode();

    /// A dictionary of the value interpolators this node controls
//@property (nonatomic, readonly)
    virtual QMap<QString, QSharedPointer<LOTValueInterpolator>> valueInterpolators() const = 0;

    /// The keyname of the node. Used for dynamically setting keyframe data.
//@property (nonatomic, readonly, strong)
    QString keyname;

    /// The current time in frames
//@property (nonatomic, readonly, strong)
    qreal currentFrame = 0.0;
    /// The upstream animator node
//@property (nonatomic, readonly, strong)
    QSharedPointer<LOTAnimatorNode> inputNode;

    /// This nodes path in local object space
//@property (nonatomic, strong)
    void setLocalPath(QSharedPointer<LOTBezierPath> localPath);
    virtual QSharedPointer<LOTBezierPath> localPath() const;
    /// The sum of all paths in the tree including this node
//@property (nonatomic, strong)
    virtual QSharedPointer<LOTBezierPath> outputPath() const;

    /// Returns true if this node needs to update its contents for the given frame. To be overwritten by subclasses.
    virtual bool needsUpdateForFrame(qreal frame);

    /// Sets the current frame and performs any updates. Returns true if any updates were performed, locally or upstream.
    bool updateWithFrame(qreal frame);
    virtual bool updateWithFrame(qreal frame, std::function<void(LOTAnimatorNode *inputNode)> modifier, bool forceUpdate);

    void forceSetCurrentFrame(qreal frame);

//@property (nonatomic, assign)
    virtual void setPathShouldCacheLengths(bool pathShouldCacheLengths);
    bool pathShouldCacheLengths() const;

    /// Update the local content for the frame.
    virtual void performLocalUpdate();

    /// Rebuild all outputs for the node. This is called after upstream updates have been performed.
    virtual void rebuildOutputs();

    void logString(const QString &string);

    virtual void searchNodesForKeypath(LOTKeypath *keypath);

    virtual void setValueDelegate(LOTValueDelegate *delegate,
                                  LOTKeypath *keypath);

private:
    QSharedPointer<LOTBezierPath> _localPath;
    QSharedPointer<LOTBezierPath> _outputPath;
    bool _pathShouldCacheLengths = false;
};
