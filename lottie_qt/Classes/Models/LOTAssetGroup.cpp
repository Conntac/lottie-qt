//
//  LOTAssetGroup.m
//  Pods
//
//  Created by Brandon Withrow on 2/17/17.
//
//

#include "LOTAssetGroup.h"
#include "LOTAsset.h"

void LOTAssetGroup::setRootDirectory(const QString &rootDirectory)
{
    _rootDirectory = rootDirectory;

    for(LOTAsset *obj : _assetMap) {
        obj->rootDirectory = rootDirectory;
    }
}

QString LOTAssetGroup::rootDirectory() const
{
    return _rootDirectory;
}

LOTAssetGroup::LOTAssetGroup(const QVariantList &jsonArray, qreal framerate)
{
//    assetBundle = bundle;

    for(const QVariant &variant : jsonArray) {
        QVariantMap assetDictionary = variant.toMap();

        if (assetDictionary.contains("id")) {
            QString referenceID = assetDictionary.value("id").toString();
            _assetJSONMap.insert(referenceID, assetDictionary);
        }
    }
}

LOTAssetGroup::~LOTAssetGroup()
{
    qDeleteAll(_assetMap);
}

void LOTAssetGroup::buildAssetNamed(const QString &refID, qreal framerate)
{
    if (assetModelForID(refID)) {
      return;
    }

    QVariantMap assetDictionary = _assetJSONMap.value(refID);
    if (!assetDictionary.isEmpty()) {
      LOTAsset *asset = new LOTAsset(assetDictionary, this, framerate);
      _assetMap.insert(refID, asset);
    }
}

void LOTAssetGroup::finalizeInitializationWithFramerate(qreal framerate)
{
    for (const QString &refID : _assetJSONMap.keys()) {
      buildAssetNamed(refID, framerate);
    }
    _assetJSONMap.clear();
}

LOTAsset *LOTAssetGroup::assetModelForID(const QString &assetID)
{
    return _assetMap.value(assetID);
}
