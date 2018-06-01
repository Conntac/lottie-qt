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
#include <QSharedPointer>
#include <QEnableSharedFromThis>

NS_ASSUME_NONNULL_BEGIN

struct LOT_Subpath {
  CGPathElementType type;
  qreal length;
  QPointF endPoint;
  QPointF controlPoint1;
  QPointF controlPoint2;
  LOT_Subpath *nextSubpath;
};

class LOTBezierPath : public QEnableSharedFromThis<LOTBezierPath>
{
public:
    LOTBezierPath();
    explicit LOTBezierPath(CGPathRef path);
    ~LOTBezierPath();

    QSharedPointer<LOTBezierPath> copy();

    void LOT_moveToPoint(const QPointF &point);

    void LOT_addLineToPoint(const QPointF &point);

    void LOT_addCurveToPoint(const QPointF &point,
                             const QPointF &cp1,
                             const QPointF &cp2);

    void LOT_closePath();

    void LOT_removeAllPoints();

    void LOT_appendPath(QSharedPointer<LOTBezierPath> bezierPath);

    void trimPathFromT(qreal fromT, qreal toT, qreal offset);

    void LOT_applyTransform(CGAffineTransform transform);

//    @property (nonatomic, assign)
    BOOL cacheLengths;

//    @property (nonatomic, readonly)
    qreal length() const;

//    @property (nonatomic, readonly)
    CGPathRef CGPath() const;
//    @property (nonatomic, readonly)
    QPointF currentPoint() const;
//    @property (nonatomic)
    CGFloat lineWidth;
//    @property (nonatomic)
    CGLineCap lineCapStyle;
//    @property (nonatomic)
    CGLineJoin lineJoinStyle;
//    @property (nonatomic)
    CGFloat miterLimit;
//    @property (nonatomic)
    CGFloat flatness;
//    @property (nonatomic)
    BOOL usesEvenOddFillRule;
//    @property (readonly, getter=isEmpty)
    bool isEmpty() const;
//    @property (nonatomic, readonly)
    QRectF bounds() const;

private:
    void _clearPathData();
    bool containsPoint(const QPointF &point) const;
    void setWithCGPath(CGPathRef path);
    void addSubpathWithType(CGPathElementType type,
                            qreal length,
                            const QPointF &endPoint,
                            const QPointF &controlPoint1,
                            const QPointF &controlPoint2);
    void removeAllSubpaths();


    LOT_Subpath *headSubpath() const;
//    @property (nonatomic, readonly) LOT_Subpath *headSubpath;

    qreal _length;

    LOT_Subpath *headSubpath_;
    LOT_Subpath *tailSubpath_;
    QPointF subpathStartPoint_;
    qreal *_lineDashPattern;
    int _lineDashCount;
    qreal _lineDashPhase;
    CGMutablePathRef _path;

    Q_DISABLE_COPY(LOTBezierPath)
};

NS_ASSUME_NONNULL_END
