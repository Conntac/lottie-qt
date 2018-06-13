#ifndef LOTTIEANIMATION_H
#define LOTTIEANIMATION_H

#include <QQuickItem>

class LottieAnimation : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal currentFrame READ currentFrame WRITE setCurrentFrame NOTIFY currentFrameChanged)
    Q_PROPERTY(qreal startFrame READ startFrame NOTIFY startFrameChanged)
    Q_PROPERTY(qreal endFrame READ endFrame NOTIFY endFrameChanged)
    Q_PROPERTY(qreal frameRate READ frameRate NOTIFY frameRateChanged)
    Q_PROPERTY(qreal timeDuration READ timeDuration NOTIFY timeDurationChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)

public:
    explicit LottieAnimation(QQuickItem *parent = nullptr);
    ~LottieAnimation();

    qreal currentFrame() const;
    void setCurrentFrame(qreal currentFrame);

    qreal startFrame() const;
    qreal endFrame() const;
    qreal frameRate() const;
    qreal timeDuration() const;

    void setSource(const QUrl &source);
    QUrl source() const;

    // QQmlParserStatus interface
    void componentComplete() override;

protected:
    // QQuickItem interface
    QSGNode *updatePaintNode(QSGNode *rootNode, UpdatePaintNodeData *updatePaintNodeData) override;
    void updatePolish() override;

signals:
    void currentFrameChanged();
    void startFrameChanged();
    void endFrameChanged();
    void frameRateChanged();
    void timeDurationChanged();

    void sourceChanged();

private:
    class Private;
    Private *d;
};

#endif // LOTTIEANIMATION_H
