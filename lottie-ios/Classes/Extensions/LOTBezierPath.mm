//
//  LOTBezierPath.m
//  Lottie
//
//  Created by brandon_withrow on 7/20/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTBezierPath.h"
#import "CGGeometry+LOTAdditions.h"

#include <QTransform>

typedef void(^LOTBezierPathEnumerationHandler)(const CGPathElement *element);


/*
- (id)copyWithZone:(NSZone *)zone {
  LOTBezierPath *copy = [[self class] new];
  
  copy.cacheLengths = self.cacheLengths;
  copy.lineWidth = self.lineWidth;
  copy.lineCapStyle = self.lineCapStyle;
  copy.lineJoinStyle = self.lineJoinStyle;
  copy.miterLimit = self.miterLimit;
  copy.flatness = self.flatness;
  copy.usesEvenOddFillRule = self.usesEvenOddFillRule;
  
  [copy LOT_appendPath:self];
  
  return copy;
}
*/

static void lot_enumeratePath(CGPathRef cgPath, LOTBezierPathEnumerationHandler handler) {
  void CGPathEnumerationCallback(void *info, const CGPathElement *element);
  CGPathApply(cgPath, (__bridge void * _Nullable)(handler), CGPathEnumerationCallback);
}

void CGPathEnumerationCallback(void *info, const CGPathElement *element)
{
  LOTBezierPathEnumerationHandler handler = (__bridge  LOTBezierPathEnumerationHandler)(info);
  if (handler) {
    handler(element);
  }
}

LOTBezierPath::LOTBezierPath()
{
    _length = 0;
    headSubpath_ = NULL;
    tailSubpath_ = NULL;
    lineWidth = 1;
    lineCapStyle = kCGLineCapButt;
    lineJoinStyle = kCGLineJoinMiter;
    miterLimit = 10;
    flatness = 0.6;
    usesEvenOddFillRule = NO;
    _lineDashPattern = NULL;
    _lineDashCount = 0;
    _lineDashPhase = 0;
    cacheLengths = NO;
}

LOTBezierPath::LOTBezierPath(CGPathRef path)
: LOTBezierPath()
{
    setWithCGPath(path);
}

LOTBezierPath::~LOTBezierPath()
{
    removeAllSubpaths();
}

QSharedPointer<LOTBezierPath> LOTBezierPath::copy()
{
    QSharedPointer<LOTBezierPath> copy = copy.create();

    copy->cacheLengths = cacheLengths;
    copy->lineWidth = lineWidth;
    copy->lineCapStyle = lineCapStyle;
    copy->lineJoinStyle = lineJoinStyle;
    copy->miterLimit = miterLimit;
    copy->flatness = flatness;
    copy->usesEvenOddFillRule = usesEvenOddFillRule;

    copy->LOT_appendPath(sharedFromThis());

    return copy;
}

void LOTBezierPath::LOT_moveToPoint(const QPointF &point)
{
    subpathStartPoint_ = point;
    addSubpathWithType(kCGPathElementMoveToPoint, 0, point, QPointF(), QPointF());
    _path.moveTo(point);
}

void LOTBezierPath::LOT_addLineToPoint(const QPointF &point)
{
    qreal length = 0;
    if (cacheLengths) {
      length = LOT_PointDistanceFromPoint(currentPoint(), point);
      _length = _length + length;
    }
    addSubpathWithType(kCGPathElementAddLineToPoint, length, point, QPointF(), QPointF());
    _path.lineTo(point);
}

void LOTBezierPath::LOT_addCurveToPoint(const QPointF &point, const QPointF &cp1, const QPointF &cp2)
{
    qreal length = 0;
    if (cacheLengths) {
      length = LOT_CubicLengthWithPrecision(currentPoint(), point, cp1, cp2, 5);
      _length = _length + length;
    }
    addSubpathWithType(kCGPathElementAddCurveToPoint, length, point, cp1, cp2);
    _path.cubicTo(cp1, cp2, point);
}

