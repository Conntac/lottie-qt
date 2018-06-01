//
//  LOTBezierPath.h
//  Lottie
//
//  Created by brandon_withrow on 7/20/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTPlatformCompat.h"

#include <QPointF>
#include <QRectF>

NS_ASSUME_NONNULL_BEGIN

@interface LOTBezierPath : NSObject

+ (instancetype)pathWithCGPath:(CGPathRef)path;

+ (instancetype)newPath;

- (void)LOT_moveToPoint:(QPointF)point;

- (void)LOT_addLineToPoint:(QPointF)point;

- (void)LOT_addCurveToPoint:(QPointF)point
              controlPoint1:(QPointF)cp1
              controlPoint2:(QPointF)cp2;

- (void)LOT_closePath;

- (void)LOT_removeAllPoints;

- (void)LOT_appendPath:(LOTBezierPath *)bezierPath;

- (void)trimPathFromT:(qreal)fromT toT:(qreal)toT offset:(qreal)offset;

- (void)LOT_applyTransform:(CGAffineTransform)transform;

@property (nonatomic, assign) BOOL cacheLengths;

@property (nonatomic, readonly) CGFloat length;

@property (nonatomic, readonly) CGPathRef CGPath;
@property (nonatomic, readonly) QPointF currentPoint;
@property (nonatomic) CGFloat lineWidth;
@property (nonatomic) CGLineCap lineCapStyle;
@property (nonatomic) CGLineJoin lineJoinStyle;
@property (nonatomic) CGFloat miterLimit;
@property (nonatomic) CGFloat flatness;
@property (nonatomic) BOOL usesEvenOddFillRule;
@property (readonly, getter=isEmpty) BOOL empty;
@property (nonatomic, readonly) QRectF bounds;

@end

NS_ASSUME_NONNULL_END
