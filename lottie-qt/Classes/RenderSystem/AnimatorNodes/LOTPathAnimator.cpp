//
//  LOTPathAnimator.m
//  Pods
//
//  Created by brandon_withrow on 6/27/17.
//
//

#include "LOTPathAnimator.h"

#include <QSharedPointer>

LOTPathAnimator::LOTPathAnimator(const QSharedPointer<LOTAnimatorNode> &inputNode, LOTShapePath *shapePath)
: LOTAnimatorNode(inputNode, shapePath->keyname)
{
    _pathConent = shapePath;
    _interpolator = _interpolator.create(_pathConent->shapePath->keyframes);
}

QMap<QString, QSharedPointer<LOTValueInterpolator> > LOTPathAnimator::valueInterpolators() const
{
    QMap<QString, QSharedPointer<LOTValueInterpolator>> map;
    map.insert("Path", _interpolator);
    return map;
}

bool LOTPathAnimator::needsUpdateForFrame(qreal frame)
{
    return _interpolator->hasUpdateForFrame(frame);
}

void LOTPathAnimator::performLocalUpdate()
{
    setLocalPath(_interpolator->pathForFrame(currentFrame, pathShouldCacheLengths()));
}
