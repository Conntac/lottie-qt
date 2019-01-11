//
//  LOTBezierPath.h
//  Lottie
//
//  Created by brandon_withrow on 7/20/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#pragma once

#include <QPointF>
#include <QRectF>
#include <QPainterPath>
#include <QSharedPointer>
#include <QTransform>
#include <QEnableSharedFromThis>

struct LOT_Subpath {
  enum ElementType {
    MoveToPoint,
    AddLineToPoint,
    AddCurveToPoint,
    CloseSubpath
  };

  ElementType type;
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
    explicit LOTBezierPath(const QPainterPath &path);
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

    void LOT_applyTransform(const QTransform &transform);

//    @property (nonatomic, assign)
    bool cacheLengths;

//    @property (nonatomic, readonly)
    qreal length() const;

//    @property (nonatomic, readonly)
    QPainterPath CGPath() const;
//    @property (nonatomic, readonly)
    QPointF currentPoint() const;
//    @property (nonatomic)
    qreal lineWidth;
//    @property (nonatomic)
    Qt::PenCapStyle lineCapStyle;
//    @property (nonatomic)
    Qt::PenJoinStyle lineJoinStyle;
//    @property (nonatomic)
    qreal miterLimit;
//    @property (nonatomic)
    qreal flatness;
//    @property (nonatomic)
    bool usesEvenOddFillRule;
//    @property (readonly, getter=isEmpty)
    bool isEmpty() const;
//    @property (nonatomic, readonly)
    QRectF bounds() const;

private:
    void _clearPathData();
    bool containsPoint(const QPointF &point) const;
    void setWithCGPath(const QPainterPath &path);
    void addSubpathWithType(LOT_Subpath::ElementType type,
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
    QPainterPath _path;

    Q_DISABLE_COPY(LOTBezierPath)
};

