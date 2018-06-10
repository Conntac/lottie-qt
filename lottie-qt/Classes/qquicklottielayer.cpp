#include "qquicklottielayer.h"

QQuickLottieLayer::QQuickLottieLayer()
{
}

//QQuickLottieLayer::QQuickLottieLayer(const QSharedPointer<QQuickLottieLayer> &layer)
//{
//}

QQuickLottieLayer::~QQuickLottieLayer()
{
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

}

