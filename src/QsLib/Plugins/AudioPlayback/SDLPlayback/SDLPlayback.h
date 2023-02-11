#ifndef SDLPLAYBACK_H
#define SDLPLAYBACK_H

#include "Api/IAudioPlayback.h"

class SDLPlaybackPrivate;

class Q_DECL_EXPORT SDLPlayback : public IAudioPlayback {
    Q_OBJECT
    Q_DECLARE_PRIVATE(SDLPlayback)
    Q_INTERFACES(IAudioPlayback)
    Q_PLUGIN_METADATA(IID IAudioPlayback_IID FILE "plugin.json")
public:
    explicit SDLPlayback(QObject *parent = nullptr);
    ~SDLPlayback();

public:
    QStringList drivers() const override;
    QString currentDriver() const override;
    bool setDriver(const QString &driver) override;

    QStringList devices() const override;
    QString currentDevice() const override;
    bool setDevice(const QString &device) override;

protected:
    SDLPlayback(SDLPlaybackPrivate &d, QObject *parent = nullptr);
};

#endif // SDLPLAYBACK_H
