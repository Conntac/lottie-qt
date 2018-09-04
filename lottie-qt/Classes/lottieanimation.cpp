#include "lottieanimation.h"

#include <QLoggingCategory>
#include <QQmlEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPropertyAnimation>

#include "qquickshape_p.h"
#include "qquickshapegenericrenderer_p.h"

//#include "LOTAnimationView.h"

#include "LOTComposition.h"
#include "LOTCompositionContainer.h"

#include "LOTBlockCallback.h"

Q_LOGGING_CATEGORY(logLottieAnimation, "lottie.qml.animation")

class LottieAnimation::Private
{
public:
    Private(LottieAnimation *q)
    : q(q)
    , renderer(q)
    {
    }

    LottieAnimation *q;

    // Properties
    LottieAnimation::FillMode fillMode = LottieAnimation::PreserveAspectFit;
    LottieAnimation::Status status = LottieAnimation::Null;

    QString errorString;

    qreal currentFrame = 0;
    qreal startFrame = 0.0;
    qreal endFrame = 0.0;
    qreal frameRate = 0.0;
    qreal timeDuration = 0.0;

    QUrl source;

    QPropertyAnimation* animation = nullptr;

    QSharedPointer<LOTComposition> composition;
    QSharedPointer<LOTCompositionContainer> container;

    QQuickShapeGenericRenderer renderer;
    QQuickShapeGenericNode *rootNode = nullptr;
    QSGTransformNode *transformNode = nullptr;

    bool running = false;
    bool clearNodes = false;

    // Functions
    void init();
    void setStatus(LottieAnimation::Status status, const QString &errorString = QString());

    void loadAnimation();
    void loadAnimation(const QByteArray &data);
    void sync();
};

static void walkLayers(int indent, const QSharedPointer<QQuickLottieLayer> &layer, QList<QQuickLottieLayer *> *layers) {
    if (layer->hidden()) {
        return;
    }

    layers->append(layer.data());

    for (QSharedPointer<QQuickLottieLayer> child : layer->sublayers) {
        walkLayers(indent + 1, child, layers);
    }
}

void LottieAnimation::Private::init()
{
    animation = new QPropertyAnimation(q, "currentFrame", q);
}

void LottieAnimation::Private::setStatus(LottieAnimation::Status status, const QString &errorString)
{
    if (this->status != status) {
        this->status = status;
        this->errorString = errorString;

        emit q->statusChanged();
    }
}

void LottieAnimation::Private::loadAnimation()
{
    setStatus(LottieAnimation::Loading);

    bool fromDisk = true;

    composition.clear();
    container.clear();

    QString path = source.toString();
    if (path.startsWith("qrc:")) {
        path.remove(0, 3);
    } else if (source.scheme() == "file") {
        path = source.toLocalFile();
    } else {
        fromDisk = false;

        QNetworkRequest request(source);

        QNetworkAccessManager *mgr = qmlEngine(q)->networkAccessManager();
        QNetworkReply *reply = mgr->get(request);
        QObject::connect(reply, &QNetworkReply::finished, q, [=]() {
            reply->deleteLater();

            if (reply->error() == QNetworkReply::NoError) {
                loadAnimation(reply->readAll());

                setStatus(LottieAnimation::Ready);
            } else {
                qCCritical(logLottieAnimation) << "Unable to open" << reply->url() << ":" << reply->errorString();

                setStatus(LottieAnimation::Error, reply->errorString());
            }
        });
    }

    if (fromDisk) {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly)) {
            loadAnimation(file.readAll());

            setStatus(LottieAnimation::Ready);
        } else {
            qCCritical(logLottieAnimation) << "Unable to open" << path << ":" << file.errorString();

            setStatus(LottieAnimation::Error, file.errorString());
        }
    }
}

