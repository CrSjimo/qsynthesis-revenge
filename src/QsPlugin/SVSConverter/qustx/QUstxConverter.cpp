#include "QUstxConverter.h"

QUstxConverter::QUstxConverter(QObject *parent) : ISVSConverter(parent) {
}

QUstxConverter::~QUstxConverter() {
}

bool QUstxConverter::load(const QString &filename, QSvipFile *out,
                          const QMap<QString, QVariant> &args) {
    return false;
}

bool QUstxConverter::save(const QString &filename, const QSvipFile &in,
                          const QMap<QString, QVariant> &args) {
    return false;
}