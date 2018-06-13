//
//  LOTLayer.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LOTPlatformCompat.h"
#import "LOTKeyframe.h"

#include "lotbase.h"

#include <QString>
#include <QColor>
#include <QRectF>

class LOTShapeGroup;
class LOTMask;
class LOTAsset;
class LOTAssetGroup;

enum LOTLayerType {
  LOTLayerTypePrecomp,
  LOTLayerTypeSolid,
  LOTLayerTypeImage,
  LOTLayerTypeNull,
  LOTLayerTypeShape,
  LOTLayerTypeUnknown
};

enum LOTMatteType {
  LOTMatteTypeNone,
  LOTMatteTypeAdd,
  LOTMatteTypeInvert,
  LOTMatteTypeUnknown
};


class LOTLayer
{
public:
    LOTLayer(const QVariantMap &jsonDictionary,
             LOTAssetGroup * _Nullable assetGroup,
             qreal framerate);

//@property (nonatomic, readonly)
    QString layerName;
//@property (nonatomic, readonly, nullable)
    QString referenceID;
//@property (nonatomic, readonly)
    int layerID = -1; // default might also be a good -1
//@property (nonatomic, readonly)
    LOTLayerType layerType;
//@property (nonatomic, readonly, nullable)
    int parentID = -1; // default might also be a good -1
//@property (nonatomic, readonly)
    qreal startFrame;
//@property (nonatomic, readonly)
    qreal inFrame;
//@property (nonatomic, readonly)
    qreal outFrame;
//@property (nonatomic, readonly)
    qreal timeStretch;
//@property (nonatomic, readonly)
    QRectF layerBounds;

//@property (nonatomic, readonly, nullable)
    QList<LOTBase *> shapes;
//@property (nonatomic, readonly, nullable)
    QList<LOTMask *> masks;

//@property (nonatomic, readonly, nullable)
    qreal layerWidth;
//@property (nonatomic, readonly, nullable)
    qreal layerHeight;
//@property (nonatomic, readonly)
    QColor solidColor;
//@property (nonatomic, readonly, nullable)
    LOTAsset *imageAsset = nullptr;

//@property (nonatomic, readonly)
    LOTKeyframeGroup *opacity = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *timeRemapping = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *rotation = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *position = nullptr;

//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *positionX = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTKeyframeGroup *positionY = nullptr;

//@property (nonatomic, readonly)
    LOTKeyframeGroup *anchor = nullptr;
//@property (nonatomic, readonly)
    LOTKeyframeGroup *scale = nullptr;

//@property (nonatomic, readonly)
    LOTMatteType matteType;
};

