//
//  LOTMaskContainer.m
//  Lottie
//
//  Created by brandon_withrow on 7/19/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTMaskContainer.h"
#include "LOTPathInterpolator.h"
#include "LOTNumberInterpolator.h"

class LOTMaskNodeLayer : public QQuickLottieShapeLayer
{
public:
    explicit LOTMaskNodeLayer(LOTMask *maskNode)
    {
        _pathInterpolator = _pathInterpolator.create(maskNode->maskPath->keyframes);
        _opacityInterpolator = _opacityInterpolator.create(maskNode->opacity->keyframes);
        _expansionInterpolator = _expansionInterpolator.create(maskNode->expansion->keyframes);
        this->maskNode = maskNode;
        setFillColor(QColor(Qt::blue));
    }

//    @property (nonatomic, readonly)
    LOTMask *maskNode;

    void updateForFrame(qreal frame, const QRectF &viewBounds)
    {
      if (hasUpdateForFrame(frame)) {
        QSharedPointer<LOTBezierPath> path = _pathInterpolator->pathForFrame(frame, false);

//        Q_ASSERT(false);
        if (maskNode->maskMode == LOTMaskModeSubtract) {
//          CGMutablePathRef pathRef = CGPathCreateMutable();
//          CGPathAddRect(pathRef, NULL, viewBounds.toCGRect());
//          CGPathAddPath(pathRef, NULL, path->CGPath());
//          path = pathRef;
          setFillRule(Qt::OddEvenFill);
//          CGPathRelease(pathRef);
        } else {
            setPath(path->CGPath());
        }

        qreal opacity = _opacityInterpolator->floatValueForFrame(frame);
        setOpacity(opacity);
      }
    }

    bool hasUpdateForFrame(qreal frame)
    {
      return (_pathInterpolator->hasUpdateForFrame(frame) ||
              _opacityInterpolator->hasUpdateForFrame(frame));
    }

private:
    QSharedPointer<LOTPathInterpolator> _pathInterpolator;
    QSharedPointer<LOTNumberInterpolator> _opacityInterpolator;
    QSharedPointer<LOTNumberInterpolator> _expansionInterpolator;
};

LOTMaskContainer::LOTMaskContainer(const QList<LOTMask *> &masks)
{
    QList<QSharedPointer<LOTMaskNodeLayer>> maskNodes;
    QSharedPointer<QQuickLottieLayer> containerLayer = containerLayer.create();;

    for (LOTMask *mask : masks) {
      QSharedPointer<LOTMaskNodeLayer> node = node.create(mask);
      maskNodes.append(node);
      if (mask->maskMode == LOTMaskModeAdd ||
          mask == masks.first()) {
        containerLayer->addSublayer(node);
      } else {
        containerLayer->mask = node;
        QSharedPointer<QQuickLottieLayer> newContainer = newContainer.create();
        newContainer->addSublayer(containerLayer);
        containerLayer = newContainer;
      }
    }
    addSublayer(containerLayer);
    _masks = maskNodes;
}

void LOTMaskContainer::setCurrentFrame(qreal currentFrame)
{
    if (_currentFrame == currentFrame) {
      return;
    }
    _currentFrame = currentFrame;

    for (auto nodeLayer : _masks) {
      nodeLayer->updateForFrame(currentFrame, bounds);
    }
}

qreal LOTMaskContainer::currentFrame() const
{
    return _currentFrame;
}
