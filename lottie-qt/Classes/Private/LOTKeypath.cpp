//
//  LOTKeypath.m
//  Lottie_iOS
//
//  Created by brandon_withrow on 12/13/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#include "LOTKeypath.h"

const QString kLOTKeypathEnd = "LOTENDKEYPATH";

LOTKeypath::LOTKeypath(const QString &keypath)
{
    initWithKeys(keypath.split('.'));
}

LOTKeypath::LOTKeypath(const QStringList &keypath)
{
    initWithKeys(keypath);
}

LOTKeypath::~LOTKeypath()
{
}

QString LOTKeypath::absoluteKeypath() const
{
    return _absoluteKeypath;
}

QString LOTKeypath::currentKey() const
{
    if (_currentDepth == _keys.size()) {
      return kLOTKeypathEnd;
    }
    return _keys[_currentDepth];
}

QString LOTKeypath::currentKeyPath() const
{
    return _currentStack.join('.');
}

QMap<QString, QSharedPointer<LOTBase> > LOTKeypath::searchResults() const
{
    return _searchResults;
}

bool LOTKeypath::hasFuzzyWildcard() const
{
    if (_currentDepth == 0 ||
        _currentDepth > _keys.size()) {
      return false;
    }
    return _keys[_currentDepth - 1] == "**";
}

bool LOTKeypath::hasWildcard() const
{
    if (_currentDepth == _keys.size()) {
      return false;
    }
    return (_keys[_currentDepth] == "**" ||
            _keys[_currentDepth] == "*");
}

bool LOTKeypath::endOfKeypath() const
{
    return (_currentDepth == _keys.size());
}

bool LOTKeypath::pushKey(const QString &key)
{
    if (_currentDepth == _keys.size() &&
        hasFuzzyWildcard() == false) {
      return false;
    }
    QString current = currentKey();
    if (hasWildcard() ||
      current == key) {
      _currentStack.append(key);
      _currentDepth ++;
      if (hasFuzzyWildcard()) {
        _fuzzyDepthStack.append(_currentDepth);
      }
      return true;
    } else if (hasFuzzyWildcard()) {
      _currentStack.append(key);
      return true;
    }
    return false;
}

void LOTKeypath::popKey()
{
    if (_currentDepth == 0) {
      return;
    }
    int stackCount = _currentStack.size();
    _currentStack.removeLast();

    if (hasFuzzyWildcard()) {
      if (stackCount == _fuzzyDepthStack.last()) {
          _fuzzyDepthStack.removeLast();
      } else {
        return;
      }
    }
    _currentDepth --;
}

void LOTKeypath::popToRootKey()
{
    _currentDepth = 0;
    _currentStack.clear();
    _fuzzyDepthStack.clear();
}

void LOTKeypath::addSearchResultForCurrentPath(const QSharedPointer<LOTBase> &result)
{
    _searchResults.insert(currentKeyPath(), result);
}

void LOTKeypath::initWithKeys(const QStringList &keys)
{
    _keys = keys;
    _currentStack.clear();
    _absoluteKeypath = keys.join('.');
    _currentDepth = 0;
    _fuzzyDepthStack.clear();
    _searchResults.clear();
}
