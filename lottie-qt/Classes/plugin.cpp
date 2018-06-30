#include "plugin.h"
#include "lottieanimation.h"

void LottieQmlPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Lottie"));
    qmlRegisterType<LottieAnimation>(uri, 1, 0, "LottieAnimation");
}
