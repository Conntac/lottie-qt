//
//  LOTAnimatorNode.m
//  Pods
//
//  Created by brandon_withrow on 6/27/17.
//
//

#import "LOTAnimatorNode.h"
#import "LOTHelpers.h"
#import "LOTValueInterpolator.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logAnimatorNode, "lottie.animator_node")

NSInteger indentation_level = 0;

LOTAnimatorNode::LOTAnimatorNode(const QSharedPointer<LOTAnimatorNode> &inputNode, const QString &keyname)
: inputNode(inputNode)
, keyname(keyname)
{
}

LOTAnimatorNode::~LOTAnimatorNode()
{
}

void LOTAnimatorNode::setLocalPath(QSharedPointer<LOTBezierPath> localPath)
{
    _localPath = localPath;
}

QSharedPointer<LOTBezierPath> LOTAnimatorNode::localPath() const
{
    return _localPath;
}

QSharedPointer<LOTBezierPath> LOTAnimatorNode::outputPath() const
{
    return _outputPath;
}

/// To be overwritten by subclass. Defaults to YES
bool LOTAnimatorNode::needsUpdateForFrame(qreal frame)
{
    return true;
}

/// The node checks if local update or if upstream update required. If upstream update outputs are rebuilt. If local update local update is performed. Returns no if no action
bool LOTAnimatorNode::updateWithFrame(qreal frame)
{
    return updateWithFrame(frame, nullptr, false);
}

bool LOTAnimatorNode::updateWithFrame(qreal frame, std::function<void(LOTAnimatorNode * _Nonnull inputNode)> modifier, bool forceUpdate)
{
    if (currentFrame == frame && !forceUpdate) {
      return NO;
    }
    if (ENABLE_DEBUG_LOGGING) qCDebug(logAnimatorNode) << (quint64)this << keyname << "Checking for update";
    BOOL localUpdate = needsUpdateForFrame(frame) || forceUpdate;
    if (localUpdate && ENABLE_DEBUG_LOGGING) {
      logString([NSString stringWithFormat:@"%lu %@ Performing update", (unsigned long)this, keyname.toNSString()]);
    }
    bool inputUpdated = inputNode ? inputNode->updateWithFrame(frame, modifier, forceUpdate) : false;
    currentFrame = frame;
    if (localUpdate) {
      performLocalUpdate();
      if (modifier) {
        modifier(this);
      }
    }

    if (inputUpdated || localUpdate) {
      rebuildOutputs();
    }
    return (inputUpdated || localUpdate);
}

void LOTAnimatorNode::forceSetCurrentFrame(qreal frame)
{
    currentFrame = frame;
}

void LOTAnimatorNode::setPathShouldCacheLengths(bool pathShouldCacheLengths)
{
    _pathShouldCacheLengths = pathShouldCacheLengths;
    if (inputNode) {
        inputNode->setPathShouldCacheLengths(pathShouldCacheLengths);
    }
}

bool LOTAnimatorNode::pathShouldCacheLengths() const
{
    return _pathShouldCacheLengths;
}

// TOBO BW Perf, make updates perform only when necessary. Currently everything in a node is updated
/// Performs any local content update and updates self.localPath
void LOTAnimatorNode::performLocalUpdate()
{
    _localPath = _localPath.create();
}

/// Rebuilds outputs by adding localPath to inputNodes output path.
void LOTAnimatorNode::rebuildOutputs()
{
    if (inputNode) {
      _outputPath = inputNode->outputPath()->copy();
      _outputPath->LOT_appendPath(localPath());
    } else {
      _outputPath = localPath();
    }
}

void LOTAnimatorNode::logString(NSString *string)
{
    qCDebug(logAnimatorNode) << "|" << QString(indentation_level*2, QLatin1Char(' ')) << QString::fromNSString(string);
}

void LOTAnimatorNode::searchNodesForKeypath(LOTKeypath *keypath)
{
    inputNode->searchNodesForKeypath(keypath);
    if (keypath->pushKey(keyname)) {
      // Matches self. Check interpolators
      if (keypath->endOfKeypath()) {
        // Add self
//        [keypath addSearchResultForCurrentPath:this];
      } else if (valueInterpolators()[keypath->currentKey()]) {
        keypath->pushKey(keypath->currentKey());
        // We have a match!
//        [keypath addSearchResultForCurrentPath:this];
        keypath->popKey();
      }
      keypath->popKey();
    }
}

void LOTAnimatorNode::setValueDelegate(id<LOTValueDelegate> delegate, LOTKeypath *keypath)
{
    if (keypath->pushKey(keyname)) {
      // Matches self. Check interpolators
      QSharedPointer<LOTValueInterpolator> interpolator = valueInterpolators()[keypath->currentKey()];
      if (interpolator) {
        // We have a match!
        interpolator->setValueDelegate(delegate);
      }
      keypath->popKey();
    }
    inputNode->setValueDelegate(delegate, keypath);
}
