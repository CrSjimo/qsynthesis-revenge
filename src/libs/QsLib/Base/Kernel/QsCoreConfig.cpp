#include "QsCoreConfig.h"
#include "QMSystem.h"
#include "private/QsCoreConfig_p.h"

#include <QDebug>

Q_SINGLETON_DECLARE(QsCoreConfig)

QsCoreConfig::QsCoreConfig() : QsCoreConfig(*new QsCoreConfigPrivate()) {
}

QsCoreConfig::~QsCoreConfig() {
}

bool QsCoreConfig::load(const QString &filename) {
    Q_D(QsCoreConfig);
    bool res = true;
    d->initAll();
    if (!d->load_helper(filename)) {
        qDebug().noquote()
            << QString("load_config: configuration file %1 not found.").arg(QMFs::PathFindFileName(filename));
        res = false;
    }
    return res;
}

bool QsCoreConfig::apply() {
    Q_D(QsCoreConfig);
    return d->apply_helper();
}

void QsCoreConfig::saveDefault(const QString &filename) {
    Q_D(QsCoreConfig);
    d->save_default(filename);
}

QString QsCoreConfig::appDir(int type) const {
    Q_D(const QsCoreConfig);
    return d->dirMap.value(type).dir;
}

QString QsCoreConfig::locateBinTool(const QString &name) const {
#ifdef Q_OS_WINDOWS
    const char _suffix[] = ".exe";
#else
    const char _suffix[] = "";
#endif
    QString filename = QMFs::binaryPath() + '/' + name + _suffix;
    if (QFileInfo(filename).isExecutable()) {
        return filename;
    }
    return QString();
}

QString QsCoreConfig::internalPlugin(QsCoreConfig::InternalPlugins id) const {
    Q_D(const QsCoreConfig);
    return d->pluginMap.value(id).name;
}

QsCoreConfig::QsCoreConfig(QsCoreConfigPrivate &d) : d_ptr(&d) {
    construct();

    d.q_ptr = this;
    d.init();
}