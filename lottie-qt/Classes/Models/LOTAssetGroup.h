//
//  LOTAssetGroup.h
//  Pods
//
//  Created by Brandon Withrow on 2/17/17.
//
//

#pragma once

#include <QList>
#include <QMap>

class LOTAsset;
class LOTLayerGroup;

class LOTAssetGroup
{
public:

//@property (nonatomic, readwrite)
    void setRootDirectory(const QString &rootDirectory);
    QString rootDirectory() const;

//@property (nonatomic, readonly, nullable)
//    NSBundle *assetBundle = nil;

    LOTAssetGroup(const QVariantList &jsonArray,
                  qreal framerate);

    void buildAssetNamed(const QString &refID, qreal framerate);

    void finalizeInitializationWithFramerate(qreal framerate);

    LOTAsset *assetModelForID(const QString &assetID);

private:
    QString _rootDirectory;

    QMap<QString, LOTAsset *> _assetMap;
    QMap<QString, QVariantMap> _assetJSONMap;
};
