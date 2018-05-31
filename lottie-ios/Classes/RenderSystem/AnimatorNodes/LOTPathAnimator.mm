//
//  LOTPathAnimator.m
//  Pods
//
//  Created by brandon_withrow on 6/27/17.
//
//

#import "LOTPathAnimator.h"
#import "LOTPathInterpolator.h"

#include <QSharedPointer>

@implementation LOTPathAnimator {
  LOTShapePath *_pathConent;
  QSharedPointer<LOTPathInterpolator> _interpolator;
}

- (instancetype _Nonnull)initWithInputNode:(LOTAnimatorNode *_Nullable)inputNode
                                  shapePath:(LOTShapePath *_Nonnull)shapePath {
  self = [super initWithInputNode:inputNode keyName:shapePath.keyname];
  if (self) {
    _pathConent = shapePath;
    _interpolator = _interpolator.create(_pathConent.shapePath.keyframes);
  }
  return self;
}

- (QMap<QString, QSharedPointer<LOTValueInterpolator>>)valueInterpolators {
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Path", _interpolator);
    return map;
}

- (BOOL)needsUpdateForFrame:(NSNumber *)frame {
  return _interpolator->hasUpdateForFrame(frame.floatValue);
}

- (void)performLocalUpdate {
  self.localPath = _interpolator->pathForFrame(self.currentFrame.floatValue, self.pathShouldCacheLengths);
}

@end
