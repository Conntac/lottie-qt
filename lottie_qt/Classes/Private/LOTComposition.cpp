//
//  LOTScene.m
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#include "LOTComposition.h"
#include "LOTLayer.h"
#include "LOTAssetGroup.h"
#include "LOTLayerGroup.h"
//#include "LOTAnimationCache.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logLOTComposition, "lottie.composition")

/*

+ (nullable instancetype)animationNamed:(nonnull NSString *)animationName inBundle:(nonnull NSBundle *)bundle {
  NSArray *components = [animationName componentsSeparatedByString:@"."];
  animationName = components.firstObject;
  
  LOTComposition *comp = [[LOTAnimationCache sharedCache] animationForKey:animationName];
  if (comp) {
    return comp;
  }
  
  NSError *error;
  NSString *filePath = [bundle pathForResource:animationName ofType:@"json"];
  NSData *jsonData = [[NSData alloc] initWithContentsOfFile:filePath];
  
  if (@available(iOS 9.0, *)) {
    if (!jsonData) {
      jsonData = [[NSDataAsset alloc] initWithName:animationName].data;
    }
  }
  
  NSDictionary  *JSONObject = jsonData ? [NSJSONSerialization JSONObjectWithData:jsonData
                                                                         options:0 error:&error] : nil;
  if (JSONObject && !error) {
    LOTComposition *laScene = [[self alloc] initWithJSON:JSONObject withAssetBundle:bundle];
    [[LOTAnimationCache sharedCache] addAnimation:laScene forKey:animationName];
    laScene.cacheKey = animationName;
    return laScene;
  }
  NSLog(@"%s: Animation Not Found", __PRETTY_FUNCTION__);
  return nil;
}
*/

/*
+ (nullable instancetype)animationWithFilePath:(const QString &)filePath {
//  NSString *animationName = filePath;
  
//  LOTComposition *comp = [[LOTAnimationCache sharedCache] animationForKey:animationName];
//  if (comp) {
//    return comp;
//  }

  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly)) {
    return nil;
  }
  
  NSError *error;
  NSData *jsonData = file.readAll().toNSData();
  NSDictionary  *JSONObject = jsonData ? [NSJSONSerialization JSONObjectWithData:jsonData
                                                                         options:0 error:&error] : nil;
  if (JSONObject && !error) {
    LOTComposition *laScene = [[self alloc] initWithJSON:JSONObject withAssetBundle:[NSBundle mainBundle]];
//    laScene.rootDirectory = [filePath stringByDeletingLastPathComponent];
//    [[LOTAnimationCache sharedCache] addAnimation:laScene forKey:animationName];
//    laScene.cacheKey = animationName;
    return laScene;
  }
  
  NSLog(@"%s: Animation Not Found", __PRETTY_FUNCTION__);
  return nil;
}
*/

LOTComposition::LOTComposition()
{
}

LOTComposition::~LOTComposition()
{
    delete layerGroup;
    delete assetGroup;
}

bool LOTComposition::loadFromData(const QByteArray &data)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error == QJsonParseError::NoError) {
        QJsonObject obj = doc.object();
        mapFromJSON(obj.toVariantMap());

        return true;
    } else {
        qCCritical(logLOTComposition) << "Error parsing JSON:" << error.errorString();
    }

    return false;
}

void LOTComposition::setRootDirectory(const QString &rootDirectory)
{
    _rootDirectory = rootDirectory;
    assetGroup->setRootDirectory(rootDirectory);
}

QString LOTComposition::rootDirectory() const
{
    return _rootDirectory;
}

void LOTComposition::mapFromJSON(const QVariantMap &jsonDictionary)
{
    qreal width = jsonDictionary["w"].toReal();
    qreal height = jsonDictionary["h"].toReal();
    if (width && height) {
      compBounds = QRectF(0, 0, width, height);
    }

    startFrame = jsonDictionary.value("ip", -1).toInt();
    endFrame = jsonDictionary.value("op", -1).toInt();
    framerate = jsonDictionary.value("fr", -1).toInt();

    if (startFrame != -1 && endFrame != -1 && framerate != -1) {
      int frameDuration = (endFrame - startFrame) - 1;
      timeDuration = frameDuration / framerate;
    }

    if (jsonDictionary.contains("assets")) {
      assetGroup = new LOTAssetGroup(jsonDictionary.value("assets").toList(), framerate);
    }

    QVariantList layersJSON = jsonDictionary["layers"].toList();
    if (layersJSON.size()) {
      layerGroup = new LOTLayerGroup(layersJSON, assetGroup, framerate);
    }

    assetGroup->finalizeInitializationWithFramerate(framerate);
}