void LOTBezierPath::LOT_closePath()
{
    qreal length = 0;
    if (cacheLengths) {
      length = LOT_PointDistanceFromPoint(currentPoint(), subpathStartPoint_);
      _length = _length + length;
    }
    addSubpathWithType(kCGPathElementCloseSubpath, length, subpathStartPoint_, QPointF(), QPointF());
    _path.closeSubpath();
}

void LOTBezierPath::LOT_removeAllPoints()
{
    removeAllSubpaths();
    _clearPathData();
}

void LOTBezierPath::LOT_appendPath(QSharedPointer<LOTBezierPath> bezierPath)
{
    _path.addPath(bezierPath->CGPath());

    LOT_Subpath *nextSubpath = bezierPath->headSubpath();
    while (nextSubpath) {
      CGFloat length = 0;
      if (cacheLengths) {
        if (bezierPath->cacheLengths) {
          length = nextSubpath->length;
        } else {
          // No previous length data, measure.
          if (nextSubpath->type == kCGPathElementAddLineToPoint) {
            length = LOT_PointDistanceFromPoint(currentPoint(), nextSubpath->endPoint);
          } else if (nextSubpath->type == kCGPathElementAddCurveToPoint) {
            length = LOT_CubicLengthWithPrecision(currentPoint(), nextSubpath->endPoint, nextSubpath->controlPoint1, nextSubpath->controlPoint2, 5);
          } else if (nextSubpath->type == kCGPathElementCloseSubpath) {
            length = LOT_PointDistanceFromPoint(currentPoint(), nextSubpath->endPoint);
          }
        }
      }
      _length = _length + length;
      addSubpathWithType(nextSubpath->type,
                         length,
                         nextSubpath->endPoint,
                         nextSubpath->controlPoint1,
                         nextSubpath->controlPoint2);

      nextSubpath = nextSubpath->nextSubpath;
    }
}

