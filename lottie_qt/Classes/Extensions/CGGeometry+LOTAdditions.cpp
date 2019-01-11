
#include "CGGeometry+LOTAdditions.h"
#include <math.h>
#include <QtMath>

const QSizeF QSizeFMax = {std::numeric_limits<qreal>::min(), std::numeric_limits<qreal>::max()};
//
// Core Graphics Geometry Additions
//

// QRectFIntegral returns a rectangle with the smallest integer values for its origin and size that contains the source rectangle.
// For a rect with .origin={5, 5.5}, .size=(10, 10), it will return .origin={5,5}, .size={10, 11};
// LOT_RectIntegral will return {5,5}, {10, 10}.
QRectF LOT_RectIntegral(QRectF rect) {
  return QRectF(rintf(rect.x()), rintf(rect.y()),
                ceilf(rect.width()), ceil(rect.height()));
}

//
// Centering

// Returns a rectangle of the given size, centered at a point

QRectF LOT_RectCenteredAtPoint(QPointF center, QSizeF size, bool integral) {
  QRectF result;
  result.setX(center.x() - 0.5f * size.width());
  result.setY(center.y() - 0.5f * size.height());
  result.setSize(size);
  
  if (integral) { result = LOT_RectIntegral(result); }
  return result;
}

// Returns the center point of a QRectF
QPointF LOT_RectGetCenterPoint(const QRectF &rect) {
    return rect.center();
}

//
// Insetting

// Inset the rectangle on a single edge

QRectF LOT_RectInsetLeft(QRectF rect, qreal inset) {
  rect.adjust(inset, 0, -inset, 0);
  return rect;
}

QRectF LOT_RectInsetRight(QRectF rect, qreal inset) {
  rect.adjust(0, 0, -inset, 0);
  return rect;
}

QRectF LOT_RectInsetTop(QRectF rect, qreal inset) {
  rect.adjust(0, inset, 0, -inset);
  return rect;
}

QRectF LOT_RectInsetBottom(QRectF rect, qreal inset) {
  rect.adjust(0, 0, 0, -inset);
  return rect;
}

// Inset the rectangle on two edges

QRectF LOT_RectInsetHorizontal(QRectF rect, qreal leftInset, qreal rightInset) {
  rect.adjust(leftInset, 0, -(leftInset + rightInset), 0);
  return rect;
}

QRectF LOT_RectInsetVertical(QRectF rect, qreal topInset, qreal bottomInset) {
  rect.adjust(0, topInset, 0, -(topInset + bottomInset));
  return rect;
}

// Inset the rectangle on all edges

QRectF LOT_RectInsetAll(QRectF rect, qreal leftInset, qreal rightInset, qreal topInset, qreal bottomInset) {
  rect.adjust(leftInset, topInset, -(leftInset + rightInset), -(topInset + bottomInset));
  return rect;
}

//
// Framing

// Returns a rectangle of size framed in the center of the given rectangle

//QRectF LOT_RectFramedCenteredInRect(QRectF rect, QSizeF size, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rintf(0.5f * (rect.size.width - size.width));
//  result.origin.y = rect.origin.y + rintf(0.5f * (rect.size.height - size.height));
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

// Returns a rectangle of size framed in the given rectangle and inset

