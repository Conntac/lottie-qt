//
//  LOTValueInterpolator.h
//  Pods
//
//  Created by brandon_withrow on 7/10/17.
//
//

#import <Foundation/Foundation.h>
#import "LOTKeyframe.h"
#import "LOTValueDelegate.h"

#include <QtCore>

NS_ASSUME_NONNULL_BEGIN

class LOTValueInterpolator
{
public:
    explicit LOTValueInterpolator(NSArray <LOTKeyframe *> *keyframes);
    virtual ~LOTValueInterpolator();

    // Properties
    LOTKeyframe *leadingKeyframe = nullptr;
    LOTKeyframe *trailingKeyframe = nullptr;

    // Functions
    virtual bool hasDelegateOverride() const;
    virtual void setValueDelegate(id<LOTValueDelegate> _Nonnull delegate);

    bool hasUpdateForFrame(qreal frame);
    qreal progressForFrame(qreal frame);

private:
    void updateKeyframeSpanForFrame(qreal frame);

    NSArray <LOTKeyframe *> *keyframes;
};

NS_ASSUME_NONNULL_END
