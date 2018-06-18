//
//  LOTLayerGroup.m
//  Pods
//
//  Created by Brandon Withrow on 2/16/17.
//
//

#include "LOTLayerGroup.h"
#include "LOTLayer.h"
#include "LOTAssetGroup.h"

LOTLayerGroup::LOTLayerGroup(const QVariantList &layersJSON, LOTAssetGroup *assetGroup, qreal framerate)
{
    for(const QVariant &variant : layersJSON) {
        QVariantMap layerJSON = variant.toMap();

        LOTLayer *layer = new LOTLayer(layerJSON, assetGroup, framerate);
        layers.append(layer);
        _modelMap.insert(layer->layerID, layer);

        if (!layer->referenceID.isNull()) {
            _referenceIDMap.insert(layer->referenceID, layer);
        }
    }
}

LOTLayer *LOTLayerGroup::layerModelForID(int layerID)
{
    return _modelMap.value(layerID);
}

LOTLayer *LOTLayerGroup::layerForReferenceID(const QString &referenceID)
{
    return _referenceIDMap.value(referenceID);
}