void LOTBezierPath::trimPathFromT(qreal fromT, qreal toT, qreal offset)
{
    fromT = MIN(MAX(0, fromT), 1);
    toT = MIN(MAX(0, toT), 1);
    if (fromT > toT) {
      qreal to = fromT;
      fromT = toT;
      toT = to;
    }

    offset = offset - floor(offset);
    qreal fromLength = fromT + offset;
    qreal toLength = toT + offset;

    if (toT - fromT == 1) {
      // Do Nothing, Full Path returned.
      return;
    }

    if (fromLength == toLength) {
      // Empty Path
      LOT_removeAllPoints();
      return;
    }

    if (fromLength >= 1) {
      fromLength = fromLength - floor(fromLength);
    }
    if (toLength > 1) {
      toLength = toLength - floor(toLength);
    }

    if (fromLength == 0 &&
        toLength == 1) {
      // Do Nothing. Full Path returned.
      return;
    }

    if (fromLength == toLength) {
      // Empty Path
      LOT_removeAllPoints();
      return;
    }

    qreal totalLength = _length;

    _clearPathData();

    LOT_Subpath *subpath = headSubpath_;
    headSubpath_ = NULL;
    tailSubpath_ = NULL;

    fromLength = fromLength * totalLength;
    toLength = toLength * totalLength;

    qreal currentStartLength = fromLength < toLength ? fromLength : 0;
    qreal currentEndLength = toLength;

    qreal subpathBeginningLength = 0;
    QPointF currentPoint;

    while (subpath) {

      CGFloat pathLength = subpath->length;
      if (!cacheLengths) {
        if (subpath->type == kCGPathElementAddLineToPoint) {
          pathLength = LOT_PointDistanceFromPoint(currentPoint, subpath->endPoint);
        } else if (subpath->type == kCGPathElementAddCurveToPoint) {
          pathLength = LOT_CubicLengthWithPrecision(currentPoint, subpath->endPoint, subpath->controlPoint1, subpath->controlPoint2, 5);
        } else if (subpath->type == kCGPathElementCloseSubpath) {
          pathLength = LOT_PointDistanceFromPoint(currentPoint, subpath->endPoint);
        }
      }
      CGFloat subpathEndLength = subpathBeginningLength + pathLength;

      if (subpath->type != kCGPathElementMoveToPoint &&
          subpathEndLength > currentStartLength) {
        // The end of this path overlaps the current drawing region

        // x                    x                                 x                          x
        // ---------------ooooooooooooooooooooooooooooooooooooooooooooooooo-------------------
        // Start          |currentStartLength             currentEndLength|                End

        qreal currentSpanStartT = LOT_RemapValue(currentStartLength, subpathBeginningLength, subpathEndLength, 0, 1);
        qreal currentSpanEndT = LOT_RemapValue(currentEndLength, subpathBeginningLength, subpathEndLength, 0, 1);

        // At this point currentSpan start and end T can be less than 0 or greater than 1

        if (subpath->type == kCGPathElementAddLineToPoint) {

          if (currentSpanStartT >= 0) {
            // The current drawable span either starts with this subpath or along this subpath.
            // If this is the middle of a segment then currentSpanStartT would be less than 0
            if (currentSpanStartT > 0) {
              currentPoint = LOT_PointInLine(currentPoint, subpath->endPoint, currentSpanStartT);
            }
            LOT_moveToPoint(currentPoint);
            // Now we are ready to draw a line
          }

          QPointF toPoint = subpath->endPoint;
          if (currentSpanEndT < 1) {
            // The end of the span is inside of the current subpath. Find it.
            toPoint = LOT_PointInLine(currentPoint, subpath->endPoint, currentSpanEndT);
          }
          LOT_addLineToPoint(toPoint);
          currentPoint = toPoint;
        } else if (subpath->type == kCGPathElementAddCurveToPoint) {

          QPointF cp1, cp2, end;
          cp1 = subpath->controlPoint1;
          cp2 = subpath->controlPoint2;
          end = subpath->endPoint;

          if (currentSpanStartT >= 0) {
            // The current drawable span either starts with this subpath or along this subpath.
            // If this is the middle of a segment then currentSpanStartT would be less than 0
            // Beginning of a segment Move start point and calculate cp1 and 2 is necessary
            if (currentSpanStartT > 0) {
              QPointF A = LOT_PointInLine(currentPoint, cp1, currentSpanStartT);
              QPointF B = LOT_PointInLine(cp1, cp2, currentSpanStartT);
              QPointF C = LOT_PointInLine(cp2, end, currentSpanStartT);
              QPointF D = LOT_PointInLine(A, B, currentSpanStartT);
              QPointF E = LOT_PointInLine(B, C, currentSpanStartT);
              QPointF F = LOT_PointInLine(D, E, currentSpanStartT);
              currentPoint = F;
              cp1 = E;
              cp2 = C;
              currentSpanEndT = LOT_RemapValue(currentSpanEndT, currentSpanStartT, 1, 0, 1);
            }
            LOT_moveToPoint(currentPoint);
          }

          if (currentSpanEndT < 1) {
            QPointF A = LOT_PointInLine(currentPoint, cp1, currentSpanEndT);
            QPointF B = LOT_PointInLine(cp1, cp2, currentSpanEndT);
            QPointF C = LOT_PointInLine(cp2, end, currentSpanEndT);
            QPointF D = LOT_PointInLine(A, B, currentSpanEndT);
            QPointF E = LOT_PointInLine(B, C, currentSpanEndT);
            QPointF F = LOT_PointInLine(D, E, currentSpanEndT);
            cp1 = A;
            cp2 = D;
            end = F;
          }
          LOT_addCurveToPoint(end, cp1, cp2);
        }

        if (currentSpanEndT <= 1) {
          // We have possibly reached the end.
          // Current From and To will possibly need to be reset.
          if (fromLength < toLength) {
              while (subpath) {
                  LOT_Subpath *nextNode = subpath->nextSubpath;
                  subpath->nextSubpath = NULL;
                  free(subpath);
                  subpath = nextNode;
              }
              break;
          } else {
            currentStartLength = fromLength;
            currentEndLength = totalLength;
            if (fromLength < (subpathBeginningLength + pathLength) &&
                fromLength > subpathBeginningLength &&
                currentSpanEndT < 1) {
              // Loop over this subpath one more time.
              // In this case the path start and end trim fall within this subpath bounds
              continue;
            }
          }
        }
      }
      currentPoint = subpath->endPoint;
      subpathBeginningLength = subpathEndLength;

      LOT_Subpath *nextNode = subpath->nextSubpath;
      subpath->nextSubpath = NULL;
      free(subpath);
      subpath = nextNode;
    }
}

