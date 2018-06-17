
#import <CoreGraphics/CoreGraphics.h>

#include <QPointF>
#include <QRectF>

//
// Core Graphics Geometry Additions
//

extern const QSizeF QSizeFMax;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

QRectF LOT_RectIntegral(QRectF rect);

// Centering

// Returns a rectangle of the given size, centered at a point
QRectF LOT_RectCenteredAtPoint(CGPoint center, QSizeF size, bool integral);

// Returns the center point of a QRectF
QPointF LOT_RectGetCenterPoint(const QRectF &rect);

// Insetting

// Inset the rectangle on a single edge
QRectF LOT_RectInsetLeft(QRectF rect, qreal inset);
QRectF LOT_RectInsetRight(QRectF rect, qreal inset);
QRectF LOT_RectInsetTop(QRectF rect, qreal inset);
QRectF LOT_RectInsetBottom(QRectF rect, qreal inset);

// Inset the rectangle on two edges
QRectF LOT_RectInsetHorizontal(QRectF rect, qreal leftInset, qreal rightInset);
QRectF LOT_RectInsetVertical(QRectF rect, qreal topInset, qreal bottomInset);

// Inset the rectangle on all edges
QRectF LOT_RectInsetAll(QRectF rect, qreal leftInset, qreal rightInset, qreal topInset, qreal bottomInset);

// Framing

// Returns a rectangle of size framed in the center of the given rectangle
QRectF LOT_RectFramedCenteredInRect(QRectF rect, QSizeF size, bool integral);

// Returns a rectangle of size framed in the given rectangle and inset
QRectF LOT_RectFramedLeftInRect(QRectF rect, QSizeF size, qreal inset, bool integral);
QRectF LOT_RectFramedRightInRect(QRectF rect, QSizeF size, qreal inset, bool integral);
QRectF LOT_RectFramedTopInRect(QRectF rect, QSizeF size, qreal inset, bool integral);
QRectF LOT_RectFramedBottomInRect(QRectF rect, QSizeF size, qreal inset, bool integral);

QRectF LOT_RectFramedTopLeftInRect(QRectF rect, QSizeF size, qreal insetWidth, qreal insetHeight, bool integral);
QRectF LOT_RectFramedTopRightInRect(QRectF rect, QSizeF size, qreal insetWidth, qreal insetHeight, bool integral);
QRectF LOT_RectFramedBottomLeftInRect(QRectF rect, QSizeF size, qreal insetWidth, qreal insetHeight, bool integral);
QRectF LOT_RectFramedBottomRightInRect(QRectF rect, QSizeF size, qreal insetWidth, qreal insetHeight, bool integral);

// Divides a rect into sections and returns the section at specified index

//QRectF LOT_RectDividedSection(QRectF rect, NSInteger sections, NSInteger index, QRectFEdge fromEdge);

// Returns a rectangle of size attached to the given rectangle
QRectF LOT_RectAttachedLeftToRect(QRectF rect, QSizeF size, qreal margin, bool integral);
QRectF LOT_RectAttachedRightToRect(QRectF rect, QSizeF size, qreal margin, bool integral);
QRectF LOT_RectAttachedTopToRect(QRectF rect, QSizeF size, qreal margin, bool integral);
QRectF LOT_RectAttachedBottomToRect(QRectF rect, QSizeF size, qreal margin, bool integral);

QRectF LOT_RectAttachedBottomLeftToRect(QRectF rect, QSizeF size, qreal marginWidth, qreal marginHeight, bool integral);
QRectF LOT_RectAttachedBottomRightToRect(QRectF rect, QSizeF size, qreal marginWidth, qreal marginHeight, bool integral);
QRectF LOT_RectAttachedTopRightToRect(QRectF rect, QSizeF size, qreal marginWidth, qreal marginHeight, bool integral);
QRectF LOT_RectAttachedTopLeftToRect(QRectF rect, QSizeF size, qreal marginWidth, qreal marginHeight, bool integral);

bool LOT_CGPointIsZero(CGPoint point);

// Combining
// Adds all values of the 2nd rect to the first rect
QRectF LOT_RectAddRect(QRectF rect, QRectF other);
QRectF LOT_RectAddPoint(QRectF rect, CGPoint point);
QRectF LOT_RectAddSize(QRectF rect, QSizeF size);
QRectF LOT_RectBounded(QRectF rect);

QPointF LOT_PointAddedToPoint(const QPointF &point1, const QPointF &point2);

QRectF LOT_RectSetHeight(QRectF rect, qreal height);

qreal LOT_PointDistanceFromPoint(const QPointF &point1, const QPointF &point2);
qreal LOT_DegreesToRadians(qreal degrees);

qreal LOT_RemapValue(qreal value, qreal low1, qreal high1, qreal low2, qreal high2 );
QPointF LOT_PointByLerpingPoints(const QPointF &point1, const QPointF &point2, qreal value);

QPointF LOT_PointInLine(const QPointF &A, const QPointF &B, qreal T);
QPointF LOT_PointInCubicCurve(const QPointF &start, const QPointF &cp1, const QPointF &cp2, const QPointF &end, qreal T);

qreal LOT_CubicBezeirInterpolate(const QPointF &P0, const QPointF &P1, const QPointF &P2, const QPointF &P3, qreal x);
qreal LOT_SolveCubic(qreal a, qreal b, qreal c, qreal d);
qreal LOT_SolveQuadratic(qreal a, qreal b, qreal c);
qreal LOT_Squared(qreal f);
qreal LOT_Cubed(qreal f);
qreal LOT_CubicRoot(qreal f);

qreal LOT_CubicLength(const QPointF &fromPoint, const QPointF &toPoint, const QPointF &controlPoint1, const QPointF &controlPoint2);
qreal LOT_CubicLengthWithPrecision(const QPointF &fromPoint, const QPointF &toPoint, const QPointF &controlPoint1, const QPointF &controlPoint2, qreal iterations);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
