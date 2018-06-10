#ifndef QQUICKLOTTIELAYER_H
#define QQUICKLOTTIELAYER_H

#include "lotbase.h"

#include <QColor>
#include <QString>
#include <QRectF>
#include <QSharedPointer>

#include <qquickshape_p.h>

class QQuickLottieLayer : public QQuickShapePath
        , public LOTBase // CALayer
{
public:
    QQuickLottieLayer();
//    explicit QQuickLottieLayer(const QSharedPointer<QQuickLottieLayer> &layer);
    ~QQuickLottieLayer();

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
};

class QQuickLottieShapeLayer : public QQuickLottieLayer // CAShapeLayer
{
public:
};

class QQuickLottieReplicatorLayer : public QQuickLottieLayer // CAReplicatorLayer
{
public:
    int instanceCount = 0;
    QTransform instanceTransform;

    qreal instanceAlphaOffset = 0.0;
};

#endif // QQUICKLOTTIELAYER_H
