#ifndef LOTTIEANIMATION_H
#define LOTTIEANIMATION_H

#include <QQuickItem>

class LottieAnimation : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(qreal currentFrame READ currentFrame WRITE setCurrentFrame NOTIFY currentFrameChanged)
    Q_PROPERTY(qreal startFrame READ startFrame NOTIFY startFrameChanged)
    Q_PROPERTY(qreal endFrame READ endFrame NOTIFY endFrameChanged)
    Q_PROPERTY(qreal frameRate READ frameRate NOTIFY frameRateChanged)
    Q_PROPERTY(qreal timeDuration READ timeDuration NOTIFY timeDurationChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)

    Q_PROPERTY(bool running READ isRunning WRITE setIsRunning NOTIFY runningChanged)
    Q_PROPERTY(int loops READ loops WRITE setLoops NOTIFY loopsChanged)

public:
    explicit LottieAnimation(QQuickItem *parent = nullptr);
    ~LottieAnimation();

    enum FillMode {
        PreserveAspectFit,
        PreserveAspectCrop,
        Pad
    };
    Q_ENUM(FillMode)

    void setFillMode(FillMode fillMode);
    FillMode fillMode() const;

    enum Status {
        Null,
        Ready,
        Loading,
        Error
    };
    Q_ENUM(Status)

    Status status() const;

    Q_INVOKABLE QString errorString() const;

    qreal currentFrame() const;
    void setCurrentFrame(qreal currentFrame);

    qreal startFrame() const;
    qreal endFrame() const;
    qreal frameRate() const;
    qreal timeDuration() const;

    void setSource(const QUrl &source);
    QUrl source() const;

    void setIsRunning(bool isRunning);
    bool isRunning() const;

    void setLoops(int loops);
    int loops() const;

    // QQmlParserStatus interface
    void componentComplete() override;

public slots:
    void start();
    void stop();

protected:
    // QQuickItem interface
    QSGNode *updatePaintNode(QSGNode *rootNode, UpdatePaintNodeData *updatePaintNodeData) override;
    void updatePolish() override;

signals:
    void fillModeChanged();
    void statusChanged();

    void currentFrameChanged();
    void startFrameChanged();
    void endFrameChanged();
    void frameRateChanged();
    void timeDurationChanged();

    void sourceChanged();

    void runningChanged();
    void loopsChanged();

private:
    class Private;
    Private *d;
};

#endif // LOTTIEANIMATION_H
