//
//  LOTScene.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#pragma once

#include <QString>
#include <QRectF>
#include <QVariantMap>

class LOTLayerGroup;
class LOTLayer;
class LOTAssetGroup;

class LOTComposition
{
public:
    LOTComposition(const QString &filePath);

//@property (nonatomic, readonly)
    QRectF compBounds;
//@property (nonatomic, readonly, nullable)
    int startFrame;
//@property (nonatomic, readonly, nullable)
    int endFrame;
//@property (nonatomic, readonly, nullable)
    qreal framerate = 0.0;
//@property (nonatomic, readonly)
    qreal timeDuration = 0.0;
//@property (nonatomic, readonly, nullable)
    LOTLayerGroup *layerGroup = nullptr;
//@property (nonatomic, readonly, nullable)
    LOTAssetGroup *assetGroup = nullptr;
//@property (nonatomic, readwrite, nullable)
    void setRootDirectory(const QString &rootDirectory);
    QString rootDirectory() const;
//@property (nonatomic, readonly, nullable)
//    NSBundle *assetBundle = nil;
//@property (nonatomic, copy, nullable)
    QString cacheKey;

private:
    void mapFromJSON(const QVariantMap &jsonDictionary);

    QString _rootDirectory;
};
