//
//  LOTCompositionContainer.h
//  Lottie
//
//  Created by brandon_withrow on 7/18/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTLayerContainer.h"
#import "LOTAssetGroup.h"

class LOTNumberInterpolator;

class LOTCompositionContainer : public LOTLayerContainer
{
public:
    explicit LOTCompositionContainer(LOTLayer * _Nullable layer,
                                     LOTLayerGroup * _Nullable layerGroup,
                                     LOTLayerGroup * _Nullable childLayerGroup,
                                     LOTAssetGroup * _Nullable assetGroup);

    QStringList keysForKeyPath(LOTKeypath *keypath);

    /*
    CGPoint convertPointToKeypathLayer(CGPoint point,
                         LOTKeypath *_Nonnull keypath,
                         CALayer *_Nonnull parent);

    CGRect convertRectToKeypathLayer(CGRect rect,
                       LOTKeypath *_Nonnull keypath,
                       CALayer *_Nonnull parent);

    CGPoint convertPointFromKeypathLayer(CGPoint point,
                         LOTKeypath *_Nonnull keypath,
                         CALayer *_Nonnull parent);

    CGRect convertRectFromKeypathLayer(CGRect rect,
                       LOTKeypath *_Nonnull keypath,
                       CALayer *_Nonnull parent);

    void addSublayer(CALayer *subLayer,
                     LOTKeypath *_Nonnull keypath);

    void maskSublayer(CALayer *_Nonnull subLayer,
                      LOTKeypath *_Nonnull keypath);
    */

//    @property (nonatomic, readonly, nonnull)
    QList<QSharedPointer<LOTLayerContainer>> childLayers;
//    @property (nonatomic, readonly, nonnull)
    QMap<QString, QSharedPointer<LOTLayerContainer>> childMap;

    // LOTLayerContainer interface
    void setViewportBounds(const QRectF &viewportBounds) override;
    void displayWithFrame(qreal frame, bool forceUpdate) override;
    void searchNodesForKeypath(LOTKeypath *keypath) override;
    void setValueDelegate(LOTValueDelegate *delegate, LOTKeypath *keypath) override;

private:
    void initializeWithChildGroup(LOTLayerGroup *childGroup,
                                  LOTAssetGroup *assetGroup);

//    CALayer *_layerForKeypath(LOTKeypath *_Nonnull keypath);

    qreal _frameOffset = 0.0;
    QSharedPointer<QQuickLottieLayer> DEBUG_Center;
    QMap<QString, QSharedPointer<LOTBase>> _keypathCache;
    QSharedPointer<LOTNumberInterpolator> _timeInterpolator;
};
