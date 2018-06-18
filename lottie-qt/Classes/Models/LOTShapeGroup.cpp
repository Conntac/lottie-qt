//
//  LOTShape.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTShapeGroup.h"
#include "LOTShapeFill.h"
#include "LOTShapePath.h"
#include "LOTShapeCircle.h"
#include "LOTShapeStroke.h"
#include "LOTShapeTransform.h"
#include "LOTShapeRectangle.h"
#include "LOTShapeTrimPath.h"
#include "LOTShapeGradientFill.h"
#include "LOTShapeStar.h"
#include "LOTShapeRepeater.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logLOTShapeGroup, "lottie.shape_group")

/*
- (NSString *)description {
    NSMutableString *text = [[super description] mutableCopy];
    [text appendFormat:@" items: %@", self.items];
    return text;
}
*/

LOTShapeGroup::LOTShapeGroup(const QVariantMap &jsonDictionary)
{
    keyname = jsonDictionary.value("nm").toString();

    QVariantList itemsJSON = jsonDictionary["it"].toList();
    for (const QVariant &variant : itemsJSON) {
      LOTShapeItem *newItem = LOTShapeGroup::shapeItemWithJSON(variant.toMap());
      if (newItem) {
        items.append(newItem);
      }
    }
}

LOTShapeItem *LOTShapeGroup::shapeItemWithJSON(const QVariantMap &itemJSON)
{
    QString type = itemJSON["ty"].toString();
    if (type == "gr") {
      LOTShapeGroup *group = new LOTShapeGroup(itemJSON);
      return group;
    } else if (type == "st") {
      LOTShapeStroke *stroke = new LOTShapeStroke(itemJSON);
      return stroke;
    } else if (type == "fl") {
      LOTShapeFill *fill = new LOTShapeFill(itemJSON);
      return fill;
    } else if (type == "tr") {
      LOTShapeTransform *transform = new LOTShapeTransform(itemJSON);
      return transform;
    } else if (type == "sh") {
      LOTShapePath *path = new LOTShapePath(itemJSON);
      return path;
    } else if (type == "el") {
      LOTShapeCircle *circle = new LOTShapeCircle(itemJSON);
      return circle;
    } else if (type == "rc") {
      LOTShapeRectangle *rectangle = new LOTShapeRectangle(itemJSON);
      return rectangle;
    } else if (type == "tm") {
      LOTShapeTrimPath *trim = new LOTShapeTrimPath(itemJSON);
      return trim;
    } else  if (type == "gs") {
      qCWarning(logLOTShapeGroup) << "gradient strokes are not supported";
    } else  if (type == "gf") {
      LOTShapeGradientFill *gradientFill = new LOTShapeGradientFill(itemJSON);
      return gradientFill;
    } else if (type == "sr") {
      LOTShapeStar *star = new LOTShapeStar(itemJSON);
      return star;
    } else if (type == "mm") {
      QString name = itemJSON["nm"].toString();
      qCWarning(logLOTShapeGroup) << "merge shape is not supported. name:" << name;
    } else if (type == "rp") {
      LOTShapeRepeater *repeater = new LOTShapeRepeater(itemJSON);
      return repeater;
    } else {
      QString name = itemJSON["nm"].toString();
      qCWarning(logLOTShapeGroup) << "Unsupported shape:" << type << "name:" <<name;
    }

    return nullptr;
}
