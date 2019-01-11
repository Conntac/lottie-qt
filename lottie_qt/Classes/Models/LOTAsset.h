//
//  LOTAsset.h
//  Pods
//
//  Created by Brandon Withrow on 2/16/17.
//
//

#pragma once

#include <QString>
#include <QVariantMap>

class LOTLayerGroup;
class LOTLayer;
class LOTAssetGroup;

class LOTAsset
{
public:
    LOTAsset(const QVariantMap &jsonDictionary,
             LOTAssetGroup *assetGroup,
             qreal framerate);
    ~LOTAsset();

//@property (nonatomic, readonly, nullable)
    QString referenceID;
//@property (nonatomic, readonly, nullable)
    qreal assetWidth;
//@property (nonatomic, readonly, nullable)
    qreal assetHeight;

//@property (nonatomic, readonly, nullable)
    QString imageName;
//@property (nonatomic, readonly, nullable)
    QString imageDirectory;

//@property (nonatomic, readonly, nullable)
    LOTLayerGroup *layerGroup = nullptr;

//@property (nonatomic, readwrite)
    QString rootDirectory;
//@property (nonatomic, readonly)
//    NSBundle *assetBundle = nullptr;
};

