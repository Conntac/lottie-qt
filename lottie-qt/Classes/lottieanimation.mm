#include "lottieanimation.h"

#include <QLoggingCategory>

#include "qquickshape_p.h"
#include "qquickshapegenericrenderer_p.h"

//#import "LOTAnimationView.h"

#include "LOTComposition.h"
#include "LOTCompositionContainer.h"

Q_LOGGING_CATEGORY(logLottieAnimation, "lottie_animation")

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
    qreal currentFrame = 0;
    qreal startFrame = 0.0;
    qreal endFrame = 0.0;
    qreal frameRate = 0.0;
    qreal timeDuration = 0.0;

    QUrl source;

    QSharedPointer<LOTCompositionContainer> container;

    QQuickShapeGenericRenderer renderer;
    QQuickShapeGenericNode *rootNode = nullptr;

    // Functions
    void loadAnimation();
    void sync();
};

static void walkLayers(int indent, const QSharedPointer<QQuickLottieLayer> &layer, QList<QQuickLottieLayer *> *layers) {
    if (layer->hidden()) {
        return;
    }

    layers->append(layer.data());

    for (auto child : layer->sublayers) {
        walkLayers(indent + 1, child, layers);
    }
}

void LottieAnimation::Private::loadAnimation()
{
    QString path = source.toString();
    if (path.startsWith("qrc:")) {
        path.remove(0, 3);
    }

    LOTComposition *composition = new LOTComposition(path);
    if (composition) {
        container = container.create(nil, nil, composition->layerGroup, composition->assetGroup);

        startFrame = composition->startFrame;
        endFrame = composition->endFrame;
        frameRate = composition->framerate;
        timeDuration = composition->timeDuration;

//        QRectF bound = QRectF::fromCGRect(composition.compBounds);

        emit q->startFrameChanged();
        emit q->endFrameChanged();
        emit q->frameRateChanged();
        emit q->timeDurationChanged();

        container->display();
    }
}

void LottieAnimation::Private::sync()
{
    if (!container) {
        return;
    }

    // Collect all layers as flat items
    QList<QQuickLottieLayer *> flatLayers;
    walkLayers(0, container, &flatLayers);

    const int count = flatLayers.size();

//    qCDebug(logLottieAnimation) << "Collected" << count << "layers";

    renderer.beginSync(count);

    for(int i=0; i < count; ++i) {
        QQuickLottieLayer *layer = flatLayers.at(i);

        QList<QTransform> transformTree;
        QQuickLottieLayer *p = layer;
        while (p) {
            transformTree.prepend(p->transform());

            p = p->parentLayer;
        }

        QTransform absoluteTransform;
        for(QTransform t : transformTree) {
            absoluteTransform *= t;
        }

        renderer.setTransform(i, absoluteTransform);
        renderer.setHidden(i, layer->hidden());
        renderer.setOpacity(i, layer->opacity());
        renderer.setPath(i, layer->path());
        renderer.setStrokeColor(i, layer->strokeColor());
        renderer.setStrokeWidth(i, layer->strokeWidth());
        renderer.setFillColor(i, layer->fillColor());
        renderer.setFillRule(i, (QQuickShapePath::FillRule)layer->fillRule());
        renderer.setJoinStyle(i, (QQuickShapePath::JoinStyle)layer->joinStyle(), layer->miterLimit());
        renderer.setCapStyle(i, (QQuickShapePath::CapStyle)layer->capStyle());
        renderer.setStrokeStyle(i, (QQuickShapePath::StrokeStyle)layer->strokeStyle(), layer->dashOffset(), layer->dashPattern());
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
    setFlag(ItemHasContents);
}

LottieAnimation::~LottieAnimation()
{
    delete d;
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

    if (d->container->currentFrame == currentFrame) {
        return;
    }

    d->container->currentFrame = currentFrame;

    emit currentFrameChanged();

    d->container->display();
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

        emit sourceChanged();

        d->loadAnimation();
    }
}

QUrl LottieAnimation::source() const
{
    return d->source;
}

void LottieAnimation::componentComplete()
{
    QQuickItem::componentComplete();

    if (d->container) {
        d->container->currentFrame = d->currentFrame;
        d->container->display();
    }

    polish();
}

QSGNode *LottieAnimation::updatePaintNode(QSGNode *rootNode, UpdatePaintNodeData *updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData);

    // FIXME: If we don't change the root node, we're having caching problems
    if (rootNode) {
        delete rootNode;
        rootNode = nullptr;
    }

    if (!rootNode) {
        rootNode = d->rootNode = new QQuickShapeGenericNode;
        rootNode->setFlag(QSGNode::OwnedByParent);

        d->renderer.setRootNode(d->rootNode);
    }

    d->renderer.updateNode();

    return rootNode;
}

void LottieAnimation::updatePolish()
{
    d->sync();
}