//QRectF LOT_RectFramedLeftInRect(QRectF rect, QSizeF size, qreal inset, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + inset;
//  result.origin.y = rect.origin.y + rintf(0.5f * (rect.size.height - size.height));
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectFramedRightInRect(QRectF rect, QSizeF size, qreal inset, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rect.size.width - size.width - inset;
//  result.origin.y = rect.origin.y + rintf(0.5f * (rect.size.height - size.height));
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectFramedTopInRect(QRectF rect, QSizeF size, qreal inset, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rintf(0.5f * (rect.size.width - size.width));
//  result.origin.y = rect.origin.y + inset;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectFramedBottomInRect(QRectF rect, QSizeF size, qreal inset, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rintf(0.5f * (rect.size.width - size.width));
//  result.origin.y = rect.origin.y + rect.size.height - size.height - inset;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectFramedTopLeftInRect(QRectF rect, QSizeF size, qreal insetWidth, qreal insetHeight, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + insetWidth;
//  result.origin.y = rect.origin.y + insetHeight;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectFramedTopRightInRect(QRectF rect, QSizeF size, qreal insetWidth, qreal insetHeight, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rect.size.width - size.width - insetWidth;
//  result.origin.y = rect.origin.y + insetHeight;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectFramedBottomLeftInRect(QRectF rect, QSizeF size, qreal insetWidth, qreal insetHeight, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + insetWidth;
//  result.origin.y = rect.origin.y + rect.size.height - size.height - insetHeight;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectFramedBottomRightInRect(QRectF rect, QSizeF size, qreal insetWidth, qreal insetHeight, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rect.size.width - size.width - insetWidth;
//  result.origin.y = rect.origin.y + rect.size.height - size.height - insetHeight;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

// Returns a rectangle of size attached to the given rectangle

//QRectF LOT_RectAttachedLeftToRect(QRectF rect, QSizeF size, qreal margin, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x - size.width - margin;
//  result.origin.y = rect.origin.y + rintf(0.5f * (rect.size.height - size.height));
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectAttachedRightToRect(QRectF rect, QSizeF size, qreal margin, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rect.size.width + margin;
//  result.origin.y = rect.origin.y + rintf(0.5f * (rect.size.height - size.height));
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectAttachedTopToRect(QRectF rect, QSizeF size, qreal margin, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rintf(0.5f * (rect.size.width - size.width));
//  result.origin.y = rect.origin.y - size.height - margin;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectAttachedTopLeftToRect(QRectF rect, QSizeF size, qreal marginWidth, qreal marginHeight, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + marginWidth;
//  result.origin.y = rect.origin.y - size.height - marginHeight;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectAttachedTopRightToRect(QRectF rect, QSizeF size, qreal marginWidth, qreal marginHeight, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rect.size.width - size.width - marginWidth;
//  result.origin.y = rect.origin.y - rect.size.height - marginHeight;
//  result.size = size;

//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectAttachedBottomToRect(QRectF rect, QSizeF size, qreal margin, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rintf(0.5f * (rect.size.width - size.width));
//  result.origin.y = rect.origin.y + rect.size.height + margin;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectAttachedBottomLeftToRect(QRectF rect, QSizeF size, qreal marginWidth, qreal marginHeight, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + marginWidth;
//  result.origin.y = rect.origin.y + rect.size.height + marginHeight;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

//QRectF LOT_RectAttachedBottomRightToRect(QRectF rect, QSizeF size, qreal marginWidth, qreal marginHeight, bool integral) {
//  QRectF result;
//  result.origin.x = rect.origin.x + rect.size.width - size.width - marginWidth;
//  result.origin.y = rect.origin.y + rect.size.height + marginHeight;
//  result.size = size;
  
//  if (integral) { result = LOT_RectIntegral(result); }
//  return result;
//}

// Divides a rect into sections and returns the section at specified index

//QRectF LOT_RectDividedSection(QRectF rect, NSInteger sections, NSInteger index, QRectFEdge fromEdge) {
//  if (sections == 0) {
//    return QRectFZero;
//  }
//  QRectF r = rect;
//  if (fromEdge == QRectFMaxXEdge || fromEdge == QRectFMinXEdge) {
//    r.size.width = rect.size.width / sections;
//    r.origin.x += r.size.width * index;
//  } else {
//    r.size.height = rect.size.height / sections;
//    r.origin.y += r.size.height * index;
//  }
//  return r;
//}


//QRectF LOT_RectAddRect(QRectF rect, QRectF other) {
//  return QRectFMake(rect.origin.x + other.origin.x, rect.origin.y + other.origin.y,
//                    rect.size.width + other.size.width, rect.size.height + other.size.height);
//}

//QRectF LOT_RectAddPoint(QRectF rect, QPointF point) {
//  return QRectFMake(rect.origin.x + point.x, rect.origin.y + point.y,
//                    rect.size.width, rect.size.height);
//}

//QRectF LOT_RectAddSize(QRectF rect, QSizeF size) {
//  return QRectFMake(rect.origin.x, rect.origin.y,
//                    rect.size.width + size.width, rect.size.height + size.height);
//}

//QRectF LOT_RectBounded(QRectF rect) {
//  QRectF returnRect = rect;
//  returnRect.origin = QPointFZero;
//  return returnRect;
//}

QPointF LOT_PointAddedToPoint(const QPointF &point1, const QPointF &point2) {
//  QPointF returnPoint = point1;
//  returnPoint.x += point2.x;
//  returnPoint.y += point2.y;
  return point1 + point2;
}

//QRectF LOT_RectSetHeight(QRectF rect, qreal height) {
//  return QRectFMake(rect.origin.x, rect.origin.y, rect.size.width, height);
//}

qreal LOT_DegreesToRadians(qreal degrees) {
  return degrees * M_PI / 180;
}

qreal LOT_PointDistanceFromPoint(const QPointF &point1, const QPointF &point2) {
  qreal xDist = (point2.x() - point1.x());
  qreal yDist = (point2.y() - point1.y());
  qreal distance = sqrt((xDist * xDist) + (yDist * yDist));
  return distance;
}

qreal LOT_RemapValue(qreal value, qreal low1, qreal high1, qreal low2, qreal high2 ) {
  return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

QPointF LOT_PointByLerpingPoints(const QPointF &point1, const QPointF &point2, qreal value) {
  qreal xDiff = point2.x() - point1.x();
  qreal yDiff = point2.y() - point1.y();
  QPointF transposed(fabs(xDiff), fabs(yDiff));
  QPointF returnPoint;
  if (xDiff == 0 || yDiff == 0) {
    returnPoint.setX(xDiff == 0 ? point1.x() : LOT_RemapValue(value, 0, 1, point1.x(), point2.x()));
    returnPoint.setY(yDiff == 0 ? point1.y() : LOT_RemapValue(value, 0, 1, point1.y(), point2.y()));
  } else {
    qreal rx = transposed.x() / transposed.y();
    qreal yLerp = LOT_RemapValue(value, 0, 1, 0, transposed.y());
    qreal xLerp = yLerp * rx;
    QPointF interpolatedPoint(point2.x() < point1.x() ? xLerp * -1 : xLerp,
                              point2.y() < point1.y() ? yLerp * -1 : yLerp);
    returnPoint = LOT_PointAddedToPoint(point1, interpolatedPoint);
  }
  return returnPoint;
}

QPointF LOT_PointInLine(const QPointF &A, const QPointF &B, qreal T) {
  QPointF C;
  C.setX(A.x() - ((A.x() - B.x()) * T));
  C.setY(A.y() - ((A.y() - B.y()) * T));
  return C;
}

qreal LOT_CubicBezierGetY(QPointF cp1, QPointF cp2, qreal T) {
//       (1-x)^3 * y0 + 3*(1-x)^2 * x * y1 + 3*(1-x) * x^2 * y2 + x^3 * y3
  return 3 * qPow(1.f - T, 2.f) * T * cp1.y() + 3.f * (1.f - T) * qPow(T, 2.f) * cp2.y() + qPow(T, 3.f);
}

QPointF LOT_PointInCubicCurve(const QPointF &start, const QPointF &cp1, const QPointF &cp2, const QPointF &end, qreal T) {
  QPointF A = LOT_PointInLine(start, cp1, T);
  QPointF B = LOT_PointInLine(cp1, cp2, T);
  QPointF C = LOT_PointInLine(cp2, end, T);
  QPointF D = LOT_PointInLine(A, B, T);
  QPointF E = LOT_PointInLine(B, C, T);
  QPointF F = LOT_PointInLine(D, E, T);
  return F;
}

qreal LOT_SolveCubic(qreal a, qreal b, qreal c, qreal d) {
  if (a == 0) return LOT_SolveQuadratic(b, c, d);
  if (d == 0) return 0;
  
  b /= a;
  c /= a;
  d /= a;
  qreal q = (3.0 * c - LOT_Squared(b)) / 9.0;
  qreal r = (-27.0 * d + b * (9.0 * c - 2.0 * LOT_Squared(b))) / 54.0;
  qreal disc = LOT_Cubed(q) + LOT_Squared(r);
  qreal term1 = b / 3.0;
  
  if (disc > 0) {
    double s = r + sqrtf(disc);
    s = (s < 0) ? - LOT_CubicRoot(-s) : LOT_CubicRoot(s);
    double t = r - sqrtf(disc);
    t = (t < 0) ? - LOT_CubicRoot(-t) : LOT_CubicRoot(t);
    
    double result = -term1 + s + t;
    if (result >= 0 && result <= 1) return result;
  } else if (disc == 0) {
    double r13 = (r < 0) ? - LOT_CubicRoot(-r) : LOT_CubicRoot(r);
    
    double result = -term1 + 2.0 * r13;
    if (result >= 0 && result <= 1) return result;
    
    result = -(r13 + term1);
    if (result >= 0 && result <= 1) return result;
  } else {
    q = -q;
    double dum1 = q * q * q;
    dum1 = acosf(r / sqrtf(dum1));
    double r13 = 2.0 * sqrtf(q);
    
    double result = -term1 + r13 * cos(dum1 / 3.0);
    if (result >= 0 && result <= 1) return result;
    
    result = -term1 + r13 * cos((dum1 + 2.0 * M_PI) / 3.0);
    if (result >= 0 && result <= 1) return result;
    
    result = -term1 + r13 * cos((dum1 + 4.0 * M_PI) / 3.0);
    if (result >= 0 && result <= 1) return result;
  }
  
  return -1;
}

qreal LOT_SolveQuadratic(qreal a, qreal b, qreal c) {
  qreal result = (-b + sqrtf(LOT_Squared(b) - 4 * a * c)) / (2 * a);
  if (result >= 0 && result <= 1) return result;
  
  result = (-b - sqrtf(LOT_Squared(b) - 4 * a * c)) / (2 * a);
  if (result >= 0 && result <= 1) return result;
  
  return -1;
}

qreal LOT_Squared(qreal f) { return f * f; }

qreal LOT_Cubed(qreal f) { return f * f * f; }

qreal LOT_CubicRoot(qreal f) { return powf(f, 1.0 / 3.0); }

qreal LOT_CubicBezeirInterpolate(const QPointF &P0, const QPointF &P1, const QPointF &P2, const QPointF &P3, qreal x) {
  qreal t;
  if (x == P0.x()) {
    // Handle corner cases explicitly to prevent rounding errors
    t = 0;
  } else if (x == P3.x()) {
    t = 1;
  } else {
    // Calculate t
    qreal a = -P0.x() + 3 * P1.x() - 3 * P2.x() + P3.x();
    qreal b = 3 * P0.x() - 6 * P1.x() + 3 * P2.x();
    qreal c = -3 * P0.x() + 3 * P1.x();
    qreal d = P0.x() - x;
    qreal tTemp = LOT_SolveCubic(a, b, c, d);
    if (tTemp == -1) return -1;
    t = tTemp;
  }
  
  // Calculate y from t
  return LOT_Cubed(1 - t) * P0.y() + 3 * t * LOT_Squared(1 - t) * P1.y() + 3 * LOT_Squared(t) * (1 - t) * P2.y() + LOT_Cubed(t) * P3.y();
}

qreal LOT_CubicLengthWithPrecision(const QPointF &fromPoint, const QPointF &toPoint, const QPointF &controlPoint1, const QPointF &controlPoint2, qreal iterations) {
  qreal length = 0;
  QPointF previousPoint = fromPoint;
  iterations = ceilf(iterations);
  for (int i = 1; i <= iterations; ++i) {
    float s = (float)i  / iterations;
    
    QPointF p = LOT_PointInCubicCurve(fromPoint, controlPoint1, controlPoint2, toPoint, s);
    
    length += LOT_PointDistanceFromPoint(previousPoint, p);
    previousPoint = p;
  }
  return length;
}

qreal LOT_CubicLength(const QPointF &fromPoint, const QPointF &toPoint, const QPointF &controlPoint1, const QPointF &controlPoint2) {
  return LOT_CubicLengthWithPrecision(fromPoint, toPoint, controlPoint1, controlPoint2, 20);
}

//bool LOT_QPointFIsZero(QPointF point) {
//  return QPointFEqualToPoint(point, QPointFZero);
//}
