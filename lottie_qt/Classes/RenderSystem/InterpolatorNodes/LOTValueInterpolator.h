//
//  LOTValueInterpolator.h
//  Pods
//
//  Created by brandon_withrow on 7/10/17.
//
//

#pragma once

#include "LOTKeyframe.h"
#include "LOTValueDelegate.h"

class LOTValueInterpolator
{
public:
    explicit LOTValueInterpolator(const QList<LOTKeyframe *> &keyframes);
    virtual ~LOTValueInterpolator();

    // Properties
    LOTKeyframe *leadingKeyframe = nullptr;
    LOTKeyframe *trailingKeyframe = nullptr;

    // Functions
    virtual bool hasDelegateOverride() const;
    virtual void setValueDelegate(LOTValueDelegate *delegate);

    bool hasUpdateForFrame(qreal frame);
    qreal progressForFrame(qreal frame);

private:
    void updateKeyframeSpanForFrame(qreal frame);

    QList<LOTKeyframe *> keyframes;
};

