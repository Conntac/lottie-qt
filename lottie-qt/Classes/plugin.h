#ifndef PLUGIN_H
#define PLUGIN_H

#include <QQmlExtensionPlugin>
#include <QQmlEngine>

class LottieQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);
};

#endif // PLUGIN_H
