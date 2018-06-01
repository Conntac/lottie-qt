//
//  LOTAnimatorNode.h
//  Pods
//
//  Created by brandon_withrow on 6/27/17.
//
//

#import <Foundation/Foundation.h>
#import "LOTPlatformCompat.h"
#import "LOTBezierPath.h"
#import "LOTKeypath.h"
#import "LOTValueDelegate.h"

#include <QMap>
#include <QSharedPointer>
#include <functional>

class LOTValueInterpolator;

extern NSInteger indentation_level;

class LOTAnimatorNode
{
public:
    /// Initializes the node with and optional input node and keyname.
    explicit LOTAnimatorNode(const QSharedPointer<LOTAnimatorNode> &inputNode, NSString *_Nullable keyname);
    virtual ~LOTAnimatorNode();

    /// A dictionary of the value interpolators this node controls
//@property (nonatomic, readonly)
    virtual QMap<QString, QSharedPointer<LOTValueInterpolator>> valueInterpolators() const = 0;

    /// The keyname of the node. Used for dynamically setting keyframe data.
//@property (nonatomic, readonly, strong)
    NSString * _Nullable keyname = nil;

    /// The current time in frames
//@property (nonatomic, readonly, strong)
    qreal currentFrame = 0.0;
    /// The upstream animator node
//@property (nonatomic, readonly, strong)
    QSharedPointer<LOTAnimatorNode> inputNode;

    /// This nodes path in local object space
//@property (nonatomic, strong)
    void setLocalPath(LOTBezierPath *localPath);
    virtual LOTBezierPath * _Nonnull localPath() const;
    /// The sum of all paths in the tree including this node
//@property (nonatomic, strong)
    virtual LOTBezierPath * _Nonnull outputPath() const;

    /// Returns true if this node needs to update its contents for the given frame. To be overwritten by subclasses.
    virtual bool needsUpdateForFrame(qreal frame);

    /// Sets the current frame and performs any updates. Returns true if any updates were performed, locally or upstream.
    bool updateWithFrame(qreal frame);
    virtual bool updateWithFrame(qreal frame, std::function<void(LOTAnimatorNode * _Nonnull inputNode)> modifier, bool forceUpdate);

    void forceSetCurrentFrame(qreal frame);

//@property (nonatomic, assign)
    virtual void setPathShouldCacheLengths(bool pathShouldCacheLengths);
    bool pathShouldCacheLengths() const;

    /// Update the local content for the frame.
    virtual void performLocalUpdate();

    /// Rebuild all outputs for the node. This is called after upstream updates have been performed.
    virtual void rebuildOutputs();

    void logString(NSString *_Nullable string);

    virtual void searchNodesForKeypath(LOTKeypath *_Nonnull keypath);

    virtual void setValueDelegate(id<LOTValueDelegate> _Nonnull delegate,
                                  LOTKeypath * _Nonnull keypath);

private:
    LOTBezierPath *_localPath = nil;
    LOTBezierPath *_outputPath = nil;
    bool _pathShouldCacheLengths = false;
};
