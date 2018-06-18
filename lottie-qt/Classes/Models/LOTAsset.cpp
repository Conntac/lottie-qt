//
//  LOTAsset.m
//  Pods
//
//  Created by Brandon Withrow on 2/16/17.
//
//

#include "LOTAsset.h"
#include "LOTLayer.h"
#include "LOTLayerGroup.h"
#include "LOTAssetGroup.h"

LOTAsset::LOTAsset(const QVariantMap &jsonDictionary, LOTAssetGroup *assetGroup, qreal framerate)
{
//    assetBundle = nil;

    referenceID = jsonDictionary.value("id").toString();

    assetWidth = jsonDictionary.value("w", 0.0).toReal();
    assetHeight = jsonDictionary.value("h", 0.0).toReal();
    imageDirectory = jsonDictionary.value("u").toString();
    imageName = jsonDictionary.value("p").toString();

    QVariant layers = jsonDictionary.value("layers");
    if (!layers.isNull()) {
        layerGroup = new LOTLayerGroup(layers.toList(), assetGroup, framerate);
    }
}
