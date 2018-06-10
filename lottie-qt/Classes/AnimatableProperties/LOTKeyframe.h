//
//  LOTKeyframe.h
//  Pods
//
//  Created by brandon_withrow on 7/10/17.
//
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import "LOTPlatformCompat.h"
#import "LOTBezierData.h"

#include <QSharedPointer>
#include <QPointF>
#include <QSizeF>

NS_ASSUME_NONNULL_BEGIN

@interface LOTKeyframe : NSObject

- (instancetype)initWithKeyframe:(NSDictionary *)keyframe;
- (instancetype)initWithValue:(id)value;
- (void)remapValueWithBlock:(CGFloat (^)(CGFloat inValue))remapBlock;
- (LOTKeyframe *)copyWithData:(id)data;

@property (nonatomic, readonly) NSNumber *keyframeTime;
@property (nonatomic, readonly) BOOL isHold;
@property (nonatomic, readonly) QPointF inTangent;
@property (nonatomic, readonly) QPointF outTangent;
@property (nonatomic, readonly) QPointF spatialInTangent;
@property (nonatomic, readonly) QPointF spatialOutTangent;

@property (nonatomic, readonly) CGFloat floatValue;
@property (nonatomic, readonly) QPointF pointValue;
@property (nonatomic, readonly) QSizeF sizeValue;
@property (nonatomic, readonly) UIColor *colorValue;
@property (nonatomic, readonly) QSharedPointer<LOTBezierData> pathData;
@property (nonatomic, readonly) NSArray *arrayValue;

@end

@interface LOTKeyframeGroup : NSObject

- (instancetype)initWithData:(id)data;

- (void)remapKeyframesWithBlock:(CGFloat (^)(CGFloat inValue))remapBlock;

@property (nonatomic, readonly) NSArray<LOTKeyframe *> *keyframes;

@end

NS_ASSUME_NONNULL_END
