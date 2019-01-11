#include "qquicklottielayer.h"

QQuickLottieLayer::QQuickLottieLayer()
{
}

QQuickLottieLayer::~QQuickLottieLayer()
{
}

void QQuickLottieLayer::setFillColor(const QColor &fillColor)
{
    m_fillColor = fillColor;
}

QColor QQuickLottieLayer::fillColor() const
{
    return m_fillColor;
}

void QQuickLottieLayer::setFillRule(Qt::FillRule fillRule)
{
    m_fillRule = fillRule;
}

Qt::FillRule QQuickLottieLayer::fillRule() const
{
    return m_fillRule;
}

void QQuickLottieLayer::setOpacity(qreal opacity)
{
    m_opacity = opacity;
}

qreal QQuickLottieLayer::opacity() const
{
    return m_opacity;
}

void QQuickLottieLayer::setCapStyle(Qt::PenCapStyle capStyle)
{
    m_capStyle = capStyle;
}

Qt::PenCapStyle QQuickLottieLayer::capStyle() const
{
    return m_capStyle;
}

void QQuickLottieLayer::setHidden(bool hidden)
{
    m_hidden = hidden;
}

bool QQuickLottieLayer::hidden() const
{
    return m_hidden;
}

void QQuickLottieLayer::setTransform(const QTransform &transform)
{
    m_transform = transform;
}

QTransform QQuickLottieLayer::transform() const
{
    return m_transform;
}

void QQuickLottieLayer::setPath(const QPainterPath &path)
{
    m_path = path;
}

QPainterPath QQuickLottieLayer::path() const
{
    return m_path;
}

void QQuickLottieLayer::setStrokeColor(const QColor &strokeColor)
{
    m_strokeColor = strokeColor;
}

QColor QQuickLottieLayer::strokeColor() const
{
    return m_strokeColor;
}

void QQuickLottieLayer::setStrokeWidth(qreal strokeWidth)
{
    m_strokeWidth = strokeWidth;
}

qreal QQuickLottieLayer::strokeWidth() const
{
    return m_strokeWidth;
}

void QQuickLottieLayer::setJoinStyle(Qt::PenJoinStyle joinStyle)
{
    m_joinStyle = joinStyle;
}

Qt::PenJoinStyle QQuickLottieLayer::joinStyle() const
{
    return m_joinStyle;
}

void QQuickLottieLayer::setStrokeStyle(Qt::PenStyle strokeStyle)
{
    m_strokeStyle = strokeStyle;
}

Qt::PenStyle QQuickLottieLayer::strokeStyle() const
{
    return m_strokeStyle;
}

void QQuickLottieLayer::setMiterLimit(int miterLimit)
{
    m_miterLimit = miterLimit;
}

int QQuickLottieLayer::miterLimit() const
{
    return m_miterLimit;
}

void QQuickLottieLayer::setDashPattern(const QVector<qreal> &dashPattern)
{
    m_dashPattern = dashPattern;

    if (dashPattern.isEmpty()) {
        setStrokeStyle(Qt::SolidLine);
    } else {
        setStrokeStyle(Qt::DashLine);
    }
}

QVector<qreal> QQuickLottieLayer::dashPattern() const
{
    return m_dashPattern;
}

void QQuickLottieLayer::setDashOffset(qreal dashOffset)
{
    m_dashOffset = dashOffset;
}

qreal QQuickLottieLayer::dashOffset() const
{
    return m_dashOffset;
}

void QQuickLottieLayer::setFillGradient(QQuickShapeGradient *fillGradient)
{
    m_fillGradient = fillGradient;
}

QQuickShapeGradient *QQuickLottieLayer::fillGradient() const
{
    return m_fillGradient;
}

void QQuickLottieLayer::addSublayer(const QSharedPointer<QQuickLottieLayer> &sublayer)
{
    Q_ASSERT(!sublayer->parentLayer);
    sublayer->parentLayer = this;

    sublayers.append(sublayer);
}

void QQuickLottieLayer::insertSublayer(const QSharedPointer<QQuickLottieLayer> &sublayer, int index)
{
    Q_ASSERT(!sublayer->parentLayer);
    sublayer->parentLayer = this;

    sublayers.insert(index, sublayer);
}

void QQuickLottieLayer::actionForKey(const QString &event)
{

}

void QQuickLottieLayer::display()
{
    int blub=4;
}

QQuickLottieShapeLayer::QQuickLottieShapeLayer()
{
//    Q_ASSERT(false);
}

QQuickLottieReplicatorLayer::QQuickLottieReplicatorLayer()
{
//    Q_ASSERT(false);
}