void LottieAnimation::Private::loadAnimation(const QByteArray &data)
{
    composition = composition.create();
    if (composition->loadFromData(data)) {
        container = container.create(nullptr, nullptr, composition->layerGroup, composition->assetGroup);

        startFrame = composition->startFrame;
        endFrame = composition->endFrame;
        frameRate = composition->framerate;
        timeDuration = composition->timeDuration;

        animation->stop();
        animation->setDuration(static_cast<int>(timeDuration * 1000));
        animation->setStartValue(startFrame);
        animation->setEndValue(endFrame);

        if (running) {
            animation->start();
        }

        emit q->startFrameChanged();
        emit q->endFrameChanged();
        emit q->frameRateChanged();
        emit q->timeDurationChanged();
        emit q->currentFrameChanged();

        // Clear all known render nodes in the next frame
        clearNodes = true;

        // Update the item now
        q->polish();
    }
}

void LottieAnimation::Private::sync()
{
    if (!container) {
        return;
    }

    container->display();

    // Collect all layers as flat items
    QList<QQuickLottieLayer *> flatLayers;
    walkLayers(0, container, &flatLayers);

    const int count = flatLayers.size();

//    qCDebug(logLottieAnimation) << "Collected" << count << "layers";

    renderer.beginSync(count);

    for(int i=0; i < count; ++i) {
        QQuickLottieLayer *layer = flatLayers.at(i);

        qreal completeOpacity = 1.0;

        QList<QTransform> transformTree;
        QQuickLottieLayer *p = layer;
        while (p) {
            transformTree.append(p->transform());

            completeOpacity *= p->opacity();

            p = p->parentLayer;
        }

        QTransform absoluteTransform;
        for(QTransform t : transformTree) {
            absoluteTransform *= t;
        }

        renderer.setTransform(i, absoluteTransform);
        renderer.setHidden(i, layer->hidden());
        renderer.setOpacity(i, layer->opacity());
        renderer.setOpacity(i, /*layer->opacity()*/ completeOpacity);
        renderer.setPath(i, layer->path());
        renderer.setStrokeColor(i, layer->strokeColor());
        renderer.setStrokeWidth(i, layer->strokeWidth());
        renderer.setFillColor(i, layer->fillColor());
        renderer.setFillRule(i, static_cast<QQuickShapePath::FillRule>(layer->fillRule()));
        renderer.setJoinStyle(i, static_cast<QQuickShapePath::JoinStyle>(layer->joinStyle()), layer->miterLimit());
        renderer.setCapStyle(i, static_cast<QQuickShapePath::CapStyle>(layer->capStyle()));

        // Make the dash pattern even
        QVector<qreal> dashPattern = layer->dashPattern();
        if (dashPattern.size() % 2) {
//            dashPattern.append(dashPattern.last());
            debugPainterPath(layer->path());
        }
        renderer.setStrokeStyle(i, static_cast<QQuickShapePath::StrokeStyle>(layer->strokeStyle()), layer->dashOffset(), dashPattern);
        renderer.setFillGradient(i, layer->fillGradient());
    }

    renderer.endSync(false);

    // Now update the render tree
    q->update();
}

LottieAnimation::LottieAnimation(QQuickItem *parent)
: QQuickItem(parent)
, d(new Private(this))
{
    d->init();

    setFlag(ItemHasContents);
}

LottieAnimation::~LottieAnimation()
{
    delete d;
}

void LottieAnimation::setFillMode(LottieAnimation::FillMode fillMode)
{
    if (d->fillMode != fillMode) {
        d->fillMode = fillMode;

        emit fillModeChanged();

        polish();
    }
}

LottieAnimation::FillMode LottieAnimation::fillMode() const
{
    return d->fillMode;
}

LottieAnimation::Status LottieAnimation::status() const
{
    return d->status;
}

QString LottieAnimation::errorString() const
{
    return d->errorString;
}

qreal LottieAnimation::currentFrame() const
{
    if (d->container) {
        return d->container->currentFrame;
    }

    return 0.0;
}

void LottieAnimation::setCurrentFrame(qreal currentFrame)
{
    if (!d->container) {
        return;
    }

    if (qFuzzyCompare(d->container->currentFrame, currentFrame)) {
        return;
    }

    d->container->currentFrame = currentFrame;

    emit currentFrameChanged();

    polish();
}

qreal LottieAnimation::startFrame() const
{
    return d->startFrame;
}

qreal LottieAnimation::endFrame() const
{
    return d->endFrame;
}

