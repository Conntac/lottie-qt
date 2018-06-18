//
//  LOTLayerGroup.h
//  Pods
//
//  Created by Brandon Withrow on 2/16/17.
//
//

#pragma once

#include <QVariantMap>

class LOTLayer;
class LOTAssetGroup;

class LOTLayerGroup
{
public:
    LOTLayerGroup(const QVariantList &layersJSON,
                  LOTAssetGroup * assetGroup,
                  qreal framerate);

//@property (nonatomic, readonly)
    QList<LOTLayer *> layers;

    LOTLayer *layerModelForID(int layerID);
    LOTLayer *layerForReferenceID(const QString &referenceID);

private:
    QMap<int, LOTLayer *> _modelMap;
    QMap<QString, LOTLayer *> _referenceIDMap;
};

