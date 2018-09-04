#ifndef QQUICKLOTTIELAYER_H
#define QQUICKLOTTIELAYER_H

#include "lotbase.h"

#include <QColor>
#include <QString>
#include <QRectF>
#include <QSharedPointer>

#include <qquickshape_p.h>

class QQuickLottieLayer : public LOTBase // CALayer
{
public:
    QQuickLottieLayer();
    ~QQuickLottieLayer();

    void setFillColor(const QColor &fillColor);
    QColor fillColor() const;

    void setFillRule(Qt::FillRule fillRule);
    Qt::FillRule fillRule() const;

    void setOpacity(qreal opacity);
    qreal opacity() const;

    void setCapStyle(Qt::PenCapStyle capStyle);
    Qt::PenCapStyle capStyle() const;

    void setHidden(bool hidden);
    bool hidden() const;

    void setTransform(const QTransform &transform);
    QTransform transform() const;

    void setPath(const QPainterPath &path);
    QPainterPath path() const;

    void setStrokeColor(const QColor &strokeColor);
    QColor strokeColor() const;

    void setStrokeWidth(qreal strokeWidth);
    qreal strokeWidth() const;

    void setJoinStyle(Qt::PenJoinStyle joinStyle);
    Qt::PenJoinStyle joinStyle() const;

    void setStrokeStyle(Qt::PenStyle strokeStyle);
    Qt::PenStyle strokeStyle() const;

    void setMiterLimit(int miterLimit);
    int miterLimit() const;

    void setDashPattern(const QVector<qreal> &dashPattern);
    QVector<qreal> dashPattern() const;

    void setDashOffset(qreal dashOffset);
    qreal dashOffset() const;

    void setFillGradient(QQuickShapeGradient *fillGradient);
    QQuickShapeGradient *fillGradient() const;

    QRectF bounds;

//    QQuickPath *path = nullptr;

    bool masksToBounds = false;
    QSharedPointer<QQuickLottieLayer> mask;

    QVariantMap actions;

    QStringList animationKeys;
    QSharedPointer<QQuickLottieLayer> presentationLayer;
//    bool hidden = false;

//    QVector<qreal> lineDashPattern;

    QPointF position;
    QPointF anchorPoint;
//    QTransform transform;

    // Properties
    QColor backgroundColor;
    QColor borderColor;
    qreal borderWidth = 1.0;
//    QString lineCap;
//    QString lineJoin;

    qreal lineDashPhase = 0.0;
//    QColor strokeColor;
//    qreal lineWidth = 0.0;

//    QColor fillColor;
//    QString fillRule;
//    qreal opacity = 1.0;

    // Functions
    void addSublayer(const QSharedPointer<QQuickLottieLayer> &sublayer);
    void insertSublayer(const QSharedPointer<QQuickLottieLayer> &sublayer, int index);

    // TODO: Return some kind of animation?
    virtual void actionForKey(const QString &event);

    virtual void display();

    QQuickLottieLayer *parentLayer = nullptr;
    QList<QSharedPointer<QQuickLottieLayer>> sublayers;

private:
    Q_DISABLE_COPY(QQuickLottieLayer)

    QColor m_fillColor = Qt::transparent;
    Qt::FillRule m_fillRule = Qt::OddEvenFill;
    qreal m_opacity = 1.0;
    Qt::PenCapStyle m_capStyle = Qt::FlatCap;
    bool m_hidden = false;
    QTransform m_transform;
    QPainterPath m_path;
    QColor m_strokeColor = Qt::transparent;
    qreal m_strokeWidth = 0.0;
    Qt::PenJoinStyle m_joinStyle = Qt::MiterJoin;
    int m_miterLimit = 0;
    Qt::PenStyle m_strokeStyle = Qt::SolidLine;
    QVector<qreal> m_dashPattern;
    qreal m_dashOffset = 0.0;
    QQuickShapeGradient *m_fillGradient = nullptr;
};

class QQuickLottieShapeLayer : public QQuickLottieLayer // CAShapeLayer
{
public:
    QQuickLottieShapeLayer();
};

class QQuickLottieReplicatorLayer : public QQuickLottieLayer // CAReplicatorLayer
{
public:
    QQuickLottieReplicatorLayer();

    int instanceCount = 0;
    QTransform instanceTransform;

    qreal instanceAlphaOffset = 0.0;
};

#endif // QQUICKLOTTIELAYER_H
