#ifndef QMCOREHOST_H
#define QMCOREHOST_H

#include <QObject>
#include <QSettings>

#include "QMGlobal.h"

#define qmHost QMCoreHost::instance()

class QMCoreHostPrivate;

class QMCORELIB_API QMCoreHost : public QObject {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QMCoreHost)
    Q_SINGLETON(QMCoreHost)
public:
    explicit QMCoreHost(QObject *parent = nullptr);
    ~QMCoreHost();

public:
    bool isAboutToQuit() const;
    QSettings::Format settingsJsonFormat() const;

    QString appDataDir() const;
    void setAppDataDir(const QString &dir);

    QString tempDir() const;
    void setTempDir(const QString &dir);

    QString libDir() const;
    void setLibDir(const QString &dir);

    QString shareDir() const;
    void setShareDir(const QString &dir);

    bool createDataAndTempDirs() const;

protected:
    QMCoreHost(QMCoreHostPrivate &d, QObject *parent = nullptr);

    QScopedPointer<QMCoreHostPrivate> d_ptr;

private:
    void _q_appAboutToQuit();
};

#endif // QMCOREHOST_H
