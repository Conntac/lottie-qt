//
//  LOTLayerContainer.h
//  Lottie
//
//  Created by brandon_withrow on 7/18/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTLayer.h"
#import "LOTLayerGroup.h"
#import "LOTKeypath.h"
#import "LOTValueDelegate.h"

#include "qquicklottielayer.h"

#include <QMap>
#include <QSharedPointer>


class LOTMaskContainer;
class LOTRenderGroup;

class LOTValueInterpolator;
class LOTTransformInterpolator;
class LOTNumberInterpolator;

class LOTLayerContainer : public QQuickLottieLayer
{
public:
    explicit LOTLayerContainer(LOTLayer * _Nullable layer,
                               LOTLayerGroup * _Nullable layerGroup);
//    explicit LOTLayerContainer(const QSharedPointer<QQuickLottieLayer> &layer);

//    @property (nonatomic, readonly, strong, nullable)
    QString layerName;
//    @property (nonatomic, nullable)
    qreal currentFrame = 0.0;
//    @property (nonatomic, readonly, nonnull)
    qreal timeStretchFactor = 0.0;
//    @property (nonatomic, assign)
    QRectF viewportBounds() const;
    virtual void setViewportBounds(const QRectF &viewportBounds);
//    @property (nonatomic, readonly)
    QSharedPointer<QQuickLottieLayer> wrapperLayer;
//    @property (nonatomic, readonly)
    QMap<QString, QSharedPointer<LOTValueInterpolator>> valueInterpolators;

    void displayWithFrame(qreal frame);
    virtual void displayWithFrame(qreal frame, bool forceUpdate);

    virtual void searchNodesForKeypath(LOTKeypath *keypath);

    virtual void setValueDelegate(LOTValueDelegate *delegate,
                                  LOTKeypath *keypath);

    // QQuickLottieLayer interface
    void actionForKey(const QString &event) override;
    void display() override;

private:
    void commonInitializeWith(LOTLayer *layer,
                              LOTLayerGroup *layerGroup);
    void buildContents(const QList<LOTBase *> &contents);

    QRectF _viewportBounds;

    QSharedPointer<LOTTransformInterpolator> _transformInterpolator;
    QSharedPointer<LOTNumberInterpolator> _opacityInterpolator;
    qreal _inFrame;
    qreal _outFrame;
    QSharedPointer<QQuickLottieLayer> DEBUG_Center;
    QSharedPointer<LOTRenderGroup> _contentsGroup;
    QSharedPointer<LOTMaskContainer> _maskLayer;
};

