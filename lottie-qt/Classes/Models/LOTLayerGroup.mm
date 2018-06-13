//
//  LOTLayerGroup.m
//  Pods
//
//  Created by Brandon Withrow on 2/16/17.
//
//

#import "LOTLayerGroup.h"
#import "LOTLayer.h"
#import "LOTAssetGroup.h"

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
