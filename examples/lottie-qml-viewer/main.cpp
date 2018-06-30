#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "lottieanimation.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("material");

    qmlRegisterType<LottieAnimation>("Lottie", 1, 0, "LottieAnimation");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
