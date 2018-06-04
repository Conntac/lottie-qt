//
//  LOTKeypath.h
//  Lottie_iOS
//
//  Created by brandon_withrow on 12/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "lotbase.h"

#include <QString>
#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QSharedPointer>

extern const QString kLOTKeypathEnd;

/*!
 @brief LOTKeypath is an object that describes a keypath search for nodes in the animation JSON. LOTKeypath matches views inside of LOTAnimationView to their After Effects counterparts.

 @discussion
 LOTKeypath is used with LOTAnimationView to set animation properties dynamically at runtime, to add or mask subviews, converting geometry, and numerous other functions.

 LOTKeypath can describe a specific object, or can use wildcards for fuzzy matching of objects. Acceptable wildcards are either "*" (star) or "**" (double star). Single star will search a single depth for the next object, double star will search any depth.

 Read More at http://airbnb.io/lottie/ios/dynamic.html
 
 EG:
  @"Layer.Shape Group.Stroke 1.Color"
  Represents a specific color node on a specific stroke.

  @"**.Stroke 1.Color"
  Represents the color node for every "Stroke 1" in the animation scene.

 */

class LOTKeypath
{
public:
/*!
 @brief Creates a LOTKeypath from a dot separated string, can use wildcards @"*" and fuzzy depth wild cards @"**".

 @discussion LOTKeypath is an object that describes a keypath search for nodes in the animation JSON.

 LOTKeypath is used with LOTAnimationView to set animation properties dynamically at runtime, to add or mask subviews, converting geometry, and numerous other functions.

 LOTKeypath can describe a specific object, or can use wildcards for fuzzy matching of objects. Acceptable wildcards are either "*" (star) or "**" (double star). Single star will search a single depth for the next object, double star will search any depth.

 @param  keypath A dot separated string describing a keypath from the JSON animation. EG @"Layer.Shape Group.Stroke 1.Color"

 @return A new LOTKeypath
 */
    LOTKeypath(const QString &keypath);

/*!
 @brief Creates a LOTKeypath from a list of keypath string objects, can use wildcards @"*" and fuzzy depth wild cards @"**".

 @discussion LOTKeypath is an object that describes a keypath search for nodes in the animation JSON.

 LOTKeypath is used with LOTAnimationView to set animation properties dynamically at runtime, to add or mask subviews, converting geometry, and numerous other functions.

 LOTKeypath can describe a specific object, or can use wildcards for fuzzy matching of objects. Acceptable wildcards are either "*" (star) or "**" (double star). Single star will search a single depth for the next object, double star will search any depth.

 @param  firstKey A nil terminated list of strings describing a keypath. EG @"Layer", @"Shape Group", @"Stroke 1", @"Color", nil

 @return A new LOTKeypath
 */

    LOTKeypath(const QStringList &keypaths);
    ~LOTKeypath();

//@property (nonatomic, readonly, nonnull)
    QString absoluteKeypath() const;
//@property (nonatomic, readonly, nonnull)
    QString currentKey() const;
//@property (nonatomic, readonly, nonnull)
    QString currentKeyPath() const;

//@property (nonatomic, readonly, nonnull)
    QMap<QString, QSharedPointer<LOTBase>> searchResults() const;

//@property (nonatomic, readonly)
    bool hasFuzzyWildcard() const;
//@property (nonatomic, readonly)
    bool hasWildcard() const;
//@property (nonatomic, readonly)
    bool endOfKeypath() const;

    bool pushKey(const QString &key);
    void popKey();
    void popToRootKey();

    void addSearchResultForCurrentPath(const QSharedPointer<LOTBase> &result);

private:
    void initWithKeys(const QStringList &keys);

    QString _absoluteKeypath;
    int _currentDepth;
    QList<int> _fuzzyDepthStack;
    QStringList _currentStack;
    QStringList _keys;
    QMap<QString, QSharedPointer<LOTBase>> _searchResults;
};