qreal LottieAnimation::frameRate() const
{
    return d->frameRate;
}

qreal LottieAnimation::timeDuration() const
{
    return d->timeDuration * 1000;
}

void LottieAnimation::setSource(const QUrl &source)
{
    if (d->source != source) {
        d->source = source;

        d->loadAnimation();

        emit sourceChanged();
    }
}

QUrl LottieAnimation::source() const
{
    return d->source;
}

void LottieAnimation::setIsRunning(bool isRunning)
{
    if (d->running != isRunning) {
        d->running = isRunning;

        if (isRunning && d->container && d->animation->state() != QPropertyAnimation::Running) {
            d->animation->start();
        } else if (!isRunning) {
            d->animation->stop();
        }

        emit runningChanged();
    }
}

bool LottieAnimation::isRunning() const
{
    return d->animation->state() == QPropertyAnimation::Running;
}

void LottieAnimation::setLoops(int loops)
{
    if (d->animation->loopCount() != loops) {
        d->animation->setLoopCount(loops);

        emit loopsChanged();
    }
}

int LottieAnimation::loops() const
{
    return d->animation->loopCount();
}

void LottieAnimation::componentComplete()
{
    QQuickItem::componentComplete();

    if (d->container) {
        d->container->currentFrame = d->currentFrame;
    }

    polish();
}

void LottieAnimation::start()
{
    setIsRunning(true);
}

void LottieAnimation::stop()
{
    setIsRunning(false);
}

void LottieAnimation::logHierarchyKeypaths()
{
    LOTKeypath path("**");

    for (const QString &keypath : d->container->keysForKeyPath(&path)) {
        qCDebug(logLottieAnimation) << keypath;
    }
}

QSGNode *LottieAnimation::updatePaintNode(QSGNode *rootNode, UpdatePaintNodeData *updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData);

    // FIXME: If we don't change the root node, we're having caching problems
    if (/*d->clearNodes &&*/ rootNode) {
        d->clearNodes = false;

        delete rootNode;
        rootNode = nullptr;
    }

    if (!rootNode) {
        rootNode = d->transformNode = new QSGTransformNode;
        d->transformNode->setFlag(QSGNode::OwnedByParent);

        d->rootNode = new QQuickShapeGenericNode;
        d->rootNode->setFlag(QSGNode::OwnedByParent);
        d->transformNode->appendChildNode(d->rootNode);

        d->renderer.setRootNode(d->rootNode);
    }

    if (d->composition) {
        QRectF compBounds = d->composition->compBounds;
        QRectF itemBounds = boundingRect();

        qreal xScale = itemBounds.width() / compBounds.width();
        qreal yScale = itemBounds.height() / compBounds.height();

        switch(d->fillMode) {
        case LottieAnimation::PreserveAspectFit:
            {
                qreal scale = qMin(xScale, yScale);

                QPointF itemCenter = itemBounds.center();
                QPointF compCenter = compBounds.center() * scale;

                QPointF translation = itemCenter - compCenter;

                QTransform transform;
                transform.translate(translation.x(), translation.y());
                transform.scale(scale, scale);

                d->transformNode->setMatrix(transform);
            }
            break;
        case LottieAnimation::PreserveAspectCrop:
            {
                qreal scale = qMax(xScale, yScale);

                QPointF itemCenter = itemBounds.center();
                QPointF compCenter = compBounds.center() * scale;

                QPointF translation = itemCenter - compCenter;

                QTransform transform;
                transform.translate(translation.x(), translation.y());
                transform.scale(scale, scale);

                d->transformNode->setMatrix(transform);
            }
            break;
        case LottieAnimation::Pad:
            {
                // Just center it
                QPointF itemCenter = itemBounds.center();
                QPointF compCenter = compBounds.center();

                QPointF translation = itemCenter - compCenter;

                QTransform transform;
                transform.translate(translation.x(), translation.y());

                d->transformNode->setMatrix(transform);
            }
            break;
        }
    }

    d->renderer.updateNode();

    return rootNode;
}

void LottieAnimation::updatePolish()
{
    d->sync();
}
