//
//  LOTLayer.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTLayer.h"
#include "LOTAsset.h"
#include "LOTAssetGroup.h"
#include "LOTShapeGroup.h"
#include "LOTComposition.h"
#include "LOTHelpers.h"
#include "LOTMask.h"
#include "LOTHelpers.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logLOTLayer, "lottie.layer")

/*
- (NSString *)description {
    NSMutableString *text = [[super description] mutableCopy];
    [text appendFormat:@" %@ id: %d pid: %d frames: %d-%d", _layerName.toNSString(), (int)_layerID.integerValue, (int)_parentID.integerValue,
     (int)_inFrame.integerValue, (int)_outFrame.integerValue];
    return text;
}
*/

LOTLayer::LOTLayer(const QVariantMap &jsonDictionary, LOTAssetGroup *assetGroup, qreal framerate)
{
    layerName = jsonDictionary.value("nm").toString();
    layerID = jsonDictionary.value("ind").toInt();

    layerType = static_cast<LOTLayerType>(jsonDictionary.value("ty").toInt());

    referenceID = jsonDictionary.value("refId").toString();

    parentID = jsonDictionary.value("parent", -1).toInt();

    startFrame = jsonDictionary.value("st").toReal(); // Asumme 0.0 default
//    if (jsonDictionary[@"st"]) {
//      _startFrame = [jsonDictionary[@"st"] copy];
//    }
    inFrame = jsonDictionary.value("ip").toReal();
    outFrame = jsonDictionary.value("op").toReal();

    timeStretch = jsonDictionary.value("sr", 1.0).toReal();

    if (layerType == LOTLayerTypePrecomp) {
      layerHeight = jsonDictionary.value("h").toReal();
      layerWidth = jsonDictionary.value("w").toReal();
      assetGroup->buildAssetNamed(referenceID, framerate);
    } else if (layerType == LOTLayerTypeImage) {
      assetGroup->buildAssetNamed(referenceID, framerate);
      imageAsset = assetGroup->assetModelForID(referenceID);
      layerWidth = imageAsset->assetWidth;
      layerHeight = imageAsset->assetHeight;
    } else if (layerType == LOTLayerTypeSolid) {
      layerWidth = jsonDictionary.value("sw").toReal();
      layerHeight = jsonDictionary.value("sh").toReal();
      solidColor = QColor(jsonDictionary.value("sc").toString());
    }

    layerBounds = QRectF(0, 0, layerWidth, layerHeight);

    QVariantMap ks = jsonDictionary.value("ks").toMap();

    if (ks.contains("o")) {
      opacity = new LOTKeyframeGroup(ks.value("o"));
      opacity->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, 0, 100, 0, 1);
      });
    }

    if (jsonDictionary.contains("tm")) {
      timeRemapping = new LOTKeyframeGroup(jsonDictionary.value("tm"));
      timeRemapping->remapKeyframesWithBlock([=](qreal inValue) -> qreal {
        return inValue * framerate;
      });
    }

    QVariantMap rotation = ks.value("r").toMap();
    if (rotation.isEmpty()) {
      rotation = ks.value("rz").toMap();
    }
    if (!rotation.isEmpty()) {
      this->rotation = new LOTKeyframeGroup(rotation);
      this->rotation->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_DegreesToRadians(inValue);
      });
    }

    QVariantMap position = ks.value("p").toMap();
    if (position.value("s").toBool()) {
      // Separate dimensions
      positionX = new LOTKeyframeGroup(position.value("x"));
      positionY = new LOTKeyframeGroup(position.value("y"));
    } else {
      this->position = new LOTKeyframeGroup(position);
    }

    if (ks.contains("a")) {
        anchor = new LOTKeyframeGroup(ks.value("a"));
    }

    if (ks.contains("s")) {
      scale = new LOTKeyframeGroup(ks.value("s"));
      scale->remapKeyframesWithBlock([](qreal inValue) -> qreal {
        return LOT_RemapValue(inValue, -100, 100, -1, 1);
      });
    }

    matteType = static_cast<LOTMatteType>(jsonDictionary.value("tt").toInt());

    for(const QVariant &variant : jsonDictionary.value("masksProperties").toList()) {
        LOTMask *mask = new LOTMask(variant.toMap());
        masks.append(mask);
    }

    for(const QVariant &variant : jsonDictionary.value("shapes").toList()) {
        LOTShapeItem *shapeItem = LOTShapeGroup::shapeItemWithJSON(variant.toMap());
        // FIXME: Handle parsing errors (return null)
        if (shapeItem) {
            shapes.append(shapeItem);
        }
    }

    QVariantList effects = jsonDictionary.value("ef").toList();
    if (effects.size() > 0) {
      QMap<int, QString> effectNames = {
         {0,  "slider"},
         {1,  "angle"},
         {2,  "color"},
         {3,  "point"},
         {4,  "checkbox"},
         {5,  "group"},
         {6,  "noValue"},
         {7,  "dropDown"},
         {9,  "customValue"},
         {10, "layerIndex"},
         {20, "tint"},
         {21, "fill"}
      };

      for(const QVariant &variant : effects) {
          QVariantMap effect = variant.toMap();

          int typeNumber = effect.value("ty").toInt();
          QString name = effect.value("nm").toString();
          QString internalName = effect.value("mn").toString();
          QString typeString = effectNames.value(typeNumber);
          if (!typeString.isNull()) {
              qCWarning(logLOTLayer) << typeString << "effect not supported:" << internalName << "/" << name;
          }
      }
    }
}