void LOTBezierPath::LOT_applyTransform(const QTransform &transform)
{
//    CGMutablePathRef mutablePath = CGPathCreateMutable();
//    CGPathAddPath(mutablePath, &transform, _path);
//    CGPathRelease(_path);
//    _path = mutablePath;
    Q_ASSERT(transform.isAffine());
    _path = transform.map(_path);
}

qreal LOTBezierPath::length() const
{
    return _length;
}

QPainterPath LOTBezierPath::CGPath() const
{
    return _path;
}

QPointF LOTBezierPath::currentPoint() const
{
    QPointF previousPoint = tailSubpath_ ? tailSubpath_->endPoint : QPointF();
    return previousPoint;
}

bool LOTBezierPath::isEmpty() const
{
    return _path.isEmpty();
}

QRectF LOTBezierPath::bounds() const
{
    return _path.boundingRect();
}

void LOTBezierPath::_clearPathData()
{
    _length = 0;
    subpathStartPoint_ = QPointF();
    _path = QPainterPath();
}

bool LOTBezierPath::containsPoint(const QPointF &point) const
{
    Q_ASSERT(false);
//    CGPathContainsPoint(_path, NULL, point.toCGPoint(), usesEvenOddFillRule);
    return _path.contains(point);
}

void LOTBezierPath::setWithCGPath(CGPathRef path)
{
    lot_enumeratePath(path, ^(const CGPathElement *element) {
      switch (element->type) {
        case kCGPathElementMoveToPoint: {
          QPointF point = QPointF::fromCGPoint(element ->points[0]);
          LOT_moveToPoint(point);
          break;
        }
        case kCGPathElementAddLineToPoint: {
          QPointF point = QPointF::fromCGPoint(element ->points[0]);
          LOT_addLineToPoint(point);
          break;
        }
        case kCGPathElementAddQuadCurveToPoint: {
          break;
        }
        case kCGPathElementAddCurveToPoint: {
          QPointF point1 = QPointF::fromCGPoint(element->points[0]);
          QPointF point2 = QPointF::fromCGPoint(element->points[1]);
          QPointF point3 = QPointF::fromCGPoint(element->points[2]);
          LOT_addCurveToPoint(point3, point1, point2);
          break;
        }
        case kCGPathElementCloseSubpath: {
          LOT_closePath();
          break;
        }
      }
    });
}

void LOTBezierPath::addSubpathWithType(CGPathElementType type, qreal length, const QPointF &endPoint, const QPointF &controlPoint1, const QPointF &controlPoint2)
{
    LOT_Subpath *subPath = new LOT_Subpath;
    subPath->type = type;
    subPath->length = length;
    subPath->endPoint = endPoint;
    subPath->controlPoint1 = controlPoint1;
    subPath->controlPoint2 = controlPoint2;
    subPath->nextSubpath = NULL;
    if (tailSubpath_ == NULL) {
      headSubpath_ = subPath;
      tailSubpath_ = subPath;
    } else {
      tailSubpath_->nextSubpath = subPath;
      tailSubpath_ = subPath;
    }
}

void LOTBezierPath::removeAllSubpaths()
{
    LOT_Subpath *node = headSubpath_;
    while (node) {
      LOT_Subpath *nextNode = node->nextSubpath;
      node->nextSubpath = NULL;
      free(node);
      node = nextNode;
    }
    headSubpath_ = NULL;
    tailSubpath_ = NULL;
}

LOT_Subpath *LOTBezierPath::headSubpath() const
{
    return headSubpath_;
}
